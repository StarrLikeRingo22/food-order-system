#include "Station.h"
#include "Utilities.h"


    size_t Station::m_widthField = 0;

    int Station::id_generator = 0;

    Station::Station(const std::string& record)
    : id(0), m_serialNumber(0), m_quantity(0) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
  


        id = ++Station::id_generator;

        if (record.empty()) {
            throw "The record is empty!";
        }

        else {
            m_itemName = util.extractToken(record, next_pos, more);

            if (more) {
                m_serialNumber = std::stoi(util.extractToken(record, next_pos, more));
            }

            if (more) {
                m_quantity = std::stoi(util.extractToken(record, next_pos, more));
            }

            if (m_widthField < util.getFieldWidth()) {
                m_widthField = util.getFieldWidth();
            }

            if (more) {
                m_description = util.extractToken(record, next_pos, more);
            }
        }
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            --m_quantity;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        if (full) {
            os << std::right << std::setw(3) << std::setfill('0') << id << " | "
                << std::left << std::setw(m_widthField) << std::setfill(' ') << m_itemName << "| "
                << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | "
                << std::right << std::setw(4) << std::setfill(' ') << m_quantity << " | "
                << std::left << m_description << std::endl;
        }
        else {
            os << std::right << std::setw(3) << std::setfill('0') << id << " | "
                << std::left << std::setw(m_widthField) << std::setfill(' ') << m_itemName << "| "
                << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | "
                << std::endl;
        }
    }


