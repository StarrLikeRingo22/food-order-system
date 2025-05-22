#include "MenuItem.h"
#include "Utilities.h"
#include "Station.h"

extern const double g_taxrate;
extern const double g_discount;

MenuItem::MenuItem(const std::string& record) : Station(record) {
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
double MenuItem::getPrice() const {
    double base = Station::getPrice();
    double taxed = base * (1.0 + g_taxrate);
    if (Station::isDiscounted())
        taxed *= (1.0 - g_discount);
    return taxed;
}

bool MenuItem::isDiscounted() const {
    return m_isDiscounted;
}

void MenuItem::display(std::ostream& os, bool full) const {
    os << m_name;
    if (full) {
        os << " | Serial: " << m_serial << " | Quantity: " << m_quantity;
    }
    os << std::endl;
}
