#include "Item.h"
#include <iostream>

int main() {
    // Define a set of barcodes to test
    const std::string barcode1 = "5449000000439"; // Coca-Cola
    const std::string barcode2 = "0000000000000"; // Heinz Ketchup
    const std::string barcode3 = "0000000000000"; // Oreo Cookies

    // Define location for testing
    const std::string location = "DefaultLoc";

    // Create Item objects
    Item item1;
    Item item2;
    Item item3;

    // Update barcode numbers
    item1.updateBarcodeNum(barcode1);
    item2.updateBarcodeNum(barcode2);
    item3.updateBarcodeNum(barcode3);

    // Test updateItemInfo functionality
    std::cout << "Testing item1 with barcode " << barcode1 << std::endl;
    if (item1.updateItemInfo(location, barcode1)) {
        std::cout << "Successfully updated item with barcode " << barcode1 << " at location " << location << std::endl;
    } else {
        std::cerr << "Failed to update item with barcode " << barcode1 << " at location " << location << std::endl;
    }

    std::cout << "Testing item2 with barcode " << barcode2 << std::endl;
    if (item2.updateItemInfo(location, barcode2)) {
        std::cout << "Successfully updated item with barcode " << barcode2 << " at location " << location << std::endl;
    } else {
        std::cerr << "Failed to update item with barcode " << barcode2 << " at location " << location << std::endl;
    }

    std::cout << "Testing item3 with barcode " << barcode3 << std::endl;
    if (item3.updateItemInfo(location, barcode3)) {
        std::cout << "Successfully updated item with barcode " << barcode3 << " at location " << location << std::endl;
    } else {
        std::cerr << "Failed to update item with barcode " << barcode3 << " at location " << location << std::endl;
    }

    return 0;
}
