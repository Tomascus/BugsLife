//
// Created by Thomas on 10/04/2024.
//

#ifndef BUGSLIFE_BOARD_H
#define BUGSLIFE_BOARD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Bug.h"

using namespace std;

class Board {
public:
    Board(); //Constructor for board
    void display();
    void bugFileReader();
    void displayAllBugs(); //Display all bugs in a formatted manner
    void findBugById(); //Find a bug by inputting an ID
    void tapBugBoard(); //Simulates bug movement
    string displayBugHistory(const vector<Bug *>& bug_vector); //Displays bug history
    void exit(); //Creates .out file with custom date and time containing bug history
    void displayAllCells(); //Displays all cells on the board
    void populateBugMap();
    void runSimulation();

private:
    static const int boardSize = 10; //Size of the board
    int winnerID = -1;
    int bugCount;
    vector<vector<sf::RectangleShape>> board; //vector for board cells
    vector<Bug*> bug_vector; //Create a vector of pointers to bug objects
    string getCurrentDateTime(); //Get current date and time for .out file
    map<pair<int, int>, vector<Bug*>> bugMap;
};

#endif //BUGSLIFE_BOARD_H
