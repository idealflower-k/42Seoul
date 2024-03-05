#include "PostResponseBuilder.hpp"
#include "Login.hpp"
#include "SignUp.hpp"

PostResponseBuilder::PostResponseBuilder(reactor::sharedData_t sharedData, request_t request,
										 const utils::shared_ptr<ServerConfig>& serverConfig,
										 const utils::shared_ptr<LocationConfig>& locationConfig,
										 SessionData* sessionData)
	: _sharedData(sharedData),
	  _request(request),
	  _serverConfig(serverConfig),
	  _locationConfig(locationConfig),
	  _writeSharedData(),
	  _isExist(false),
	  _isRemoved(false),
	  _sessionData(sessionData),
	  _response(),
	  _path() {
	if (_sessionData)
		this->handleSession();
	this->prepare();
};

void PostResponseBuilder::handleSession(){};

PostResponseBuilder::~PostResponseBuilder() {
	reactor::FileCloseManager::getInstance()->closeFd(this->_fd);
}

reactor::sharedData_t PostResponseBuilder::getProduct() {
	return this->_sharedData;
}

void PostResponseBuilder::setPath(const std::string& target) {
	const std::string locPath = this->_locationConfig->getDirectives(ROOT).asString();
	const std::string serverPath = this->_serverConfig->getDirectives(ROOT).asString();

	if (access((locPath).c_str(), F_OK) == 0) {
		this->_path = locPath + target;
	} else if (access((serverPath).c_str(), F_OK) == 0) {
		this->_path = serverPath + target;
	} else {
		throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
			NOT_FOUND, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
	}
}

void PostResponseBuilder::doDefaultBehavior() {}

void PostResponseBuilder::divideEntryPoint() {
	std::string target = this->_request->second.getRequestTarget();

	if (target == "/signup")
		SignUp(this);
	if (target == "/login")
		Login(this);
}

void PostResponseBuilder::setStartLine() {
	this->_response.setStartLine(DefaultResponseBuilder::getInstance()->setDefaultStartLine(_isExist ? OK : CREATED));
}
void PostResponseBuilder::setHeader() {
	std::map<std::string, std::string> headers =
		DefaultResponseBuilder::getInstance()->setDefaultHeader(this->_serverConfig, this->_path);

	headers.erase("Content-Type");
	headers["Content-Length"] = "0";
	this->_response.setHeaders(headers);
}

bool PostResponseBuilder::setBody() {
	this->_writeSharedData->getBuffer().insert(this->_writeSharedData->getBuffer().end(),
											   this->_request->second.getBody().begin(),
											   this->_request->second.getBody().end());
	this->_request->second.getBody().clear();
	if ((this->_request->first == DONE || this->_request->first == LONG_BODY_DONE) &&
		this->_writeSharedData->getBuffer().empty() && _isRemoved == false) {
		this->_writeSharedData->setState(RESOLVE);
		reactor::Dispatcher::getInstance()->removeIOHandler(this->_writeSharedData->getFd(),
															this->_writeSharedData->getType());
		this->setStartLine();
		this->setHeader();
		const std::string raw = this->_response.getRawStr();
		this->_sharedData->getBuffer().insert(this->_sharedData->getBuffer().begin(), raw.begin(), raw.end());
		this->_request.get()->second.setContentLength(0);
		this->_request.get()->second.setContentLengthReceived(0);
		return true;
	}
	return false;
}

void PostResponseBuilder::reset() {
	this->_response.reset();
}

bool PostResponseBuilder::build() {
	if (this->_writeSharedData.get() == u::nullptr_t)
		return false;
	if (this->_writeSharedData->getState() == TERMINATE) {
		reactor::Dispatcher::getInstance()->removeIOHandler(this->_writeSharedData->getFd(),
															this->_writeSharedData->getType());
		this->_sharedData->setState(TERMINATE);
		return false;
	}
	if ((this->_request->first == HTTP_ERROR || this->_request->first == LONG_BODY_ERROR ||
		 this->_request->first == CHUNKED_ERROR) &&
		_isRemoved == false) {
		std::remove(this->_path.c_str());
		_isRemoved = true;
		reactor::Dispatcher::getInstance()->removeIOHandler(this->_writeSharedData->getFd(),
															this->_writeSharedData->getType());
		throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(
			new ErrorResponseBuilder(this->_request->second.getErrorCode(), this->_sharedData, this->_request,
									 this->_serverConfig, this->_locationConfig));
	}
	return this->setBody();
}

void PostResponseBuilder::prepare() {
	this->divideEntryPoint();
	const std::string& target = this->_request->second.getRequestTarget();
	if (target[target.size() - 1] == '/')
		throw utils::shared_ptr<IBuilder<reactor::sharedData_t> >(new ErrorResponseBuilder(
			UNSUPPORTED_MEDIA_TYPE, this->_sharedData, this->_request, this->_serverConfig, this->_locationConfig));
	const std::string targetFile =
		utils::removeSubstring(this->_request->second.getRequestTarget(), this->_locationConfig->getPath());
	this->setPath(targetFile);
	if (checkFileMode(this->_path) == MODE_FILE)
		this->_isExist = true;
	else
		this->_isExist = false;
	this->_fd = reactor::FileCloseManager::getInstance()->makeFd(this->_path, "w");
	if (this->_fd == FD_ERROR)
		throw ErrorResponseBuilder::createErrorResponseBuilder(NOT_FOUND, this->_sharedData, this->_request,
															   this->_serverConfig, this->_locationConfig);
	this->_writeSharedData =
		utils::shared_ptr<reactor::SharedData>(new reactor::SharedData(_fd, EVENT_WRITE, std::vector<char>()));
	reactor::Dispatcher::getInstance()->registerIOHandler<reactor::FileWriteHandlerFactory>(this->_writeSharedData);
}

utils::shared_ptr<IBuilder<reactor::sharedData_t> > PostResponseBuilder::createPostResponseBuilder(
	const reactor::sharedData_t& sharedData, const request_t& request,
	const utils::shared_ptr<ServerConfig>& serverConfig, const utils::shared_ptr<LocationConfig>& locationConfig,
	SessionData* sessionData) {
	return utils::shared_ptr<IBuilder<reactor::sharedData_t> >(
		new PostResponseBuilder(sharedData, request, serverConfig, locationConfig, sessionData));
}
