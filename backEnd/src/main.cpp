#include "crow_all.h"
#include "api/api_util.h"
#include <json/json.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>
#include <sstream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

extern std::string performPostRequest(const std::string& url, struct curl_slist* headers, const std::string& jsonData);
extern void parseAndDisplayJson(const std::string& response);
extern void handleErrorResponse(const std::string& response);

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/generate-route").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto jsonData = crow::json::load(req.body);
        if (!jsonData) {
            return crow::response(400, "Invalid JSON");
        }

        string location = jsonData["location"].s();
        auto groceryList = jsonData["groceryList"];

        // Example of generating a response
        crow::json::wvalue response;
        response["message"] = "Route generated successfully!";
        response["location"] = location;
        response["itemsReceived"] = groceryList.size();

        return crow::response(response);
    });

    CROW_ROUTE(app, "/hello").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto jsonData = crow::json::load(req.body);
        if (!jsonData) {
            return crow::response(400, "Invalid JSON");
        }

        string greeting = jsonData["greeting"].s();
        crow::json::wvalue response;
        response["message"] = "Hello, " + greeting;

        return crow::response(response);
    });

    app.port(8080).multithreaded().run();

    return 0;
}
