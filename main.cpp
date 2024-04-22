#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"

int main() {
    //instance of board class
    Board board;

    //Populate the bugs vector
    board.populateBugVector();

    //Display the bugs
    board.displayBugs();

//    //Ask the user to input a bug ID
//    std::cout << "Enter bug ID: ";
//    int bugID;
//    std::cin >> bugID;
//
//    bool bugFound = false;
//
//    //Search through the bug vector
//    for(const Bug* bug : board.getBugs()) {
//        if (bug->getID() == bugID) {
//            //Display bug info
//            std::cout << "Bug with ID " << bugID << " found:" << std::endl;
//            std::cout << "ID: " << bug->getID() << ", ";
//            std::cout << "Type: ";
//            if(dynamic_cast <const Crawler *>(bug) != nullptr) {
//                std::cout << "Crawler";
//            } else if(dynamic_cast <const Hopper *>(bug) != nullptr) {
//                std::cout << "Hopper";
//            }
//
//            std::cout << ", Position: (" << bug->getPosition().first << ", " << bug->getPosition().second << "), ";
//            if(dynamic_cast <const Hopper *>(bug) != nullptr) {
//                std::cout << "HopLength: " << static_cast <const Hopper *>(bug)->getHopLength() << ", ";
//            }
//            std::cout << "Status: " << (bug->isAlive() ? "Alive" : "Dead") << std::endl;
//
//            bugFound = true;
//            break;
//        }
//    }
//
//    //If bug not found
//    if(!bugFound){
//        std::cout << "Bug " << bugID << " not found" << std::endl;
//    }


    //SFML window
    sf::RenderWindow window(sf::VideoMode(520, 520), "Bug Board");

    //Main loop
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            //Check for mouse click
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                //move bugs
                for(Bug* bug : board.getBugs()){
                    bug -> move();
                }
            }
        }

        //Window clear
        window.clear(sf::Color::White);

        //Display bug board
        board.displayBoard(window);

        //Draw bugs
        for(const Bug* bug : board.getBugs()){
            sf::CircleShape bugShape(25);
            if(dynamic_cast <const Crawler*>(bug) != nullptr){
                bugShape.setFillColor(sf::Color::Green);
            } else if(dynamic_cast <const Hopper*>(bug) != nullptr){
                bugShape.setFillColor(sf::Color::Red);
            }

            std::pair<int, int> position = bug -> getPosition();
            bugShape.setPosition(position.first * 52 + 2, position.second * 52 + 2);
            window.draw(bugShape);
        }

        //display window contents
        window.display();
    }

    return 0;
}
