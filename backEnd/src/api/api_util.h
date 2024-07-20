#ifndef API_UTIL_H
#define API_UTIL_H

#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <json/json.h>
#include <vector>
#include "aisle.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
std::string performPostRequest(const std::string& url, struct curl_slist* headers, const std::string& jsonData);
void handleErrorResponse(const std::string& response);
std::string callGeminiApiWithItem(const std::string& item);

#endif // API_UTIL_H
