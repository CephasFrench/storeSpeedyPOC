// StoreSpeedyJsonHandler.h
#ifndef STORESPEEDY_JSON_HANDLER_H
#define STORESPEEDY_JSON_HANDLER_H

#include <json/json.h> // Include JsonCpp library for JSON handling
#include <string>      // Include string for using string class
#include <vector>      // Include vector for using vector class

namespace StoreSpeedyJsonHandler {

// Function to read the content of a JSON file and return it as Json::Value
Json::Value readJsonFile(const std::string& filePath);

// Function to write Json::Value content to a JSON file
void writeJsonFile(const std::string& filePath, const Json::Value& jsonData);

// Function to ensure JSON structure for grocery list is correct
bool validateGroceryListJson(const Json::Value& jsonData);

// Function to ensure JSON structure for aisle data is correct
bool validateAisleDataJson(const Json::Value& jsonData);

// Function to get items from the grocery list JSON
std::vector<std::string> getItems(const Json::Value& jsonData);

// Function to add an item to the grocery list JSON
void addItem(Json::Value& jsonData, const std::string& newItem);

} // namespace StoreSpeedyJsonHandler

#endif // STORESPEEDY_JSON_HANDLER_H
