#include <iostream>
#include "Board.h"

Board::Board(){
    //initialize the bug board with nullptrs
    grid.resize(size, std::vector<Bug*>(size, nullptr));
}

Board::~Board(){
    //memory clean up for bugs
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            delete grid[i][j];
        }
    }
}

int Board::getSize() const{
    return size;
}

void Board::displayBoard(sf::RenderWindow& window) const{
    //cell size and padding
    const float cellSize = 50.f;
    const float padding = 2.f;

    //create cells
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setFillColor(sf::Color::White);
    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(padding);

    //draw cells and iterate over the bug board
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            //cell position
            cell.setPosition(i * (cellSize + padding), j * (cellSize + padding));

            //if there is bug on this position draw it
            if(grid[i][j] != nullptr){
                //draw bug - CUSTOMIZE IN BUGS CLASS!, only test for now
                sf::CircleShape bug(cellSize / 2);
                bug.setFillColor(sf::Color::Red);
                bug.setPosition(cell.getPosition() + sf::Vector2f(padding, padding));
                window.draw(bug);
            }

            //draw cell
            window.draw(cell);
        }
    }
}