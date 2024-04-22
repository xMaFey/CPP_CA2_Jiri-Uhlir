
#ifndef CA2_HOPPER_H
#define CA2_HOPPER_H

#include "Bug.h"

class Hopper : public Bug{
private:
    int hopLength;

public:
    Hopper(int id, std::pair<int, int> position, Direction direction, int size, int hopLength);
    ~Hopper();

    void move() override;
    bool isWayBlocked() const override;
    int getHopLength() const;
};

#endif //CA2_HOPPER_H
