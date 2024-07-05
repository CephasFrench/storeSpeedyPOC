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
std::string pdfToBase64(const std::string& pdfFilePath);
std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);

#endif // API_UTIL_H
