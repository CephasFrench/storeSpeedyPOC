#include "api_util.h"
#include <string>

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
            //std::cout << "Response received: " << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize CURL" << std::endl;
    }

    return readBuffer;
}

std::string callGeminiApiWithItem(const std::string& item) {

    //std::string item = "walmart only items"; //testing
    const std::string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash-latest:generateContent?key=AIzaSyBVCsqwcySc3JqoOolB2J6lIhAInzQ82ag";
    std::string promptText = "Please respond to this prompt with a JSON object in the following format: {\"candidates\": [{\"content\": {\"parts\": [{\"text\": \"YES\"}]}}]}. The text should be 'YES' if HEB sells " + item + ", otherwise 'NO' and nothing else.";

    // Use Json::Value to construct the JSON data
    Json::Value root;
    Json::Value content;
    Json::Value parts;
    Json::Value text;

    text["text"] = promptText;
    parts.append(text);
    content["parts"] = parts;
    root["contents"].append(content);

    // Convert Json::Value to string
    Json::StreamWriterBuilder writer;
    std::string jsonData = Json::writeString(writer, root);

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    std::cout << "Performing post request to gemini with item..." << std::endl;
    std::string response = performPostRequest(url, headers, jsonData);

    if (!response.empty()) {
        //std::cout << "Response received: " << response << std::endl;
    } else {
        std::cerr << "No response received from the API." << std::endl;
    }

    curl_slist_free_all(headers);

    return response;
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
            //std::cerr << "Response received: " << response << std::endl;
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
