#include <iostream>
#include "Board.h"
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <functional>

//For eating bugs (found on internet)
namespace std{
    template <>
    struct hash<pair<int, int>>{
        size_t operator()(const pair<int, int>& p) const{
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };
}

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

    //clear the bug vector
    for(Bug* bug : bugs){
        delete bug;
    }
    bugs.clear();
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

            //draw cell
            window.draw(cell);
        }
    }
}

void Board::populateBugVector(){
    //open the bugs.txt file
    std::ifstream inputFile("C:/Users/Uzivatel/Desktop/School/Year 2/C++/CA2/bugs.txt");
    if(!inputFile){
        std::cerr << "Error: Unable to open bugs.txt" << std::endl;
        return;
    }
    std::cout << "File opened successfully!" << std::endl;

    //Read each line from the file
    std::string line;
    while(std::getline(inputFile, line)){
        // Debug statement to check the line read from the file
        std::cout << "Read line: " << line << std::endl;

        //create a string stream to parse the line
        std::istringstream iss(line);

        //read info from the line
        std::string bugTypeStr, idStr, xStr, yStr, directionStr, sizeStr, hopLengthStr;
        std::getline(iss, bugTypeStr, ';');
        std::getline(iss, idStr, ';');
        std::getline(iss, xStr, ';');
        std::getline(iss, yStr, ';');
        std::getline(iss, directionStr, ';');
        std::getline(iss, sizeStr, ';');
        std::getline(iss, hopLengthStr, ';'); // Only for Hopper bugs

        //parse the values
        char bugType = bugTypeStr[0];
        int id = std::stoi(idStr);
        int x = std::stoi(xStr);
        int y = std::stoi(yStr);
        int direction = std::stoi(directionStr);
        int size = std::stoi(sizeStr);
        int hopLength = (bugType == 'H') ? std::stoi(hopLengthStr) : 0;

        //create position pair
        std::pair<int, int> position(x, y);

        // Read direction as integer
        int directionInt;
        iss >> directionInt;

        //create Bug object base on the bug type
        Bug* bug = nullptr;
        if(bugType == 'C'){
            //crawler
            bug = new Crawler(id, position, static_cast<Direction>(direction), size);
        } else if(bugType == 'H') {
            //hopper
            bug = new Hopper(id, position, static_cast<Direction>(direction), size, hopLength);
        } else{
            std::cerr << "Unknown bug type: " << bugType << std::endl;
            continue;
        }

        //add bug to the vector
        bugs.push_back(bug);

    }

    //close the file
    inputFile.close();
}

void Board::displayBugs() const{
    //Iterate over each bug in the vector
    for(const Bug* bug : bugs){
        //print bug info
        std::cout << "ID: " << bug -> getID() << ", ";
        std::cout << "Type: ";

        //check the type of bug
        if(dynamic_cast <const Crawler*>(bug) != nullptr){
            std::cout << "Crawler";
        } else if(dynamic_cast <const Hopper*>(bug) != nullptr){
            std::cout << "Hopper";
        }

        //print others
        std::cout << ", Position: (" << bug -> getPosition().first << ", " << bug -> getPosition().second << "), ";
        std::cout << "Size: " << bug -> getSize() << ", ";
        std::cout << "Direction: " << bug -> getDirectionAsString() << ", ";

        //print hopLength for hoppers
        if(dynamic_cast <const Hopper*>(bug) != nullptr){
            std::cout << "HopLength: " << static_cast <const Hopper*>(bug) -> getHopLength() << ", ";
        }
        std::cout << "Status: " << (bug -> isAlive() ? "Alive" : "Dead") << std::endl;
    }
}

const std::vector<Bug*>& Board::getBugs() const{
    return bugs;
}

void Bug::setAlive(bool alive){
    this -> alive = alive;
}

void Board::bugFights(){
    //Create map to group bugs by their positions
    std::unordered_map<std::pair<int, int>, std::vector<Bug*>> bugGroups;

    //Group bugs by their positions
    for(Bug* bug : bugs){
        std::pair<int, int> position = bug -> getPosition();
        bugGroups[position].push_back(bug);
    }

    //Iterate through each group of bugs in the same position
    for(auto& group : bugGroups){
        std::vector<Bug*>& bugsInSamePosition = group.second;

        //Find the largest bug
        auto maxBug = std::max_element(bugsInSamePosition.begin(), bugsInSamePosition.end(), [](Bug* bug1, Bug* bug2){
            return bug1 -> getSize() < bug2 -> getSize();
        });

        //Mark dead bugs as dead and update size
        for(Bug * bug : bugsInSamePosition){
            if(bug != *maxBug && bug -> isAlive()){
                bug -> setAlive(false);
                (*maxBug) -> setSize((*maxBug) -> getSize() + bug -> getSize());
            }
        }
    }
}