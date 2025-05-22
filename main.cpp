#include <iostream>
#include <iomanip>
#include <vector>
#include "MenuItem.h"
#include "Utilities.h"


    extern const double g_taxrate = 0.13; // 13 percent tax
    extern const double g_discount = 0.10; //10 percent disc.

void showMenu(const std::vector<MenuItem>& menu) {
    std::cout << "\nMenu:\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        std::cout << i + 1 << ". ";
        menu[i].display(std::cout, false);

        double taxedPrice = menu[i].getPrice() * (1.0 + g_taxrate);
        if (menu[i].isDiscounted()) {
            taxedPrice -= taxedPrice * g_discount;
        }
        std::cout << "   Price: $" << std::fixed << std::setprecision(2) << taxedPrice << '\n';
    }
    std::cout << "0. Checkout\n";
}

int main() {
    Utilities::setDelimiter(',');

    std::vector<MenuItem> menu = {
    MenuItem("Big Mac,10,1001,5.99,1"),
    MenuItem("McChicken,15,1002,4.49,0"),
    MenuItem("Filet-O-Fish,12,1003,4.79,0"),
    MenuItem("Quarter Pounder,8,1004,6.29,1"),
    MenuItem("McNuggets (10 pcs),20,1005,5.39,0"),
    MenuItem("Fries (Large),25,1006,2.99,0"),
    MenuItem("Coca-Cola (Large),30,1007,1.89,1"),
    MenuItem("Apple Pie,18,1008,1.29,0"),
    MenuItem("McFlurry Oreo,10,1009,3.49,0"),
    MenuItem("Double Cheeseburger,9,1010,4.19,1")
    };

    std::vector<int> order(menu.size(), 0);

    std::cout << "=== Welcome to Terminal Food Ordering ===\n";

    while (true) {
        showMenu(menu);
        std::cout << "\nChoose an item by number (0 to finish): ";
        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        if (choice < 1 || choice >(int)menu.size()) {
            std::cout << "Invalid choice.\n";
            continue;
        }

        int qty;
        std::cout << "Enter quantity: ";
        std::cin >> qty;

        if (qty <= 0) {
            std::cout << "Invalid quantity.\n";
            continue;
        }

        size_t available = menu[choice - 1].getQuantity();
        if (qty > (int)available) {
            std::cout << "Only " << available << " left. Try again.\n";
            continue; // this continues the menu, which is fine
        }
        else if (qty <= 0) {
            std::cout << "Invalid quantity.\n";
            continue;
        }

        for (int i = 0; i < qty; ++i)
            menu[choice - 1].updateQuantity();

        order[choice - 1] += qty;
        std::cout << "Added to order.\n";
    }

    std::cout << "\n=== Your Order ===\n";
    bool empty = true;
    double grandTotal = 0.0;


    for (size_t i = 0; i < order.size(); ++i) {
        if (order[i] > 0) {
           // std::cout << order[i] << " x " << menu[i].getName() << '\n';
            empty = false;
            double basePrice = menu[i].getPrice() * order[i];
            double taxAmount = basePrice * g_taxrate;
            double discountAmount = menu[i].isDiscounted() ? (basePrice * g_discount) : 0.0;
            double total = basePrice + taxAmount - discountAmount;
            std::cout << order[i] << " x " << menu[i].getName()
                << " | Base: $" << basePrice
                << " | Tax: $" << taxAmount
                << (menu[i].isDiscounted() ? " | Discount: -$" + std::to_string(discountAmount) : "")
                << " | Total: $" << total
                << '\n';
        }
    }
    if (empty)
        std::cout << "No items ordered.\n";
    else
        std::cout << "Thank you!\n";

    std::cout << "\nRemaining Inventory:\n";
    for (auto& item : menu)
        item.display(std::cout, true);

    return 0;
}
