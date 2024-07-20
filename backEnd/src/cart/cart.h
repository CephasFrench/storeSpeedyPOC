#ifndef CART_H
#define CART_H

#include "../items/item.h"
#include <vector>
#include <string>

class Cart {
public:
    void addItem(const Item& item);
    void removeItem(Item& item);
    std::vector<Item> getItems() const;

private:
    std::vector<Item> items;
};

#endif // CART_H
