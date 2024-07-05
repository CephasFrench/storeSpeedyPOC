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

const int MAX_RETRIES = 1;
const string API_KEY = "AIzaSyBVCsqwcySc3JqoOolB2J6lIhAInzQ82ag";
const string URL = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash-latest:generateContent?key=" + API_KEY;

bool PERFORM_GENERAL_CALL = true; // Perform general API call when true

int main() {
    cout << "Starting main function..." << endl;

    if (PERFORM_GENERAL_CALL) {
        const string jsonData = R"({
            "contents": [
                {
                    "parts": [
                        {
                            "text": "Please respond to this prompt with a JSON object in the following format: {\"greeting\": \"Hello!\", \"timestamp\": \"<current date and time>\", \"status\": \"success\"}. Additionally, please provide a message about what you did to answer the prompt for debugging purposes."
                        }
                    ]
                }
            ]
        })";

        curl_global_init(CURL_GLOBAL_DEFAULT);
        struct curl_slist* headers = curl_slist_append(NULL, "Content-Type: application/json");

        if (!headers) {
            cerr << "Failed to set HTTP headers" << endl;
            return 1;
        }

        cout << "Performing general API call..." << endl;
        string response = performPostRequest(URL, headers, jsonData);
        if (!response.empty()) {
            cout << "General API call response: " << response << endl;
            parseAndDisplayJson(response);
        } else {
            cerr << "Empty response received" << endl;
            handleErrorResponse(response);
        }

        curl_slist_free_all(headers);
    }

    cout << "Cleaning up..." << endl;
    curl_global_cleanup();

    cout << "Program completed." << endl;
    return 0;
}
