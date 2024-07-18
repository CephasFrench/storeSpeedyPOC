#include "crow_all.h"
#include "StoreSpeedyJsonHandler.h"
#include "api_util.h"
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <iostream>

std::string currentLocation = "DefaultLoc";  // Server-side variable to track the chosen location
const std::string storagePath = "/Users/cameronhardin/Desktop/storeSpeedyPOC/server/storage/";

void defineRoutes(crow::SimpleApp& app);
void ensureDirectoryExists(const std::string& dir);
void ensureFileExists(const std::string& filePath, const Json::Value& defaultValue);
crow::response handleError(const std::exception& e);
Json::Value readJsonData(const std::string& filePath, const Json::Value& defaultValue);
void validateGroceryListJson(const Json::Value& jsonData);
void addItemToGroceryList(const std::string& userId, const std::string& location, const std::string& item);

int main() {
    crow::SimpleApp app;  // Create a Crow application
    defineRoutes(app);
    app.port(8080).multithreaded().run();  // Run the Crow application on port 8080 with multithreading enabled
}

// Function to ensure directory exists
void ensureDirectoryExists(const std::string& dir) {
    std::ifstream file(dir.c_str());
    if (!file) {
        std::system(("mkdir -p " + dir).c_str());
    }
}

// Ensure file exists and create with default value if not
void ensureFileExists(const std::string& filePath, const Json::Value& defaultValue) {
    std::ifstream file(filePath);
    if (!file.good()) {
        std::ofstream outFile(filePath);
        outFile << defaultValue.toStyledString();
        outFile.close();
    }
}

// Handle errors and create a response
crow::response handleError(const std::exception& e) {
    return crow::response(500, e.what());
}

// Read JSON data from a file
Json::Value readJsonData(const std::string& filePath, const Json::Value& defaultValue) {
    ensureFileExists(filePath, defaultValue);
    return StoreSpeedyJsonHandler::readJsonFile(filePath);
}

// Validate JSON structure for grocery list
void validateGroceryListJson(const Json::Value& jsonData) {
    if (!jsonData.isMember("items") || !jsonData["items"].isArray()) {
        throw std::runtime_error("Invalid JSON structure: 'items' key missing or not an array.");
    }
}

// Function to add an item to the grocery list
void addItemToGroceryList(const std::string& userId, const std::string& location, const std::string& item) {
    std::string filePath = storagePath + "users/" + userId + "/" + location + "_grocery_list.json";
    Json::Value defaultGroceryList = Json::objectValue;
    defaultGroceryList["items"] = Json::arrayValue;
    Json::Value groceryList = readJsonData(filePath, defaultGroceryList);

    groceryList["items"].append(item);
    StoreSpeedyJsonHandler::writeJsonFile(filePath, groceryList);
}

// Define routes and their handlers
void defineRoutes(crow::SimpleApp& app) {
    // Compute path endpoint
    CROW_ROUTE(app, "/compute_path").methods("GET"_method)
    ([]() {
        std::string filePath = storagePath + "locations/" + currentLocation + "/aisles/aisle_data.json";
        try {
            Json::Value jsonData = readJsonData(filePath, Json::Value(Json::objectValue));
            return crow::response{jsonData.toStyledString()};
        } catch (const std::exception& e) {
            return handleError(e);
        }
    });

    // Update aisle data endpoint
    CROW_ROUTE(app, "/update_aisle_data").methods("POST"_method)
    ([](const crow::request& req) {
        std::string filePath = storagePath + "locations/" + currentLocation + "/aisles/aisle_data.json";
        try {
            Json::Value jsonData;
            std::istringstream iss(req.body);
            Json::CharReaderBuilder rbuilder;
            std::string errs;
            if (!Json::parseFromStream(rbuilder, iss, &jsonData, &errs)) {
                return crow::response(400, "Invalid JSON");
            }
            if (!StoreSpeedyJsonHandler::validateAisleDataJson(jsonData)) {
                return crow::response(400, "Invalid JSON structure for aisle data");
            }
            StoreSpeedyJsonHandler::writeJsonFile(filePath, jsonData);
            return crow::response(200);
        } catch (const std::exception& e) {
            return handleError(e);
        }
    });

    // Ping endpoint
    CROW_ROUTE(app, "/ping").methods("GET"_method)
    ([]() {
        return crow::response(200, "Pong");
    });

    // Update location endpoint
    CROW_ROUTE(app, "/update_location").methods("POST"_method)
    ([](const crow::request& req) {
        try {
            Json::Value jsonBody;
            std::istringstream iss(req.body);
            Json::CharReaderBuilder rbuilder;
            std::string errs;
            if (!Json::parseFromStream(rbuilder, iss, &jsonBody, &errs)) {
                return crow::response(400, "Invalid JSON");
            }
            if (!jsonBody.isMember("location")) {
                return crow::response(400, "Invalid JSON");
            }
            currentLocation = jsonBody["location"].asString();
            return crow::response(200);
        } catch (const std::exception& e) {
            return handleError(e);
        }
    });

    // Get user's grocery list endpoint
    CROW_ROUTE(app, "/grocery_list/<string>/<string>").methods("GET"_method)
    ([](const std::string& userId, const std::string& location) {
        std::string filePath = storagePath + "users/" + userId + "/" + location + "_grocery_list.json";
        try {
            Json::Value defaultGroceryList = Json::objectValue;
            defaultGroceryList["items"] = Json::arrayValue;
            Json::Value jsonData = readJsonData(filePath, defaultGroceryList);
            validateGroceryListJson(jsonData);
            return crow::response{jsonData.toStyledString()};
        } catch (const std::exception& e) {
            return handleError(e);
        }
    });

    // Update user's grocery list endpoint
    CROW_ROUTE(app, "/update_grocery_list/<string>/<string>").methods("POST"_method)
    ([](const crow::request& req, const std::string& userId, const std::string& location) {
        std::string filePath = storagePath + "users/" + userId + "/" + location + "_grocery_list.json";
        try {
            Json::Value jsonData;
            std::istringstream iss(req.body);
            Json::CharReaderBuilder rbuilder;
            std::string errs;
            if (!Json::parseFromStream(rbuilder, iss, &jsonData, &errs)) {
                return crow::response(400, "Invalid JSON");
            }
            validateGroceryListJson(jsonData);
            StoreSpeedyJsonHandler::writeJsonFile(filePath, jsonData);
            return crow::response(200);
        } catch (const std::exception& e) {
            return handleError(e);
        }
    });

    // Test endpoint for validating grocery list
    CROW_ROUTE(app, "/check_item").methods("POST"_method)
    ([](const crow::request& req) {
        Json::Value jsonBody;
        Json::CharReaderBuilder rbuilder;
        std::string errs;
        std::istringstream iss(req.body);
        if (!Json::parseFromStream(rbuilder, iss, &jsonBody, &errs)) {
            return crow::response(400, "Invalid JSON");
        }
        if (!jsonBody.isMember("item")) {
            return crow::response(400, "Missing 'item' field");
        }
        std::string item = jsonBody["item"].asString();
        std::string response = callGeminiApiWithItem(item);

        // Log the response received from the API
        std::cout << "Gemini API response: " << response << std::endl;

        // Parse the response to check if the item is available
        Json::CharReaderBuilder readerBuilder;
        Json::Value jsonResponse;
        std::string parseErrors;
        std::istringstream responseStream(response);
        if (Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &parseErrors)) {
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

                        // Parse the cleaned JSON text
                        Json::Value nestedJson;
                        std::istringstream nestedStream(text);
                        if (Json::parseFromStream(readerBuilder, nestedStream, &nestedJson, &parseErrors)) {
                            if (nestedJson.isObject() && nestedJson.isMember("candidates")) {
                                const Json::Value& nestedCandidates = nestedJson["candidates"];
                                if (nestedCandidates.isArray() && !nestedCandidates.empty()) {
                                    const Json::Value& nestedContent = nestedCandidates[0]["content"]["parts"];
                                    if (nestedContent.isArray() && !nestedContent.empty()) {
                                        std::string nestedText = nestedContent[0]["text"].asString();
                                        std::cout << "Parsed nested text: " << nestedText << std::endl;
                                        if (nestedText == "YES") {
                                            addItemToGroceryList("default", currentLocation, item); // Add item to the grocery list
                                            return crow::response("YES");
                                        } else {
                                            return crow::response("NO");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        std::cerr << "Failed to parse Gemini API response: " << parseErrors << std::endl;
        return crow::response(400, "Failed to parse response.");
    });


}
