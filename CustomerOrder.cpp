#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

#include <iomanip>
#include <iostream>
#include <vector>

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const std::string& str) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        if (str.empty()) {
            throw "string is emtpy!";
        }
        else {
            m_name = util.extractToken(str, next_pos, more);

            if (more) {
                m_product = util.extractToken(str, next_pos, more);
            }

            m_cntItem = 0;
            std::vector<Item*> tempItems;

            while (more) {
                std::string itemName = util.extractToken(str, next_pos, more);
                tempItems.push_back(new Item(itemName));
                m_cntItem++;
            }

            m_lstItem = new Item * [m_cntItem];
            for (size_t i = 0; i < m_cntItem; i++) {
                m_lstItem[i] = tempItems[i];
            }

            if (m_widthField < util.getFieldWidth()) {
                m_widthField = util.getFieldWidth();
            }
        }
    }


    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        m_name = std::move(src.m_name);
        m_product = std::move(src.m_product);
        m_cntItem = src.m_cntItem;
        m_lstItem = src.m_lstItem;

        src.m_cntItem = 0;
        src.m_lstItem = nullptr;
    }
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
            if (m_lstItem) {
                for (size_t i = 0; i < m_cntItem; ++i) {
                    delete m_lstItem[i];
                }
                delete[] m_lstItem;
            }
            m_name = std::move(src.m_name);
            m_product = std::move(src.m_product);
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        if (m_lstItem) {
            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
            }
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName) {
                return m_lstItem[i]->m_isFilled;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        bool itemFilled = false;
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName()) {
                if (!m_lstItem[i]->m_isFilled) {
                    if (station.getQuantity() > 0) {
                        m_lstItem[i]->m_isFilled = true;
                        m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                        station.updateQuantity();
                        if (!itemFilled) {
                            os << "    Filled " << m_name << ", " << m_product
                                << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                            itemFilled = true;
                            break;
                        }
                    }
                    else {
                        os << "    Unable to fill " << m_name << ", " << m_product
                            << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    }
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const {
        os << m_name << "- " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::setw(6) << std::setfill('0') << std::right
               << m_lstItem[i]->m_serialNumber << "] "
               << std::setw(m_widthField) << std::setfill(' ') << std::left
               << m_lstItem[i]->m_itemName << " - "
               << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }