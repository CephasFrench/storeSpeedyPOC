#include "cart.h"
#include "config.h"
#include <algorithm> // for std::remove_if
#include <iostream>

void Cart::addItem(const Item& item) {
    if(LOG_FUNC_CALLS) {
        std::cout << "addItem() called" << std:: endl;
    }

    items.push_back(item);
}

void Cart::removeItem(Item& itemA) {
    if(LOG_FUNC_CALLS) {
        std::cout << "removeItem() called" << std:: endl;
    }

    int barcodeNum = itemA.getBarcodeNum();
    
    items.erase(std::remove_if(items.begin(), items.end(), [&barcodeNum](Item& itemB) {
        return (itemB.getBarcodeNum() == barcodeNum);
    }), items.end()); //Removes item FROM CART (not server memory)
}

std::vector<Item> Cart::getItems() const {
    return items;
}
