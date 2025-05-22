#ifndef FOOD_MENU_ITEM_H
#define FOOD_MENU_ITEM_H

#include <string>
#include <iostream>
#include "Station.h"

class MenuItem : public Station {
    std::string m_name;
    size_t m_serial;
    size_t m_quantity;
public:
    MenuItem(const std::string& record);
    const std::string& getName() const;
    size_t getQuantity() const;
    size_t getNextSerial();
    void updateQuantity();
    double getPrice() const;
    bool isDiscounted() const;
    void display(std::ostream& os, bool full) const;
};

#endif
