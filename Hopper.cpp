#include "Hopper.h"
#include "Board.h"
#include <cstdlib>

Hopper::Hopper(int id, std::pair<int, int> position, Direction dir, int size, int hopLength)
        : Bug(id, position, dir, size), hopLength(hopLength) {}

Hopper::~Hopper() {}

void Hopper::move() {
    // Generates random hop length between 2 and 4
    int hopDistance = rand() % 3 + 2;
    std::pair<int, int> newPosition = position; // Store the new position temporarily

    switch (direction) {
        case Direction::NORTH:
            newPosition.second -= hopDistance;
            break;
        case Direction::EAST:
            newPosition.first += hopDistance;
            break;
        case Direction::SOUTH:
            newPosition.second += hopDistance;
            break;
        case Direction::WEST:
            newPosition.first -= hopDistance;
            break;
    }

    // Check if the new position is within the boundaries of the board
    if (newPosition.first >= 0 && newPosition.first < 10 && newPosition.second >= 0 && newPosition.second < 10) {
        // Record new position in hopper's path history
        path.push_back(newPosition);
    }

    // If the hopper jumps off the board, move it next to the wall and change direction randomly
    if (newPosition.first < 0 || newPosition.first >= 10 || newPosition.second < 0 || newPosition.second >= 10) {
        // Move next to the wall
        if (newPosition.first < 0) newPosition.first = 0;
        if (newPosition.first >= 10) newPosition.first = 9;
        if (newPosition.second < 0) newPosition.second = 0;
        if (newPosition.second >= 10) newPosition.second = 9;

        // Change direction randomly
        direction = static_cast<Direction>(rand() % 4);
    }

    // Update the hopper's position
    position = newPosition;
}




bool Hopper::isWayBlocked() const {
    // Hopper can't be blocked as it can jump over obstacles
    return false;
}

int Hopper::getHopLength() const {
    return hopLength;
}
