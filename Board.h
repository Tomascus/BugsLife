//
// Created by Thomas on 10/04/2024.
//

#ifndef BUGSLIFE_BOARD_H
#define BUGSLIFE_BOARD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Bug.h"
#include "SuperBug.h"

using namespace std;

class Board {
public:
    Board(); //Constructor for board
    void display(sf::RenderWindow& window);
    void drawBugs(sf::RenderWindow& window);
    void bugFileReader();
    void displayAllBugs(); //Display all bugs in a formatted manner
    void findBugById(); //Find a bug by inputting an ID
    void tapBugBoard(); //Simulates bug movement
    string displayBugHistory(); //Displays bug history
    void exit(); //Creates .out file with custom date and time containing bug history
    void displayAllCells(); //Displays all cells on the board
    void populateBugMap();
    void runSimulation();
    void loadTextures();

private:
    static const int boardSize = 10; //Size of the board
    int bugCount;
    SuperBug* superBug; //pointer to the superbug object
    vector<vector<sf::RectangleShape>> board; //vector for board cells
    vector<Bug*> bug_vector; //Create a vector of pointers to bug objects
    string getCurrentDateTime(); //Get current date and time for .out file
    map<pair<int, int>, vector<Bug*>> bugMap;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Texture texture4;
};

#endif //BUGSLIFE_BOARD_H
