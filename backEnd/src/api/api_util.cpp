#include "api_util.h"
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <fstream>
#include <vector>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string performPostRequest(const std::string& url, struct curl_slist* headers, const std::string& jsonData)
{
    CURL* curl = curl_easy_init();
    CURLcode res;
    std::string readBuffer;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "API successfully called with the prompt." << std::endl;
            std::cout << "Response received: " << readBuffer << std::endl; // Print the raw response
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize CURL" << std::endl;
    }

    return readBuffer;
}

void handleErrorResponse(const std::string& response)
{
    Json::CharReaderBuilder readerBuilder;
    Json::Value jsonResponse;
    std::string errors;

    std::istringstream responseStream(response);
    if (Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errors)) {
        if (jsonResponse.isObject() && jsonResponse.isMember("error")) {
            int errorCode = jsonResponse["error"]["code"].asInt();
            std::string errorMessage = jsonResponse["error"]["message"].asString();
            std::cerr << "Error received: " << errorMessage << std::endl;

            switch (errorCode) {
                case 400:
                    std::cerr << "Invalid Argument: The request body is malformed." << std::endl;
                    break;
                case 403:
                    std::cerr << "Permission Denied: Your API key doesn't have the required permissions." << std::endl;
                    break;
                case 404:
                    std::cerr << "Not Found: The requested resource wasn't found." << std::endl;
                    break;
                case 429:
                    std::cerr << "Resource Exhausted: You've exceeded the rate limit." << std::endl;
                    break;
                case 500:
                    std::cerr << "Internal Error: An unexpected error occurred on Google's side." << std::endl;
                    break;
                case 503:
                    std::cerr << "Service Unavailable: The service may be temporarily overloaded or down." << std::endl;
                    break;
                default:
                    std::cerr << "Unknown Error: Please check the error code and message for more details." << std::endl;
                    break;
            }
        } else {
            std::cerr << "Failed to parse error response: " << errors << std::endl;
        }
    }
}

void parseAndDisplayJson(const std::string& response)
{
    std::cout << "Parsing general JSON response." << std::endl;
    Json::CharReaderBuilder readerBuilder;
    Json::Value jsonResponse;
    std::string errors;

    std::istringstream responseStream(response);
    if (Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errors)) {
        if (jsonResponse.isObject() && jsonResponse.isMember("candidates")) {
            const Json::Value& candidates = jsonResponse["candidates"];
            if (candidates.isArray() && !candidates.empty()) {
                const Json::Value& content = candidates[0]["content"]["parts"];
                if (content.isArray() && !content.empty()) {
                    std::string text = content[0]["text"].asString();

                    // Remove backticks and "json" keyword
                    size_t firstBacktick = text.find("```json\n");
                    if (firstBacktick != std::string::npos) {
                        text.erase(firstBacktick, 7); // Remove "```json\n"
                    }
                    size_t lastBacktick = text.rfind("\n```");
                    if (lastBacktick != std::string::npos) {
                        text.erase(lastBacktick, 4); // Remove "\n```"
                    }

                    // Separate the debugging message if present
                    size_t debugMsgPos = text.find("\n\n");
                    std::string debugMessage;
                    if (debugMsgPos != std::string::npos) {
                        debugMessage = text.substr(debugMsgPos + 2);
                        text = text.substr(0, debugMsgPos);
                    }

                    // Parse the cleaned JSON text
                    std::istringstream cleanedStream(text);
                    if (Json::parseFromStream(readerBuilder, cleanedStream, &jsonResponse, &errors)) {
                        if (jsonResponse.isObject()) {
                            std::cout << "Parsed JSON: " << jsonResponse.toStyledString() << std::endl;
                            if (!debugMessage.empty()) {
                                std::cout << "Debugging message: " << debugMessage << std::endl;
                            }
                        } else {
                            std::cerr << "Invalid JSON format received: " << text << std::endl;
                        }
                    } else {
                        std::cerr << "Failed to parse cleaned JSON response: " << errors << std::endl;
                        std::cerr << "Cleaned response received: " << text << std::endl;
                    }
                } else {
                    std::cerr << "No parts found in content: " << response << std::endl;
                }
            } else {
                std::cerr << "No candidates found in response: " << response << std::endl;
            }
        } else {
            std::cerr << "Failed to parse JSON response: " << errors << std::endl;
            std::cerr << "Response received: " << response << std::endl;
        }
    }
}

void parseAisleNeighborsJson(const std::string& response, std::vector<Aisle>& neighbors)
{
    std::cout << "Parsing aisle neighbors JSON response." << std::endl;
    Json::CharReaderBuilder readerBuilder;
    Json::Value jsonResponse;
    std::string errors;

    std::istringstream responseStream(response);
    if (Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errors)) {
        if (jsonResponse.isObject() && jsonResponse.isMember("candidates")) {
            const Json::Value& candidates = jsonResponse["candidates"];
            if (candidates.isArray() && !candidates.empty()) {
                const Json::Value& content = candidates[0]["content"]["parts"];
                if (content.isArray() && !content.empty()) {
                    std::string text = content[0]["text"].asString();

                    // Remove backticks and "json" keyword
                    size_t firstBacktick = text.find("```json\n");
                    if (firstBacktick != std::string::npos) {
                        text.erase(firstBacktick, 7); // Remove "```json\n"
                    }
                    size_t lastBacktick = text.rfind("\n```");
                    if (lastBacktick != std::string::npos) {
                        text.erase(lastBacktick, 4); // Remove "\n```"
                    }

                    // Separate the debugging message if present
                    size_t debugMsgPos = text.find("\n\n");
                    std::string debugMessage;
                    if (debugMsgPos != std::string::npos) {
                        debugMessage = text.substr(debugMsgPos + 2);
                        text = text.substr(0, debugMsgPos);
                    }

                    // Parse the cleaned JSON text
                    Json::Value cleanedJsonResponse;
                    std::istringstream cleanedStream(text);
                    if (Json::parseFromStream(readerBuilder, cleanedStream, &cleanedJsonResponse, &errors)) {
                        if (cleanedJsonResponse.isObject()) {
                            for (const auto& key : cleanedJsonResponse.getMemberNames()) {
                                Aisle aisle;
                                aisle.num = std::stoi(key);
                                const Json::Value& items = cleanedJsonResponse[key];
                                if (items.isArray()) {
                                    for (const auto& item : items) {
                                        Aisle neighbor;
                                        neighbor.num = item.asInt();
                                        aisle.addNeighbor(neighbor);
                                    }
                                    neighbors.push_back(aisle);
                                } else {
                                    std::cerr << "Items for aisle " << key << " are not an array: " << items << std::endl;
                                }
                            }
                            if (!debugMessage.empty()) {
                                std::cout << "Debugging message: " << debugMessage << std::endl;
                            }
                        } else {
                            std::cerr << "Invalid JSON format received: " << text << std::endl;
                        }
                    } else {
                        std::cerr << "Failed to parse cleaned JSON response: " << errors << std::endl;
                        std::cerr << "Cleaned response received: " << text << std::endl;
                    }
                } else {
                    std::cerr << "No parts found in content: " << response << std::endl;
                }
            } else {
                std::cerr << "No candidates found in response: " << response << std::endl;
            }
        } else {
            std::cerr << "Failed to parse JSON response: " << errors << std::endl;
            std::cerr << "Response received: " << response << std::endl;
        }
    }
}

std::string pdfToBase64(const std::string& pdfFilePath)
{
    std::ifstream file(pdfFilePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open PDF file.");
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return base64_encode(reinterpret_cast<const unsigned char*>(buffer.data()), buffer.size());
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }

    return ret;
}
