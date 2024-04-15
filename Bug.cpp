
#include "Bug.h"

Bug::Bug(int id, std::pair<int, int> position) : id(id), position(position){}

int Bug::getID() const{
    return id;
}

std::pair<int, int> Bug::getPosition() const{
    return position;
}