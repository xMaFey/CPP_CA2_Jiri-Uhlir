
#include "Crawler.h"
#include <cstdlib>

Crawler::Crawler(int id, std::pair<int, int> position, Direction dir, int size)
    : Bug(id, position, dir, size){}

Crawler::~Crawler(){}

void Crawler::move() {
    // Move by 1 unit in the current direction
    switch (direction) {
        case Direction::NORTH:
            if (position.second > 0) {
                position.second--; // Move north if not at the top edge
            } else {
                direction = static_cast<Direction>(rand() % 4); // Change direction if at the top edge
            }
            break;
        case Direction::EAST:
            if (position.first < 9) {
                position.first++; // Move east if not at the right edge
            } else {
                direction = static_cast<Direction>(rand() % 4); // Change direction if at the right edge
            }
            break;
        case Direction::SOUTH:
            if (position.second < 9) {
                position.second++; // Move south if not at the bottom edge
            } else {
                direction = static_cast<Direction>(rand() % 4); // Change direction if at the bottom edge
            }
            break;
        case Direction::WEST:
            if (position.first > 0) {
                position.first--; // Move west if not at the left edge
            } else {
                direction = static_cast<Direction>(rand() % 4); // Change direction if at the left edge
            }
            break;
    }
    // Record new position in crawler's path history
    path.push_back(position);
}


bool Crawler::isWayBlocked() const {
    int boardSize = getSize();

    //Check if the crawler is at the edge
    switch (direction){
        case Direction::NORTH:
            return position.second == 0;
        case Direction::EAST:
            return position.first == (boardSize - 1);
        case Direction::SOUTH:
            return position.second == (boardSize - 1);
        case Direction::WEST:
            return position.first == 0;
    }

    return false;
}