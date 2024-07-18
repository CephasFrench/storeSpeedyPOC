// StoreSpeedyJsonHandler.h
#ifndef STORESPEEDY_JSON_HANDLER_H
#define STORESPEEDY_JSON_HANDLER_H

#include <json/json.h> // Include JsonCpp library for JSON handling
#include <fstream>     // Include fstream for file operations
#include <string>      // Include string for using string class
#include <stdexcept>   // Include stdexcept for runtime error handling

namespace StoreSpeedyJsonHandler {

// Function to read the content of a JSON file and return it as Json::Value
Json::Value readJsonFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    Json::Value jsonData;
    file >> jsonData;
    return jsonData;
}

// Function to write Json::Value content to a JSON file
void writeJsonFile(const std::string& filePath, const Json::Value& jsonData) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    file << jsonData;
}

// Function to ensure JSON structure for grocery list is correct
bool validateGroceryListJson(const Json::Value& jsonData) {
    return jsonData.isMember("items") && jsonData["items"].isArray();
}

// Function to ensure JSON structure for aisle data is correct
bool validateAisleDataJson(const Json::Value& jsonData) {
    // Define validation logic for aisle data
    // For example:
    return jsonData.isObject(); // Simplified example
}

// Function to get items from the grocery list JSON
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

// Function to add an item to the grocery list JSON
void addItem(Json::Value& jsonData, const std::string& newItem) {
    if (validateGroceryListJson(jsonData)) {
        jsonData["items"].append(newItem);
    } else {
        throw std::runtime_error("Invalid grocery list JSON structure.");
    }
}

} // namespace StoreSpeedyJsonHandler

#endif // STORESPEEDY_JSON_HANDLER_H
