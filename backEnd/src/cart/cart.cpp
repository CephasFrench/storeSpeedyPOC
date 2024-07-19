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

void Cart::removeItem(const std::string& itemName) {
    if(LOG_FUNC_CALLS) {
        std::cout << "removeItem() called" << std:: endl;
    }
    items.erase(std::remove_if(items.begin(), items.end(), [&itemName](const Item& item) {
        return item.name == itemName;
    }), items.end());
}

std::vector<Item> Cart::getItems() const {
    return items;
}
