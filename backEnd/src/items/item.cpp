#include "Item.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <json/json.h>
#include <sys/stat.h>
#include "StoreSpeedyJsonHandler.h"

std::string Item::getBarcodeNum() const {
    return barcodeNum;
}

void Item::updateBarcodeNum(const std::string& newBarcodeNum) {
    barcodeNum = newBarcodeNum;
}

bool Item::updateItemInfo(const std::string& location, const std::string& barcodeNum) {
    std::cout << "Calling Food Facts API for barcode: " << barcodeNum << std::endl;
    std::string response = callFoodFactsAPI(barcodeNum);
    if (response.empty()) {
        std::cerr << "No response or failed to call API for barcode: " << barcodeNum << std::endl;
        return false;
    }
    return updateItemJson(location, barcodeNum, response);
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc &e) {
        return 0;
    }
    return newLength;
}

std::string Item::callFoodFactsAPI(const std::string& barcodeNum) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://world.openfoodfacts.org/api/v2/product/" + barcodeNum + ".json";
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "User-Agent: StoreSpeedyApp/1.0 (contact@storespeedyapp.com)");
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        res = curl_easy_perform(curl);
        long httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "";
        }

        std::cout << "Received response from Food Facts API for barcode: " << barcodeNum << " with HTTP code: " << httpCode << std::endl;

        if (httpCode == 200) {
            return readBuffer;
        } else if (httpCode == 404) {
            std::cerr << "Product not found: HTTP code 404" << std::endl;
            return "";
        } else if (httpCode >= 500 && httpCode < 600) {
            std::cerr << "Server error: HTTP code " << httpCode << std::endl;
            return "";
        } else if (httpCode == 301) {
            std::cerr << "Redirect to another product: HTTP code 301" << std::endl;
            return "";
        } else if (httpCode == 200 && readBuffer.find("<html>") != std::string::npos) {
            std::cerr << "Wrong password or authentication required" << std::endl;
            return "";
        }
    }
    return readBuffer;
}

bool Item::createDirectories(const std::string& path) {
    std::istringstream iss(path);
    std::string dir;
    std::string currentPath = "";

    while (std::getline(iss, dir, '/')) {
        currentPath += dir + "/";
        struct stat st;
        if (stat(currentPath.c_str(), &st) != 0) {
            if (mkdir(currentPath.c_str(), 0755) != 0) {
                std::cerr << "Could not create directory: " << currentPath << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool Item::updateItemJson(const std::string& location, const std::string& barcodeNum, const std::string& response) {
    const std::string storagePath = "/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/server/storage/locations/";
    std::string filePath = storagePath + location + "/items/" + barcodeNum + ".json";

    try {
        if (!createDirectories(storagePath + location + "/items")) {
            return false;
        }

        Json::Value root;
        Json::CharReaderBuilder builder;
        std::istringstream responseStream(response);
        std::string errs;
        if (!Json::parseFromStream(builder, responseStream, &root, &errs)) {
            std::cerr << "Failed to parse JSON response: " << errs << std::endl;
            return false;
        }

        if (root["status"].asInt() == 1 && root["status_verbose"].asString() == "product found") {
            Json::Value product = root["product"];
            std::string productName = product["product_name"].asString();
            std::string ingredients = product["ingredients_text"].asString();
            std::string allergens;
            for (const auto& allergen : product["allergens_tags"]) {
                allergens += allergen.asString() + ", ";
            }
            if (!allergens.empty()) {
                allergens.pop_back();
                allergens.pop_back();
            }

            std::cout << "Parsed product name: " << productName << std::endl;
            std::cout << "Parsed ingredients: " << ingredients << std::endl;
            std::cout << "Parsed allergens: " << allergens << std::endl;

            Json::Value existingRoot;
            std::ifstream fileCheck(filePath, std::ifstream::binary);
            if (fileCheck.is_open()) {
                fileCheck >> existingRoot;
                fileCheck.close();

                existingRoot["product_name"] = productName;
                existingRoot["ingredients"] = ingredients;
                existingRoot["allergens"] = allergens;
            } else {
                existingRoot["product_name"] = productName;
                existingRoot["ingredients"] = ingredients;
                existingRoot["allergens"] = allergens;
            }

            std::ofstream file(filePath, std::ofstream::binary);
            if (!file.is_open()) {
                std::cerr << "Could not open file: " << filePath << std::endl;
                return false;
            }

            Json::StreamWriterBuilder writer;
            std::unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
            jsonWriter->write(existingRoot, &file);
            file.close();
            return true;
        } else {
            std::cerr << "Product not found: " << root["status_verbose"].asString() << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Could not update item info: " << e.what() << std::endl;
        return false;
    }
}
