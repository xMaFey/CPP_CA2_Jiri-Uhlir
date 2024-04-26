
#ifndef CA2_CRAWLER_H
#define CA2_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug{
public:
    Crawler(int id, std::pair<int, int> position, Direction direction, int size)
            : Bug(id, position, direction, size){}
    ~Crawler() {};

    void move() override;
    bool isWayBlocked() const override;
};

#endif //CA2_CRAWLER_H