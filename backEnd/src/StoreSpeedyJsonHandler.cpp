// StoreSpeedyJsonHandler.cpp
#include "StoreSpeedyJsonHandler.h"
#include <fstream>     // Include fstream for file operations
#include <stdexcept>   // Include stdexcept for runtime error handling

namespace StoreSpeedyJsonHandler {

Json::Value readJsonFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    Json::Value jsonData;
    file >> jsonData;
    return jsonData;
}

void writeJsonFile(const std::string& filePath, const Json::Value& jsonData) {
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

} // namespace StoreSpeedyJsonHandler
