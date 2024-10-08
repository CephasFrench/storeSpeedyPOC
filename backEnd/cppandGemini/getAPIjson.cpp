/*
    Author: Cameron Hardin
    Date Created:  6/12/24
    Last Modified: 7/3/24

    NOTES:
    To run this program, simply go into the directory where build.sh is and run ./build.sh

    Prompt URL: 
    Project #: 804895084036
    API Key:   AIzaSyBVCsqwcySc3JqoOolB2J6lIhAInzQ82ag
*/

#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <sstream>

using std::cerr; 
using std::cin;
using std::cout;
using std::endl;
using std::string;

/**
 * @brief Callback function to write data to a string.
 *
 * This function appends the received data to the string pointed to by userp.
 *
 * @param contents Pointer to the delivered data.
 * @param size Size of a single data element.
 * @param nmemb Number of data elements.
 * @param userp Pointer to the user-defined data (string in this case).
 * @return size_t The number of bytes processed.
 */
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/**
 * @brief Function to perform an HTTP POST request using libcurl.
 *
 * This function initializes the libcurl library, sets up the CURL handle,
 * performs an HTTP POST request, and handles the response.
 *
 * @param url The URL to send the request to.
 * @param headers A list of headers to include in the request.
 * @param jsonData The JSON data to send in the POST request.
 * @return string The response data received from the request.
 */
string performPostRequest(const string& url, struct curl_slist* headers, const string& jsonData)
{
    CURL* curl = curl_easy_init();
    CURLcode res;
    string readBuffer;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } else {
            cout << "API successfully called with the prompt." << endl;
            cout << "Response received: " << readBuffer << endl; // Print the raw response
        }

        curl_easy_cleanup(curl);
    } else {
        cerr << "Failed to initialize CURL" << endl;
    }

    return readBuffer;
}

/**
 * @brief Function to parse and display the JSON response.
 *
 * @param response The JSON response to parse and display.
 */
void parseAndDisplayJson(const string& response)
{
    Json::CharReaderBuilder readerBuilder;
    Json::Value jsonResponse;
    string errors;

    std::istringstream responseStream(response);
    if (Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errors)) {
        if (jsonResponse.isObject() && jsonResponse.isMember("candidates")) {
            const Json::Value& candidates = jsonResponse["candidates"];
            if (candidates.isArray() && !candidates.empty()) {
                const Json::Value& content = candidates[0]["content"]["parts"];
                if (content.isArray() && !content.empty()) {
                    string text = content[0]["text"].asString();
                    
                    // Remove backticks and "json" keyword
                    size_t firstBacktick = text.find("```json\n");
                    if (firstBacktick != string::npos) {
                        text.erase(firstBacktick, 7); // Remove "```json\n"
                    }
                    size_t lastBacktick = text.rfind("\n```");
                    if (lastBacktick != string::npos) {
                        text.erase(lastBacktick, 4); // Remove "\n```"
                    }
                    
                    // Parse the cleaned JSON text
                    std::istringstream cleanedStream(text);
                    if (Json::parseFromStream(readerBuilder, cleanedStream, &jsonResponse, &errors)) {
                        if (jsonResponse.isObject() && jsonResponse.isMember("greeting") && jsonResponse.isMember("timestamp") && jsonResponse.isMember("status")) {
                            cout << "Greeting: " << jsonResponse["greeting"].asString() << endl;
                            cout << "Timestamp: " << jsonResponse["timestamp"].asString() << endl;
                            cout << "Status: " << jsonResponse["status"].asString() << endl;
                        } else {
                            cerr << "Invalid JSON format received: " << text << endl;
                        }
                    } else {
                        cerr << "Failed to parse cleaned JSON response: " << errors << endl;
                        cerr << "Cleaned response received: " << text << endl;
                    }
                } else {
                    cerr << "No parts found in content: " << response << endl;
                }
            } else {
                cerr << "No candidates found in response: " << response << endl;
            }
        } else {
            cerr << "Failed to parse JSON response: " << errors << endl;
            cerr << "Response received: " << response << endl;
        }
    }
}

/**
 * @brief Main function to execute the program.
 *
 * This function sets up the necessary headers and data, performs the HTTP request,
 * and prints the response. It also includes an optional debugging session.
 *
 * @return int Exit status of the program.
 */
int main()
{
    char debugChoice;
    cout << "Would you like to manually test JSON functionality? (y/n): ";
    cin >> debugChoice;

    if (debugChoice == 'y' || debugChoice == 'Y') {
        cout << "Enter a JSON string to test parsing (e.g., {\"greeting\": \"Hello!\", \"timestamp\": \"2023-10-27T16:11:23.457Z\", \"status\": \"success\"}): ";
        cin.ignore(); // Clear the newline character from the buffer
        string debugJson;
        std::getline(cin, debugJson);
        parseAndDisplayJson(debugJson);
        return 0;
    }

    const string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash-latest:generateContent?key=AIzaSyBVCsqwcySc3JqoOolB2J6lIhAInzQ82ag";
    const string jsonData = R"({
        "contents": [
            {
                "parts": [
                    {
                        "text": "Please respond to this prompt with a JSON object in the following format: {\"greeting\": \"Hello!\", \"timestamp\": \"<current date and time>\", \"status\": \"success\"}."
                    }
                ]
            }
        ]
    })";

    curl_global_init(CURL_GLOBAL_DEFAULT);

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    if (headers == NULL) {
        cerr << "Failed to set HTTP headers" << endl;
        return 1;
    }

    string response = performPostRequest(url, headers, jsonData);

    if (!response.empty()) {
        parseAndDisplayJson(response);
    } else {
        cerr << "Empty response received" << endl;
    }

    curl_slist_free_all(headers);
    curl_global_cleanup();

    return 0;
}
