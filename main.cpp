#include <iostream>
#include <vector>
#include "MenuItem.h"
#include "Utilities.h"

void showMenu(const std::vector<MenuItem>& menu) {
    std::cout << "\nMenu:\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        std::cout << i + 1 << ". ";
        menu[i].display(std::cout, false);
    }
    std::cout << "0. Checkout\n";
}

int main() {
    Utilities::setDelimiter(',');

    std::vector<MenuItem> menu = {
        MenuItem("Burger,10,1001"),
        MenuItem("Fries,20,1002"),
        MenuItem("Soda,15,1003"),
        MenuItem("Pizza,8,1004"),
        MenuItem("Salad,5,1005")
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
    for (size_t i = 0; i < order.size(); ++i) {
        if (order[i] > 0) {
            std::cout << order[i] << " x " << menu[i].getName() << '\n';
            empty = false;
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
