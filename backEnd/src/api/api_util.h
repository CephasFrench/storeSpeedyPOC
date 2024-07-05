#ifndef API_UTIL_H
#define API_UTIL_H

#include <string>
#include <vector>
#include <json/json.h>
#include "../aisles/aisle.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
std::string performPostRequest(const std::string& url, struct curl_slist* headers, const std::string& jsonData);
void parseAndDisplayJson(const std::string& response);
void parseAisleNeighborsJson(const std::string& response, std::vector<Aisle>& neighbors);
void handleErrorResponse(const std::string& response);

#endif // API_UTIL_H
