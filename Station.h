#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <iomanip> 

    class Station {
        int id;
        std::string m_itemName;
        std::string m_description;
        size_t m_serialNumber;
        size_t m_quantity;
        static size_t m_widthField;
        static int id_generator;
    protected:
        double m_price = 0.0;
        bool m_isDiscounted = false;
    public:
        Station(const std::string& record);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        double getPrice() const;
        bool isDiscounted() const;
        void display(std::ostream& os, bool full) const;
    };


#endif 