#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.h"
#include "Bug.h"

int main() {
    //instance of board class
    Board board;

    //SFML window
    sf::RenderWindow window(sf::VideoMode(520, 520), "Bug Board");

    //Main loop
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        //Window clear
        window.clear(sf::Color::White);

        //Display bug board
        board.displayBoard(window);

        //display window contents
        window.display();
    }

    return 0;
}
