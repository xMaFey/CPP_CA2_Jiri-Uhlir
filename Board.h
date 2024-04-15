
#ifndef CA2_BOARD_H
#define CA2_BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bug.h"

class Board {
private:
    //const 10x10 grid
    const int size = 10;
    //2D grid to represent the bug board
    std::vector<std::vector<Bug*>> grid;

public:
    Board();
    ~Board();

    int getSize() const;
    void displayBoard(sf::RenderWindow& window) const;
};


#endif //CA2_BOARD_H
