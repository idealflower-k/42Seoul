#pragma once
#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

#include "LocationConfig.h"

class ServerConfig;

class LocationConfig : public AConfig {
   private:
	utils::shared_ptr<ServerConfig> _parent;
	std::string _path;

   public:
	LocationConfig();
	LocationConfig(utils::shared_ptr<ServerConfig> parent);
	LocationConfig(const LocationConfig& other);
	~LocationConfig();
	LocationConfig& operator=(const LocationConfig& other);

	virtual void setDirectives(const std::string& directive, const std::vector<std::string>& values);
	virtual void setErrorPage(const std::vector<std::string>& values);
	virtual std::string getErrorPage(unsigned int error_code) const;
	virtual ConfigValue getDirectives(Directives method) const;
	utils::shared_ptr<ServerConfig> getParent();
	std::string getOwnRoot();
	std::vector<std::string> getOwnIndex();
	bool getOwnConfirmedMethods(Directives method);
	bool isCgi();
	bool isRedirect();
	std::string getMimeTypes(const std::string& extension) const;
	std::string getPath() const;
	void setPath(const std::string& path);
};

#endif	// LOCATIONCONFIG_HPP
