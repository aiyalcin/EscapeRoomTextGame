#include "Room.hpp"

Room::Room(const std::string& n, const std::string& d)
    : name(n), description(d) {
}

void Room::showInfo() const {
    std::cout << "\n== " << name << " ==\n" << description << "\n";
    if (!items.empty()) {
        std::cout << "Items hier: ";
        for (auto& item : items) std::cout << item << " ";
        std::cout << "\n";
    }
    std::cout << "Uitgangen: ";
    for (auto& e : exits) std::cout << e.first << " ";
    std::cout << "\n";
}
