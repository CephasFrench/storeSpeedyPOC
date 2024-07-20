#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

class Item {
public:
    std::vector<std::string> names; // Alias item names

    std::string getBarcodeNum() const;
    void updateBarcodeNum(const std::string& newBarcodeNum);

    bool updateItemInfo(const std::string& location, const std::string& barcodeNum);

private:
    std::string barcodeNum;

    std::string callFoodFactsAPI(const std::string& barcodeNum);
    bool updateItemJson(const std::string& location, const std::string& barcodeNum, const std::string& response);

    bool createDirectories(const std::string& path);
};

#endif // ITEM_H
