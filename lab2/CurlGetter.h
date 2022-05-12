#pragma once

#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <iostream>

class Curl
{
public:
	Curl(const char *URL);
	~Curl();
	std::string getJSONstring() const;
private:
	mutable CURL* m_CurlHandler;
	mutable CURLcode m_ResponceCode;
	const std::string URL;
};