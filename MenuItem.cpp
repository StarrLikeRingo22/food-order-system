#include "MenuItem.h"
#include "Utilities.h"

MenuItem::MenuItem(const std::string& record) {
    Utilities util;
    size_t pos = 0;
    bool more = true;

    m_name = util.extractToken(record, pos, more);
    m_quantity = std::stoul(util.extractToken(record, pos, more));
    m_serial = std::stoul(util.extractToken(record, pos, more));
}

const std::string& MenuItem::getName() const {
    return m_name;
}

size_t MenuItem::getQuantity() const {
    return m_quantity;
}

size_t MenuItem::getNextSerial() {
    return m_serial++;
}

void MenuItem::updateQuantity() {
    if (m_quantity > 0)
        --m_quantity;
}

void MenuItem::display(std::ostream& os, bool full) const {
    os << m_name;
    if (full) {
        os << " | Serial: " << m_serial << " | Quantity: " << m_quantity;
    }
    os << std::endl;
}
