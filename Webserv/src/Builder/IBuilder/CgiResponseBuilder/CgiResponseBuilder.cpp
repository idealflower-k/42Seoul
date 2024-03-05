#include "CgiResponseBuilder.hpp"

// cgi_tester는 cgi 스크립트가 아니라 fastCgi의 역할을 해주는 것이다.
// .bla 같은 특정 확장자의 요청은 모두 cgi로 처리될 수 있는 설정 방식이 추가 되어야 한다.
// cgi_tester에게 .bla 같은 실행야하는 스크립트 정보를 주는 것이다.
// .bla 같은 스크립트파일이 없으면 서버에서 404 notfound로 처리한다.
// 로케이션 자체가 cgi처리한다고 하면 기본실행 스크립트가 있어야 한다.

CgiResponseBuilder::CgiResponseBuilder(reactor::sharedData_t sharedData, const request_t request,
									   const utils::shared_ptr<ServerConfig>& serverConfig,
									   const utils::shared_ptr<LocationConfig>& locationConfig)
	: _sharedData(sharedData),
	  _request(request),
	  _serverConfig(serverConfig),
	  _locationConfig(locationConfig),
	  _unchunkedState(false),
	  _forked(false),
	  _cgiReadSharedData(),
	  _startLineState(false),
	  _contentLengthState(false),
	  _sessionData(u::nullptr_t) {
	this->_pendingBuf.clear();
	this->inItInterpreterMap();
	this->prepare();
}

CgiResponseBuilder::CgiResponseBuilder(reactor::sharedData_t sharedData, const request_t request,
									   const utils::shared_ptr<ServerConfig>& serverConfig,
									   const utils::shared_ptr<LocationConfig>& locationConfig,
									   SessionData* sessionData)
	: _sharedData(sharedData),
	  _request(request),
	  _serverConfig(serverConfig),
	  _locationConfig(locationConfig),
	  _unchunkedState(false),
	  _forked(false),
	  _cgiReadSharedData(),
	  _startLineState(false),
	  _contentLengthState(false),
	  _sessionData(sessionData) {
	this->_pendingBuf.clear();
	this->inItInterpreterMap();
	this->prepare();
}

void CgiResponseBuilder::inItInterpreterMap() {
	this->_interpreterMap["pl"] = "perl";
	this->_interpreterMap["py"] = "python";
	this->_interpreterMap["rb"] = "ruby";
	this->_interpreterMap["php"] = "php";
}

void CgiResponseBuilder::prepare() {
	this->_cgiFullPath = this->makeCgiFullPath();
	if (this->_cgiFullPath.empty())
		throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
			NOT_FOUND, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
	if (this->makePipes() == false)
		throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
			INTERNAL_SERVER_ERROR, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
	this->makeWriteSharedData();
	this->_cgiReadSharedData = utils::shared_ptr<reactor::SharedData>(
		new reactor::SharedData(this->_pipes[PIPE_PREAD], EVENT_READ, std::vector<char>()));
	reactor::Dispatcher::getInstance()->registerIOHandler<reactor::ClientReadHandlerFactory>(this->_cgiReadSharedData);
}

bool CgiResponseBuilder::build() {
	int status;
	if (this->_sharedData->getState() == TERMINATE) {
		this->removeIOHandlers();
		this->_cgiWriteSharedData->setState(TERMINATE);
		this->_cgiReadSharedData->setState(TERMINATE);
		if (this->_forked) {
			if (waitpid(this->_cgiPid, &status, WNOHANG) < 0)
				kill(this->_cgiPid, SIGTERM);
		}
		return false;
	}
	if (this->_forked) {
		if (waitpid(this->_cgiPid, &status, WNOHANG) > 0) {
			if (WIFEXITED(status) == false) {
				this->removeIOHandlers();
				close(this->_pipes[PIPE_PREAD]);
				close(this->_pipes[PIPE_PWRITE]);
				throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
					BAD_GATEWAY, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
			}
		} else {
			if (std::difftime(std::time(NULL), this->_cgiTime) >= 180) {
				kill(this->_cgiPid, SIGTERM);
				this->removeIOHandlers();
				close(this->_pipes[PIPE_PREAD]);
				close(this->_pipes[PIPE_PWRITE]);
				throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
					BAD_GATEWAY, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
			}
		}
	}
	return this->setBody();
}

bool CgiResponseBuilder::setBody() {
	if (this->_cgiReadSharedData.get() == u::nullptr_t)
		return false;
	if (this->makeunChunked() == false) {
		return false;
	}
	if ((this->_request->first == DONE || this->_request->first == LONG_BODY_DONE ||
		 this->_request->first == CHUNKED_DONE) &&
		this->_cgiWriteSharedData->getBuffer().empty() && this->_cgiWriteSharedData->getState() != RESOLVE) {
		this->removeWriteIO();
		close(this->_pipes[PIPE_PWRITE]);
		this->_cgiWriteSharedData->setState(RESOLVE);
	}
	if (this->_startLineState == false)
		this->replaceStartLine();
	else if (this->_startLineState == true && this->_contentLengthState == false)
		this->checkContentLength();
	if (this->_startLineState == true && this->_contentLengthState == true) {
		utils::insertData<std::vector<char>, std::vector<char> >(this->_sharedData.get()->getBuffer(),
																 this->_cgiReadSharedData.get()->getBuffer());
		this->_cgiReadSharedData.get()->getBuffer().clear();
	}
	if (this->_cgiReadSharedData.get()->getState() == TERMINATE && this->_cgiWriteSharedData->getState() == RESOLVE) {
		if (this->_startLineState == false && this->_sharedData->getBuffer().empty()) {
			this->removeIOHandlers();
			this->cleanPipes();
			throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
				BAD_GATEWAY, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
		}
		this->removeReadIO();
		close(this->_pipes[PIPE_PREAD]);
		this->_cgiReadSharedData->setState(RESOLVE);
		return true;
	}
	return true;
}

bool CgiResponseBuilder::makeunChunked() {
	if (this->_unchunkedState == true)
		return this->_unchunkedState;
	if (this->_request->first == CHUNKED_ERROR || this->_request->first == HTTP_ERROR) {
		this->removeReadIO();
		this->cleanPipes();
		throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(
			new ErrorResponseBuilder(this->_request->second.getErrorCode(), this->_sharedData, this->_request,
									 this->_serverConfig, this->_locationConfig));
	}

	if ((this->_request->first == DONE || this->_request->first == LONG_BODY_DONE ||
		 this->_request->first == CHUNKED_DONE)) {
		this->_request->second.getBody().append("\0");
		this->_request->second.getHeaders()[CONTENT_LENGTH] =
			utils::lltos(this->_request->second.getContentLengthReceived());
		utils::insertData<std::vector<char>, std::string>(this->_cgiWriteSharedData->getBuffer(),
														  this->_request->second.getBody());
		this->_request->second.getBody().clear();
		if (this->_forked == false) {
			if (this->doFork() == false) {
				this->cleanPipes();
				throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(
					new ErrorResponseBuilder(INTERNAL_SERVER_ERROR, this->_sharedData, this->_request,
											 this->_serverConfig, this->_locationConfig));
			}
			close(this->_pipes[PIPE_CREAD]);
			close(this->_pipes[PIPE_CWRITE]);
			reactor::Dispatcher::getInstance()->registerIOHandler<reactor::ClientWriteHandlerFactory>(
				this->_cgiWriteSharedData);
			this->_forked = true;
			this->_unchunkedState = true;
		}
		return true;
	}
	utils::insertData<std::vector<char>, std::string>(this->_cgiWriteSharedData->getBuffer(),
													  this->_request->second.getBody());
	this->_request->second.getBody().clear();
	return false;
}

void CgiResponseBuilder::cgiStartLineInsert() {
	const std::string delimiter = "\r\n";
	std::vector<char>& readBuffer = this->_cgiReadSharedData->getBuffer();
	std::vector<char>::iterator it =
		std::search(readBuffer.begin(), readBuffer.end(), delimiter.begin(), delimiter.end());

	if (it != readBuffer.end()) {
		readBuffer.erase(readBuffer.begin(), it + delimiter.size());
		std::string startLine = this->_startLine[0] + " " + this->_startLine[1] + " " + this->_startLine[2] + "\r\n";
		readBuffer.insert(readBuffer.begin(), startLine.begin(), startLine.end());
		this->_startLineState = true;
	}
}

void CgiResponseBuilder::replaceStartLine() {
	std::vector<char>& readBuffer = this->_cgiReadSharedData->getBuffer();
	if (readBuffer.size() == 0)
		return;
	std::string msg;

	const std::string crlf = "\r\n";
	std::vector<char>::iterator crlfIt = std::search(readBuffer.begin(), readBuffer.end(), crlf.begin(), crlf.end());

	if (crlfIt == readBuffer.end())
		return;

	msg.assign(readBuffer.begin(), crlfIt);
	std::stringstream ss;
	ss << msg;
	ss >> this->_startLine[0] >> this->_startLine[1] >> this->_startLine[2];
	if (this->_startLine[0].empty() || this->_startLine[1].empty() || this->_startLine[2].empty()) {
		this->_startLine->clear();
		return;
	}
	if (this->_startLine[0].compare("Status:") == 0) {
		this->_startLine[0] = "HTTP/1.1";
		this->_startLineState = true;
	} else {
		this->_startLine[0] = "HTTP/1.1";
		this->_startLine[1] = "200";
		this->_startLine[2] = "OK";
		std::string startLine = this->_startLine[0] + " " + this->_startLine[1] + " " + this->_startLine[2] + "\r\n";
		readBuffer.insert(readBuffer.begin(), startLine.begin(), startLine.end());
		this->_startLineState = true;
		return;
	}
	this->cgiStartLineInsert();
}

void CgiResponseBuilder::checkContentLength() {
	std::vector<char>& readBuffer = this->_cgiReadSharedData->getBuffer();
	if (readBuffer.size() == 0)
		return;
	const std::string cl = "Content-Length";
	std::vector<char>::iterator clIt = std::search(readBuffer.begin(), readBuffer.end(), cl.begin(), cl.end());

	if (clIt != readBuffer.end()) {
		this->_contentLengthState = true;
		return;
	}
	if (this->_cgiReadSharedData->getState() != TERMINATE) {
		return;
	} else {
		const std::string crlfcrlf = "\r\n\r\n";
		std::vector<char>::iterator clclIt =
			std::search(readBuffer.begin(), readBuffer.end(), crlfcrlf.begin(), crlfcrlf.end());
		if (clclIt != readBuffer.end()) {
			size_t contentLength = 0;
			clclIt += crlfcrlf.size();
			for (; clclIt != readBuffer.end(); ++clclIt)
				contentLength++;
			std::string contentLengthHeader = "Content-Length: " + utils::lltos(contentLength) + "\r\n";
			std::string crlf = "\r\n";
			clclIt = std::search(readBuffer.begin(), readBuffer.end(), crlf.begin(), crlf.end());
			readBuffer.insert(clclIt + crlf.size(), contentLengthHeader.begin(), contentLengthHeader.end());
			this->_contentLengthState = true;
			return;
		}
	}
}

std::string CgiResponseBuilder::makeUriPath() {
	std::string uriCgiPath = this->_request->second.getRequestTarget();

	size_t dotPos = uriCgiPath.find('.');
	if (dotPos != std::string::npos) {
		size_t slashPos = uriCgiPath.find('/', dotPos);
		if (slashPos != std::string::npos)
			uriCgiPath.erase(slashPos);
		size_t questPos = uriCgiPath.find('?');
		if (questPos == std::string::npos)
			return (uriCgiPath);
		uriCgiPath.erase(questPos);
		return (uriCgiPath);
	} else {
		size_t questPos = uriCgiPath.find('?');
		if (questPos != std::string::npos)
			uriCgiPath.erase(questPos);
	}
	return (uriCgiPath);
}

std::string CgiResponseBuilder::makeCgiFullPath() {
	const std::string locRootPath = this->_locationConfig.get()->getDirectives(ROOT).asString();
	const std::string serverRootPath = this->_serverConfig.get()->getDirectives(ROOT).asString();
	const std::vector<std::string> cgiIndex = this->_locationConfig.get()->getDirectives(CGI_INDEX).asStrVec();
	const std::string locationPath = this->_locationConfig.get()->getPath();

	for (std::vector<std::string>::const_iterator it = cgiIndex.begin(); it != cgiIndex.end(); ++it) {
		std::string cgiIndexTemp = *it;
		if ((*it)[0] == '/')
			cgiIndexTemp = (*it).substr(1);
		if (access((locRootPath + cgiIndexTemp).c_str(), X_OK) == 0)
			return locRootPath + cgiIndexTemp;
		if (access((serverRootPath + cgiIndexTemp).c_str(), X_OK) == 0)
			return serverRootPath + cgiIndexTemp;
	}
	return std::string("");
}

reactor::sharedData_t CgiResponseBuilder::getProduct() {
	return this->_cgiReadSharedData;
}

void CgiResponseBuilder::setStartLine() {
	this->_response.setStartLine(DefaultResponseBuilder::getInstance()->setDefaultStartLine(200));
}

bool CgiResponseBuilder::makePipes() {
	if (pipe(this->_writePipe) < 0 || pipe(this->_readPipe) < 0) {
		ErrorLogger::systemCallError(__FILE__, __LINE__, __func__);
		return false;
	}
	if (fcntl(this->_writePipe[1], F_SETFL, O_NONBLOCK, FD_CLOEXEC) < 0 ||
		fcntl(this->_readPipe[0], F_SETFL, O_NONBLOCK, FD_CLOEXEC) < 0) {
		ErrorLogger::systemCallError(__FILE__, __LINE__, __func__);
		return false;
	}
	this->_pipes[PIPE_PREAD] = this->_readPipe[0];
	this->_pipes[PIPE_CREAD] = this->_writePipe[0];
	this->_pipes[PIPE_PWRITE] = this->_writePipe[1];
	this->_pipes[PIPE_CWRITE] = this->_readPipe[1];
	return true;
}

void CgiResponseBuilder::makeWriteSharedData() {
	this->_cgiWriteSharedData = utils::shared_ptr<reactor::SharedData>(
		new reactor::SharedData(this->_pipes[PIPE_PWRITE], EVENT_WRITE, std::vector<char>()));
	utils::insertData<std::vector<char>, std::string>(this->_cgiWriteSharedData->getBuffer(),
													  this->_request->second.getBody());
	this->_request->second.getBody().clear();
}

std::string CgiResponseBuilder::makeQueryString() {
	std::string queryString = this->_request->second.getRequestTarget();

	if (queryString.empty())
		return std::string("");

	size_t questPos = queryString.find('?');

	if (questPos != std::string::npos) {
		queryString.erase(0, questPos + 1);
		return (queryString);
	} else
		return std::string("");
}

bool CgiResponseBuilder::doFork() {
	this->_cgiPid = fork();
	if (this->_cgiPid == -1) {
		this->cleanPipes();
		return false;
	}
	this->_cgiTime = std::time(NULL);
	if (this->_cgiPid == 0) {
		close(this->_pipes[PIPE_PWRITE]);
		close(this->_pipes[PIPE_PREAD]);
		char** envp = this->setEnvp();
		char** args = this->makeArgs();
		if (dup2(this->_pipes[PIPE_CREAD], STDIN_FILENO) == -1) {
			close(this->_pipes[PIPE_CREAD]);
			close(this->_pipes[PIPE_CWRITE]);
			exit(1);
		}
		if (dup2(this->_pipes[PIPE_CWRITE], STDOUT_FILENO) == -1) {
			close(this->_pipes[PIPE_CREAD]);
			close(this->_pipes[PIPE_CWRITE]);
			exit(1);
		}
		close(this->_pipes[PIPE_CREAD]);
		close(this->_pipes[PIPE_CWRITE]);
		execve(args[0], args, envp);
		exit(1);
	}
	return true;
}

char** CgiResponseBuilder::makeArgs() {
	std::vector<std::string> argsVec;
	std::string interpreter = this->makeInterpreter();
	if (!interpreter.empty())
		argsVec.push_back(interpreter);
	argsVec.push_back(this->_cgiFullPath);
	char** args = new char*[argsVec.size() + 1];
	for (size_t i = 0; i < argsVec.size(); ++i) {
		args[i] = strdup((argsVec[i].c_str()));
	}
	args[argsVec.size()] = NULL;
	return args;
}

void CgiResponseBuilder::makeHttpHeaders(std::string& key) {
	std::string http = "HTTP_";
	for (size_t i = 0; i < key.length(); ++i) {
		key[i] = std::toupper(key[i]);
		if (key[i] == '-')
			key[i] = '_';
	}
	key = http + key;
}

void CgiResponseBuilder::setClientHeaders(std::vector<std::string>& cgiEnvVec) {
	std::map<std::string, std::string>& headers = this->_request.get()->second.getHeaders();

	for (std::map<std::string, std::string>::iterator hIt = headers.begin(); hIt != headers.end(); ++hIt) {
		std::string key = hIt->first;
		std::string value = hIt->second;
		if (key != "Content-Type" && key != "Content-Length") {
			this->makeHttpHeaders(key);
			this->addCgiEnvp(cgiEnvVec, key, value);
		}
	}
}

std::string CgiResponseBuilder::makePathTranslated() {
	std::string rootPath = this->_locationConfig->getDirectives(ROOT).asString();
	std::string uriPath = this->_request->second.getRequestTarget();

	if (uriPath[0] == '/')
		uriPath.erase(0, 1);
	size_t questPos = uriPath.find('?');
	if (questPos != std::string::npos)
		uriPath.erase(questPos);
	size_t dotPos = uriPath.find('.');
	if (dotPos == std::string::npos) {
		std::vector<std::string> indexs = this->_locationConfig->getDirectives(INDEX).asStrVec();
		return rootPath + indexs[0];
	}
	return rootPath + uriPath;
}

void CgiResponseBuilder::setEnvpSessionData(std::vector<std::string>& cgiEnvpVec) {
	if (this->_sessionData == u::nullptr_t)
		return;
	for (std::map<std::string, std::string>::const_iterator cit = this->_sessionData->getData().begin();
		 cit != this->_sessionData->getData().end(); ++cit) {
		std::string key = "X_" + cit->first;
		std::string value = cit->second;
		this->addCgiEnvp(cgiEnvpVec, key, value);
	}
}

char** CgiResponseBuilder::setEnvp() {
	char** envp = ServerManager::getInstance()->getEnvp();

	std::vector<std::string> cgiEnvpVec;
	this->setClientHeaders(cgiEnvpVec);
	this->setEnvpSessionData(cgiEnvpVec);

	std::map<std::string, std::string>& headers = this->_request.get()->second.getHeaders();
	std::string serverName = this->_serverConfig->getDirectives(SERVER_NAME).asString();
	size_t colPos = serverName.find(':');
	if (colPos != std::string::npos)
		serverName.erase(colPos);
	std::string contentType = headers["Content-Type"];
	size_t contentPos = contentType.find(';');
	contentType.erase(contentPos + 1);
	std::string contentLength = headers["Content-Length"];
	if (contentLength.empty())
		contentLength = "0";

	std::string method = this->_request.get()->second.getMethodStr();
	std::string scriptName = "";
	std::string queryString = this->makeQueryString();
	std::string serverPort = utils::itos(this->_serverConfig.get()->getDirectives(LISTEN).asUint());
	std::string serverProtocol = "HTTP/1.1";
	std::string gatewayInterface = "CGI/1.1";
	std::string remoteAddr = ServerManager::getInstance()->getClientIp(this->_sharedData.get()->getFd());
	std::string pathInfo = this->makePathInfo();
	std::string pathTranslated = this->makePathTranslated();

	this->addCgiEnvp(cgiEnvpVec, "SERVER_NAME", serverName);
	this->addCgiEnvp(cgiEnvpVec, "CONTENT_TYPE", contentType);
	this->addCgiEnvp(cgiEnvpVec, "CONTENT_LENGTH", contentLength);
	this->addCgiEnvp(cgiEnvpVec, "REQUEST_METHOD", method);
	this->addCgiEnvp(cgiEnvpVec, "SCRIPT_NAME", scriptName);
	this->addCgiEnvp(cgiEnvpVec, "QUERY_STRING", queryString);
	this->addCgiEnvp(cgiEnvpVec, "SERVER_PORT", serverPort);
	this->addCgiEnvp(cgiEnvpVec, "SERVER_PROTOCOL", serverProtocol);
	this->addCgiEnvp(cgiEnvpVec, "GATEWAY_INTERFACE", gatewayInterface);
	this->addCgiEnvp(cgiEnvpVec, "REMOTE_ADDR", remoteAddr);
	this->addCgiEnvp(cgiEnvpVec, "PATH_INFO", pathInfo);
	this->addCgiEnvp(cgiEnvpVec, "PATH_TRANSLATED", pathTranslated);

	int envpLen;
	for (envpLen = 0; envp[envpLen] != NULL; ++envpLen)
		;
	char** newEnvp = new char*[cgiEnvpVec.size() + envpLen + 1];
	int idx;
	for (idx = 0; idx < envpLen; ++idx)
		newEnvp[idx] = envp[idx];
	for (size_t i = 0; i < cgiEnvpVec.size(); ++i) {
		newEnvp[idx] = strdup((cgiEnvpVec[i].c_str()));
		idx++;
	}
	newEnvp[idx] = NULL;
	return (newEnvp);
}

void CgiResponseBuilder::addCgiEnvp(std::vector<std::string>& cgiEnvpVec, const std::string& key,
									const std::string& value) {
	cgiEnvpVec.push_back(key + "=" + value);
}

std::string CgiResponseBuilder::makePathInfo() {
	std::string pathInfo = this->_request->second.getRequestTarget();

	size_t questPos = pathInfo.find('?');
	if (questPos == std::string::npos)
		return pathInfo;
	pathInfo.erase(questPos);
	return pathInfo;
}

std::string CgiResponseBuilder::makeInterpreter() {
	std::string extension = this->makeExtension();
	if (extension.empty())
		return std::string("");
	std::vector<std::string> pathEnvp = this->parsPathEnvp();
	std::string interpreter;
	std::map<std::string, std::string>::iterator it = this->_interpreterMap.find(extension);
	if (it == this->_interpreterMap.end())
		return std::string("");
	interpreter = it->second;
	for (size_t i = 0; i < pathEnvp.size(); ++i) {
		std::string exePath = pathEnvp[i] + "/" + interpreter;
		if (access(exePath.c_str(), F_OK | X_OK) == 0)
			return (exePath);
	}
	return std::string("");
}

std::string CgiResponseBuilder::makeExtension() {
	size_t dotPos = this->_cgiFullPath.find('.');
	if (dotPos == std::string::npos)
		return std::string("");
	size_t slashPos = this->_cgiFullPath.find('/', dotPos);
	std::string extension;
	if (slashPos != std::string::npos)
		extension = this->_cgiFullPath.substr(dotPos + 1, slashPos - dotPos - 1);
	else
		extension = this->_cgiFullPath.substr(dotPos + 1);
	return extension;
}

std::vector<std::string> CgiResponseBuilder::parsPathEnvp() {
	char** envp = ServerManager::getInstance()->getEnvp();
	std::vector<std::string> result;
	int i;

	i = 0;
	while (envp && envp[i]) {
		if (std::memcmp(envp[i], "PATH=", 5) == 0)
			result = utils::split(std::string(envp[i]), ":");
		i++;
	}
	return (result);
}

CgiResponseBuilder::~CgiResponseBuilder() {}

void CgiResponseBuilder::setHeader() {}

void CgiResponseBuilder::reset() {}

void CgiResponseBuilder::cleanPipes() {
	close(this->_pipes[PIPE_PREAD]);
	close(this->_pipes[PIPE_PWRITE]);
	close(this->_pipes[PIPE_CWRITE]);
	close(this->_pipes[PIPE_CREAD]);
}

void CgiResponseBuilder::removeIOHandlers() {
	this->removeReadIO();
	this->removeWriteIO();
}

void CgiResponseBuilder::removeReadIO() {
	reactor::Dispatcher::getInstance()->removeIOHandler(this->_cgiReadSharedData->getFd(),
														this->_cgiReadSharedData->getType());
}

void CgiResponseBuilder::removeWriteIO() {
	reactor::Dispatcher::getInstance()->removeIOHandler(this->_cgiWriteSharedData->getFd(),
														this->_cgiWriteSharedData->getType());
}

utils::shared_ptr<IBuilder<reactor::sharedData_t> > CgiResponseBuilder::createCgiResponseBuilder(
	const reactor::sharedData_t& sharedData, const request_t& request,
	const utils::shared_ptr<ServerConfig>& serverConfig, const utils::shared_ptr<LocationConfig>& locationConfig) {
	return utils::shared_ptr<IBuilder<reactor::sharedData_t> >(
		new CgiResponseBuilder(sharedData, request, serverConfig, locationConfig));
}

utils::shared_ptr<IBuilder<reactor::sharedData_t> > CgiResponseBuilder::createCgiResponseBuilder(
	const reactor::sharedData_t& sharedData, const request_t& request,
	const utils::shared_ptr<ServerConfig>& serverConfig, const utils::shared_ptr<LocationConfig>& locationConfig,
	SessionData* sessionData) {
	return utils::shared_ptr<IBuilder<reactor::sharedData_t> >(
		new CgiResponseBuilder(sharedData, request, serverConfig, locationConfig, sessionData));
}
