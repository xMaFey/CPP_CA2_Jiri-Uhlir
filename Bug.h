
#ifndef CA2_BUG_H
#define CA2_BUG_H

#include <utility>
#include <iostream>
#include <string>
#include <list>

enum class Direction{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Bug {
protected:
    int id;
    std::pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    std::list<std::pair<int, int>> path;

public:
    Bug(int id, std::pair<int, int> position, Direction direction, int size);
    virtual ~Bug();

    int getID() const;
    std::pair<int, int> getPosition() const;
    int getSize() const;
    bool isAlive() const;
    const std::list<std::pair<int,int>>& getPath() const;
    std::string getDirectionAsString() const;

    virtual void move() = 0;
    virtual bool isWayBlocked() const = 0;
};

#endif //CA2_BUG_H