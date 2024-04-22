#include "Hopper.h"
#include "Board.h"
#include <cstdlib>

Hopper::Hopper(int id, std::pair<int, int> position, Direction dir, int size, int hopLength)
        : Bug(id, position, dir, size), hopLength(hopLength) {}

Hopper::~Hopper() {}

void Hopper::move() {
    // Generates random hop length between 2 and 4
    int hopDistance = rand() % 3 + 2;

    switch (direction) {
        case Direction::NORTH:
            position.second -= hopDistance;
            break;
        case Direction::EAST:
            position.first += hopDistance;
            break;
        case Direction::SOUTH:
            position.second += hopDistance;
            break;
        case Direction::WEST:
            position.first -= hopDistance;
            break;
    }

    //Record new position in hopper's path history
    path.push_back(position);

    //If the hopper jumps off the board, move it next to the wall and change direction randomly
    if (position.first < 0) {
        position.first = 0;
        direction = static_cast<Direction>(rand() % 4); // Change direction randomly
    }
    if (position.first > 9) {
        position.first = 9;
        direction = static_cast<Direction>(rand() % 4);
    }
    if (position.second < 0) {
        position.second = 0;
        direction = static_cast<Direction>(rand() % 4);
    }
    if (position.second > 9) {
        position.second = 9;
        direction = static_cast<Direction>(rand() % 4);
    }
}


bool Hopper::isWayBlocked() const {
    // Hopper can't be blocked as it can jump over obstacles
    return false;
}

int Hopper::getHopLength() const {
    return hopLength;
}
