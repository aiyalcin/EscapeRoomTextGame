#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Room.hpp"

class Player {
public:
    std::shared_ptr<Room> currentRoom;
    std::vector<std::string> inventory;

    void showInventory() const;
    bool hasItem(const std::string& item) const;
    void pickUp(const std::string& item);
    void showAsciiArt(void);
};

#endif // PLAYER_HPP
