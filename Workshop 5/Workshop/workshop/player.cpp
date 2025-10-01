#include "Player.hpp"

void Player::showInventory() const {
    if (inventory.empty()) {
        std::cout << "Inventaris is leeg.\n";
    }
    else {
        std::cout << "Inventaris: ";
        for (auto& i : inventory) std::cout << i << " ";
        std::cout << "\n";
    }
}

bool Player::hasItem(const std::string& item) const {
    return std::find(inventory.begin(), inventory.end(), item) != inventory.end();
}

void Player::pickUp(const std::string& item) {
    auto& items = currentRoom->items;
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        inventory.push_back(item);
        items.erase(it);
        std::cout << "Je hebt " << item << " opgepakt.\n";
    }
    else {
        std::cout << "Geen " << item << " hier.\n";
    }
}

void Player::showAsciiArt() {
    std::cout << R"(

         [Robot Zorgassistent]
             .-"""-.
            / .===. \
            \/ 6 6 \/
            (  \_/  )
         ___ooo__V__ooo___

        )" << "\n";
}
