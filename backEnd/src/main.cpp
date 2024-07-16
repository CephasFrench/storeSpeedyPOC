#include "crow_all.h"
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <string>

std::string readJsonFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/compute_path").methods("GET"_method)
    ([]() {
        std::string filePath = "/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src/aisle_data.json";
        try {
            std::string jsonData = readJsonFile(filePath);
            return crow::response{jsonData};
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
    });

    app.port(8080).multithreaded().run();
}
