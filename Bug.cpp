
#include "Bug.h"

Bug::Bug(int id, std::pair<int, int> position, Direction direction, int size)
        : id(id), position(position), direction(direction), size(size), alive(true){}

Bug::~Bug(){}

int Bug::getID() const{
    return id;
}

std::pair<int, int> Bug::getPosition() const{
    return position;
}

int Bug::getSize() const {
    return size;
}

void Bug::setSize(int newSize){
    size = newSize;
}

const std::list<std::pair<int, int>>& Bug::getPath() const{
    return path;
}

std::string Bug::getDirectionAsString() const{
    switch(direction){
        case Direction::NORTH:
            return "North";
        case Direction::EAST:
            return "East";
        case Direction::SOUTH:
            return "South";
        case Direction::WEST:
            return "West";
        default:
            return "Unknown";
    }
}