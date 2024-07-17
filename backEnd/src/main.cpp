#include "crow_all.h"  // Include Crow library for building the web server
#include <json/json.h> // Include JsonCpp library for JSON handling
#include <fstream>     // Include fstream for file operations
#include <iostream>    // Include iostream for standard input-output stream
#include <string>      // Include string for using string class

std::string currentLocation = "Default";  // Server-side variable to track the chosen location

// Function to read the content of a JSON file and return it as a string
std::string readJsonFile(const std::string& filePath) {
    std::ifstream file(filePath);  // Open the file at the given file path
    if (!file.is_open()) {  // Check if the file is open, if not, throw an error
        throw std::runtime_error("Could not open file: " + filePath);
    }

    // Read the content of the file into a string
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;  // Return the content of the file
}

// Function to write the content to a JSON file
void writeJsonFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);  // Open the file at the given file path
    if (!file.is_open()) {  // Check if the file is open, if not, throw an error
        throw std::runtime_error("Could not open file: " + filePath);
    }
    file << content;  // Write the content to the file
}

int main() {
    crow::SimpleApp app;  // Create a Crow application

    // Define a route for the endpoint "/compute_path" with GET method
    CROW_ROUTE(app, "/compute_path").methods("GET"_method)
    ([]() {
        std::string filePath = "/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src/aisle_data.json";  // File path to the JSON data
        try {
            // Read JSON data from the file
            std::string jsonData = readJsonFile(filePath);
            return crow::response{jsonData};  // Return the JSON data as the response
        } catch (const std::exception& e) {
            // If an error occurs, return a 500 response with the error message
            return crow::response(500, e.what());
        }
    });

    // Endpoint to update aisle data with POST method
    CROW_ROUTE(app, "/update_aisle_data").methods("POST"_method)
    ([](const crow::request& req) {
        std::string filePath = "/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src/aisle_data.json";  // File path to the JSON data
        try {
            // Write the received JSON data to the file
            writeJsonFile(filePath, req.body);
            return crow::response(200);
        } catch (const std::exception& e) {
            // If an error occurs, return a 500 response with the error message
            return crow::response(500, e.what());
        }
    });

    // Endpoint to handle server ping
    CROW_ROUTE(app, "/ping").methods("GET"_method)
    ([]() {
        return crow::response(200, "Pong");
    });

    // Endpoint to update the current location
    CROW_ROUTE(app, "/update_location").methods("POST"_method)
    ([](const crow::request& req) {
        try {
            auto jsonBody = crow::json::load(req.body);
            if (!jsonBody) {
                return crow::response(400, "Invalid JSON");
            }
            currentLocation = jsonBody["location"].s();
            return crow::response(200);
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
    });

    // Run the Crow application on port 8080 with multithreading enabled
    app.port(8080).multithreaded().run();
}
