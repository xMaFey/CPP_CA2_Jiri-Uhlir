
#include "Hopper.h"
#include <cstdlib>

Hopper::Hopper(int id, std::pair<int, int> position, Direction dir, int size, int hopLength)
    : Bug(id, position, dir, size), hopLength(hopLength){}

Hopper::~Hopper(){}

void Hopper::move(){
    //Check if the way is blocked
    if(isWayBlocked()){
        Direction newDirection = static_cast<Direction>(rand() % 4);
        //Set new direction
        direction = newDirection;
    } else{
        //Generates random hop length between 2 and 4
        int hopDistance = rand() % 3 + 2;

        //Try to move hopDistance units in the current direction
        for(int i = 0; i < hopDistance; i++){
            switch(direction){
                case Direction::NORTH:
                    if(position.second > 0){
                        position.second--;
                    }
                    break;
                case Direction::EAST:
                    if(position.first < (getSize() - 1)){
                        position.first++;
                    }
                    break;
                case Direction::SOUTH:
                    if(position.second < (getSize() - 1)){
                        position.second++;
                    }
                    break;
                case Direction::WEST:
                    if(position.first > 0){
                        position.first--;
                    }
                    break;
            }

            //Record new position in hoppers path history
            path.push_back(position);

            //Check if the hopper reached the edge of the board
            if(position.first == 0 || position.first == (getSize() - 1) || position.second == 0 || position.second == (getSize() - 1)){
                break; //Stop hopping if reached the edge
            }
        }
    }
}

bool Hopper::isWayBlocked() const{
    return false;
}

int Hopper::getHopLength() const {
    return hopLength;
}