#include "GetResponseBuilder.hpp"

GetResponseBuilder::GetResponseBuilder(reactor::sharedData_t sharedData, const request_t request,
									   const utils::shared_ptr<ServerConfig>& serverConfig,
									   const utils::shared_ptr<LocationConfig>& locationConfig,
									   SessionData* sessionData)
	: _sharedData(sharedData),
	  _request(request),
	  _serverConfig(serverConfig),
	  _locationConfig(locationConfig),
	  _removed(false),
	  _sessionData(sessionData),
	  _path(),
	  _fd(FD_ERROR),
	  _readSharedData(),
	  _response() {
	if (_sessionData)
		this->handleSession();
	this->prepare();
}

GetResponseBuilder::~GetResponseBuilder() {
	reactor::FileCloseManager::getInstance()->closeFd(this->_fd);
}

reactor::sharedData_t GetResponseBuilder::getProduct() {
	return this->_readSharedData;
}

void GetResponseBuilder::setStartLine() {
	this->_response.setStartLine(DefaultResponseBuilder::getInstance()->setDefaultStartLine(OK));
}

void GetResponseBuilder::setHeader() {
	struct stat fileInfo;

	if (stat(this->_path.c_str(), &fileInfo) == SYSTEMCALL_ERROR) {
		throw ErrorResponseBuilder::createErrorResponseBuilder(INTERNAL_SERVER_ERROR, this->_sharedData, this->_request,
															   this->_serverConfig, this->_locationConfig);
	}
	if (fileInfo.st_size == 0) {
		reactor::FileCloseManager::getInstance()->closeFd(this->_fd);
		this->_fd = FD_ZERO_;
	}
	std::map<std::string, std::string> headers =
		DefaultResponseBuilder::getInstance()->setDefaultHeader(this->_serverConfig, this->_path);
	headers[CONTENT_LENGTH] = utils::lltos(fileInfo.st_size);
	this->_response.setHeaders(headers);
}

bool GetResponseBuilder::setBody() {
	this->_sharedData->getBuffer().insert(this->_sharedData->getBuffer().end(),
										  this->_readSharedData->getBuffer().begin(),
										  this->_readSharedData->getBuffer().end());
	this->_readSharedData->getBuffer().clear();
	if (this->_readSharedData->getState() == RESOLVE && this->_removed == false) {
		reactor::Dispatcher::getInstance()->removeIOHandler(this->_readSharedData->getFd(),
															this->_readSharedData->getType());
		this->_removed = true;
		return true;
	}
	return true;
}

void GetResponseBuilder::reset() {
	this->_response.reset();
	this->_sharedData->getBuffer().clear();
	this->_readSharedData->getBuffer().clear();
}
bool GetResponseBuilder::build() {
	if (this->_readSharedData.get() == u::nullptr_t)
		return false;
	if (this->_readSharedData->getState() == TERMINATE) {
		reactor::Dispatcher::getInstance()->removeIOHandler(this->_readSharedData.get()->getFd(),
															this->_readSharedData.get()->getType());
		this->_sharedData->setState(TERMINATE);
		throw false;
	}
	return this->setBody();
}

fd_t GetResponseBuilder::findReadFile() {
	const std::string locPath = this->_locationConfig->getDirectives(ROOT).asString();
	const std::string serverPath = this->_serverConfig->getDirectives(ROOT).asString();
	const std::string targetFile =
		utils::removeSubstring(this->_request->second.getRequestTarget(), this->_locationConfig->getPath());

	this->_path = locPath + targetFile;
	if (access(this->_path.c_str(), R_OK) == 0)
		return reactor::FileCloseManager::getInstance()->makeFd(this->_path, "r");
	this->_path = serverPath + targetFile;
	if (access(this->_path.c_str(), R_OK) == 0)
		return reactor::FileCloseManager::getInstance()->makeFd(this->_path, "r");
	return FD_ERROR;
}

fd_t GetResponseBuilder::fileProcessing() {
	const enum FileMode mode = this->checkFileMode(
		this->_locationConfig->getDirectives(ROOT).asString() +
		utils::removeSubstring(this->_request->second.getRequestTarget(), this->_locationConfig->getPath()));
	const enum FileMode serverMode = this->checkFileMode(
		this->_serverConfig->getDirectives(ROOT).asString() +
		utils::removeSubstring(this->_request->second.getRequestTarget(), this->_locationConfig->getPath()));
	if (this->_locationConfig->getPath() == this->_request->second.getRequestTarget() + '/')
		throw RedirectResponseBuilder::createRedirectResponseBuilder(
			SEE_OTHER, this->_request->second.getRequestTarget() + '/', this->_sharedData, this->_request,
			this->_serverConfig);
	if (mode == MODE_DIRECTORY)
		return directoryProcessing();
	if (mode == MODE_ERROR && serverMode == MODE_ERROR)
		throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
			NOT_FOUND, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
	return this->findReadFile();
}

std::vector<std::string> GetResponseBuilder::readDir(const std::string& path) {
	if (path == "")
		throw ErrorResponseBuilder::createErrorResponseBuilder(FORBIDDEN, this->_sharedData, this->_request,
															   this->_serverConfig, this->_locationConfig);
	DIR* dirp;
	struct dirent* dp;

	if ((dirp = opendir(path.c_str())) == u::nullptr_t)
		throw ErrorResponseBuilder::createErrorResponseBuilder(NOT_FOUND, this->_sharedData, this->_request,
															   this->_serverConfig, this->_locationConfig);
	std::vector<std::string> dirVec;
	while ((dp = readdir(dirp)) != u::nullptr_t) {
		if (dp->d_name[0] == '.')
			continue;
		if (dp == u::nullptr_t)
			throw ErrorResponseBuilder::createErrorResponseBuilder(
				INTERNAL_SERVER_ERROR, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig);
		dirVec.push_back(dp->d_name);
	}
	closedir(dirp);
	return dirVec;
};

void GetResponseBuilder::makeListHtml(const std::string& path, const std::vector<std::string>& dirVec) {
	const std::string requestTarget = this->_request->second.getRequestTarget();
	struct stat fileStat;

	std::string html = LIST_HTML_HEADER(requestTarget);

	for (std::vector<std::string>::const_iterator cit = dirVec.begin(); cit != dirVec.end(); ++cit) {
		if (stat((path + "/" + *cit).c_str(), &fileStat) == SYSTEMCALL_ERROR)
			throw ErrorResponseBuilder::createErrorResponseBuilder(
				INTERNAL_SERVER_ERROR, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig);
		if (S_ISDIR(fileStat.st_mode))
			html += "<a href=\"" + *cit + "\"/>" + *cit + "/</a>";
		else
			html += "<a href=\"" + *cit + "\">" + *cit + "</a>";

#if __APPLE__ == 1
		html += "                                               " +
				utils::formatTime(fileStat.st_birthtimespec.tv_sec, logTimeFormat::dirListFormat) +
				"                   " + (S_ISDIR(fileStat.st_mode) ? "-" : utils::lltos(fileStat.st_size)) + "\r\n";
#else
		html += "                                               " +
				utils::formatTime(fileStat.st_ctime, logTimeFormat::dirListFormat) + "                   " +
				(S_ISDIR(fileStat.st_mode) ? "-" : utils::lltos(fileStat.st_size)) + "\r\n";
#endif
	}
	html += "</pre><hr></body>\r\n</html>";
	this->setStartLine();
	std::map<std::string, std::string> headers =
		DefaultResponseBuilder::getInstance()->setDefaultHeader(this->_serverConfig);
	headers[CONTENT_LENGTH] = utils::lltos(html.size());
	headers["Content-Type"] = "text/html";
	this->_response.setHeaders(headers);
	const std::string raw = this->_response.getRawStr();
	this->_readSharedData = utils::shared_ptr<reactor::SharedData>(
		new reactor::SharedData(FD_LISTING, EVENT_READ, std::vector<char>(html.begin(), html.end())));
	this->_sharedData->getBuffer().insert(this->_sharedData->getBuffer().begin(), raw.begin(), raw.end());
	this->setReadState(RESOLVE);
	this->_removed = true;
}

fd_t GetResponseBuilder::directoryListing() {
	if (this->_locationConfig->getDirectives(AUTOINDEX).asBool() == false)
		throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
			FORBIDDEN, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
	const std::string path = this->_locationConfig->getPath() == this->_request->second.getRequestTarget()
								 ? this->_locationConfig->getOwnRoot()
								 : "";
	const std::vector<std::string> dirVec = this->readDir(path);
	makeListHtml(path, dirVec);

	return FD_LISTING;
}

fd_t GetResponseBuilder::directoryProcessing() {
	std::string middle =
		utils::removeSubstring(this->_request->second.getRequestTarget(), this->_locationConfig->getPath());
	if (middle[0] == '/')
		middle = "";
	if (this->checkFileMode(this->_locationConfig->getDirectives(ROOT).asString() +
							this->_request->second.getTargetFile()) == MODE_FILE)
		throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
			NOT_FOUND, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
	if (this->_locationConfig->getOwnIndex().empty())
		return this->directoryListing();
	const std::string locPath = this->_locationConfig->getDirectives(ROOT).asString() + middle;
	const std::string serverPath = this->_serverConfig->getDirectives(ROOT).asString() + middle;
	const std::vector<std::string> indexVec = this->_locationConfig->getDirectives(INDEX).asStrVec();

	for (std::vector<std::string>::const_iterator cit = indexVec.begin(); cit != indexVec.end(); ++cit) {
		this->_path = locPath + *cit;
		if (access(this->_path.c_str(), R_OK) == 0)
			return reactor::FileCloseManager::getInstance()->makeFd(this->_path, "r");
	}
	for (std::vector<std::string>::const_iterator cit = indexVec.begin(); cit != indexVec.end(); ++cit) {
		this->_path = serverPath + *cit;
		if (access(this->_path.c_str(), R_OK) == 0)
			return reactor::FileCloseManager::getInstance()->makeFd(this->_path, "r");
	}
	return FD_ERROR;
}

void GetResponseBuilder::prepare() {
	this->_fd = this->checkOurFileMode(this->_request->second.getRequestTarget()) == MODE_FILE
					? this->fileProcessing()
					: this->directoryProcessing();
	if (this->_fd == FD_ERROR)
		throw ErrorResponseBuilder::createErrorResponseBuilder(NOT_FOUND, this->_sharedData, this->_request,
															   this->_serverConfig, this->_locationConfig);
	if (this->_fd == FD_LISTING)
		return;
	this->setStartLine();
	this->setHeader();
	const std::string raw = this->_response.getRawStr();
	this->_sharedData->getBuffer().insert(this->_sharedData->getBuffer().begin(), raw.begin(), raw.end());
	this->_readSharedData =
		utils::shared_ptr<reactor::SharedData>(new reactor::SharedData(this->_fd, EVENT_READ, std::vector<char>()));
	if (this->_fd == FD_ZERO_) {
		this->setReadState(RESOLVE);
		this->_removed = true;
		return;
	}
	reactor::Dispatcher::getInstance()->registerIOHandler<reactor::FileReadHandlerFactory>(this->_readSharedData);
}

utils::shared_ptr<IBuilder<reactor::sharedData_t> > GetResponseBuilder::createGetResponseBuilder(
	const reactor::sharedData_t& sharedData, const request_t& request,
	const utils::shared_ptr<ServerConfig>& serverConfig, const utils::shared_ptr<LocationConfig>& locationConfig,
	SessionData* sessionData) {
	return utils::shared_ptr<IBuilder<reactor::sharedData_t> >(
		new GetResponseBuilder(sharedData, request, serverConfig, locationConfig, sessionData));
};

void GetResponseBuilder::handleSession() {
	HttpMessage& request = this->_request->second;
	std::string target = request.getRequestTarget();
	SessionData* sessionData = HttpSession::getInstance()->getSessionData(request.getSessionId());
	if (sessionData == u::nullptr_t)
		return;
	if (target == "/login.html") {
		throw RedirectResponseBuilder::createRedirectResponseBuilder(SEE_OTHER, "/", this->_sharedData, this->_request,
																	 this->_serverConfig);
	}
};
