#pragma once
#ifndef CGIRESPONSEBUILDER_HPP
#define CGIRESPONSEBUILDER_HPP

#include "CgiResponseBuilder.h"

// sharedData의 fd는 클라이언트의 fd 이다.

class CgiResponseBuilder : public IBuilder<reactor::sharedData_t> {
   private:
	reactor::sharedData_t _sharedData;
	const request_t _request;
	const utils::shared_ptr<ServerConfig> _serverConfig;
	const utils::shared_ptr<LocationConfig> _locationConfig;
	std::string _cgiFullPath;
	std::map<std::string, std::string> _interpreterMap;
	int _sv[2];
	int _writePipe[2];
	int _readPipe[2];
	int _pipes[4];
	pid_t _cgiPid;
	bool _unchunkedState;
	bool _forked;

	reactor::sharedData_t _cgiWriteSharedData;
	reactor::sharedData_t _cgiReadSharedData;
	reactor::sharedData_t _cgiExitSharedData;
	HttpMessage _response;
	std::string _startLine[3];
	bool _startLineState;
	bool _contentLengthState;
	std::vector<char> _pendingBuf;
	std::time_t _cgiTime;
	SessionData* _sessionData;

	CgiResponseBuilder(const CgiResponseBuilder& obj);
	CgiResponseBuilder& operator=(const CgiResponseBuilder& obj);

	void setEnvpSessionData(std::vector<std::string>& cgiEnvpVec);
	std::string makeCgiFullPath();
	bool makePipes();
	void makeWriteSharedData();
	bool makeunChunked();
	bool doFork();
	char** setEnvp();
	std::string makeQueryString();
	std::string makeUriPath();
	std::string makePathInfo();
	char** makeArgs();
	std::string makeInterpreter();
	std::string makeExtension();
	std::vector<std::string> parsPathEnvp();
	void inItInterpreterMap();
	void checkContentLength();
	void replaceStartLine();
	void cgiStartLineInsert();
	void addCgiEnvp(std::vector<std::string>& cgiEnvpVec, const std::string& key, const std::string& value);
	void setClientHeaders(std::vector<std::string>& cgiEnvVec);
	void makeHttpHeaders(std::string& key);
	std::string makePathTranslated();

	void cleanPipes();
	void removeIOHandlers();
	void removeReadIO();
	void removeWriteIO();

   public:
	CgiResponseBuilder(reactor::sharedData_t sharedData, request_t request,
					   const utils::shared_ptr<ServerConfig>& serverConfig,
					   const utils::shared_ptr<LocationConfig>& locationConfig);
	CgiResponseBuilder(reactor::sharedData_t sharedData, request_t request,
					   const utils::shared_ptr<ServerConfig>& serverConfig,
					   const utils::shared_ptr<LocationConfig>& locationConfig, SessionData* sessionData);
	~CgiResponseBuilder();

	static utils::shared_ptr<IBuilder<reactor::sharedData_t> > createCgiResponseBuilder(
		const reactor::sharedData_t& sharedData, const request_t& request,
		const utils::shared_ptr<ServerConfig>& serverConfig, const utils::shared_ptr<LocationConfig>& locationConfig);

	static utils::shared_ptr<IBuilder<reactor::sharedData_t> > createCgiResponseBuilder(
		const reactor::sharedData_t& sharedData, const request_t& request,
		const utils::shared_ptr<ServerConfig>& serverConfig, const utils::shared_ptr<LocationConfig>& locationConfig,
		SessionData* sessionData);

	virtual enum AsyncState getReadState() const { return this->_cgiReadSharedData.get()->getState(); }
	virtual void setReadState(enum AsyncState state) { this->_cgiReadSharedData.get()->setState(state); }
	virtual reactor::sharedData_t getProduct();
	virtual void setStartLine();
	virtual void setHeader();
	virtual bool setBody();
	virtual void reset();
	virtual void prepare();
	virtual bool build();
};

// Start Line: GET / HTTP/1.1
// Headers:
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
// Accept-Encoding: gzip, deflate
// Accept-Language: en-us
// Connection: keep-alive
// Host: localhost:4240
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/15.6.1 Safari/605.1.15
// Body:
// Error Code: 0

#endif
