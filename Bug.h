
#ifndef CA2_BUG_H
#define CA2_BUG_H

#include <utility>

class Bug {
private:
    int id;
    std::pair<int, int> position;

public:
    Bug(int id, std::pair<int, int> position);
    int getID() const;
    std::pair<int, int> getPosition() const;
};


#endif //CA2_BUG_H
