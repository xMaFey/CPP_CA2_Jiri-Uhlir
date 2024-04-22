
#include "Crawler.h"
#include <cstdlib>

Crawler::Crawler(int id, std::pair<int, int> position, Direction dir, int size)
    : Bug(id, position, dir, size){}

Crawler::~Crawler(){}

void Crawler::move(){
    //Check if the way is blocked
    if(isWayBlocked()){
        Direction newDirection = static_cast<Direction>(rand() % 4);
        //Set new direction
        direction = newDirection;
    } else{
        //Move in the current direction
        switch(direction){
            case Direction::NORTH:
                position.second--;
                break;
            case Direction::EAST:
                position.first++;
                break;
            case Direction::SOUTH:
                position.second++;
                break;
            case Direction::WEST:
                position.first--;
                break;
        }
    }

    //Record new position in crawlers path history
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