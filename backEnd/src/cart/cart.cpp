#include "cart.h"
#include <algorithm> // for std::remove_if

void Cart::addItem(const Item& item) {
    items.push_back(item);
}

void Cart::removeItem(const std::string& itemName) {
    items.erase(std::remove_if(items.begin(), items.end(), [&itemName](const Item& item) {
        return item.name == itemName;
    }), items.end());
}

std::vector<Item> Cart::getItems() const {
    return items;
}
