#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>

class Room {
public:
    std::string name;
    std::string description;
    std::map<std::string, std::shared_ptr<Room>> exits;
    std::vector<std::string> items;

    Room(const std::string& n, const std::string& d);

    void showInfo() const;
};

#endif // ROOM_HPP
