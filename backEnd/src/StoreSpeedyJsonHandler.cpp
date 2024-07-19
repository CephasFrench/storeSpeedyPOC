// StoreSpeedyJsonHandler.cpp
#include "StoreSpeedyJsonHandler.h"
#include "aisle.h"
#include "config.h"
#include <fstream>     // Include fstream for file operations
#include <stdexcept>   // Include stdexcept for runtime error handling
#include <iostream>

namespace StoreSpeedyJsonHandler {

Json::Value readJsonFile(const std::string& filePath) { // More efficient use of fstream
    if(LOG_FUNC_CALLS) {
        std::cout << "readJsonFile() called" << std:: endl;
    }
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    // Read the file into a stringstream for more efficient parsing
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    // Close the file
    file.close();

    // Parse the JSON data
    Json::Value jsonData;
    buffer >> jsonData;

    return jsonData;
}

void writeJsonFile(const std::string& filePath, const Json::Value& jsonData) {
    if(LOG_FUNC_CALLS) {
        std::cout << "writeJsonFile() called" << std:: endl;
    }
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    file << jsonData;
}

bool validateGroceryListJson(const Json::Value& jsonData) {
    return jsonData.isMember("items") && jsonData["items"].isArray();
}

bool validateAisleDataJson(const Json::Value& jsonData) {
    // Define validation logic for aisle data
    // For example:
    return jsonData.isObject(); // Simplified example
}

std::vector<std::string> getItems(const Json::Value& jsonData) {
    std::vector<std::string> items;
    if (validateGroceryListJson(jsonData)) {
        for (const auto& item : jsonData["items"]) {
            items.push_back(item.asString());
        }
    } else {
        throw std::runtime_error("Invalid grocery list JSON structure.");
    }
    return items;
}

void addItem(Json::Value& jsonData, const std::string& newItem) {
    if (validateGroceryListJson(jsonData)) {
        jsonData["items"].append(newItem);
    } else {
        throw std::runtime_error("Invalid grocery list JSON structure.");
    }
}


void parseAndDisplayJson(const std::string& response)
{
    if(LOG_FUNC_CALLS) {
        std::cout << "parseAndDisplayJson() called" << std:: endl;
    }
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
    if(LOG_FUNC_CALLS) {
        std::cout << "parseAisleNeighborsJson() called" << std:: endl;
    }
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

} // namespace StoreSpeedyJsonHandler
