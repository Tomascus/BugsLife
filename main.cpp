#include <iostream>
#include "Board.h"

using namespace std;

int main() {

    //Display the board
    Board board;
    //board.display();

    //Read bugs from file and populate the vector
    board.bugFileReader();

    //Display all bugs in a formatted manner
    board.displayAllBugs();

    //Find a bug by inputting an ID
    //board.findBugById();

    //Simulates bug movement
    board.tapBugBoard();

    //Displays bug history
    string output = board.displayBugHistory(vector<Bug *>());
    cout << output << endl;

    //Creates .out file with custom date and time containing bug history
    //board.exit();

    //Displays all cells on the board
    board.displayAllCells();



    return 0;
}


/*
 * void displayBugOccupancy(const map<pair<int, int>, vector<Bug*>>& cellMap);
 *
 *
 * //Display bug occupancy of each cell
    displayBugOccupancy(cellMap);


    //Display the board
    /*Board board;
    board.display();*/


//Basic version, without alive logic
/*for (Bug* bug : bug_vector) { //Deletes bugs from heap
    delete bug;
}
 *
 *
 * void displayBugOccupancy(const map<pair<int, int>, vector<Bug*>>& cellMap) {
    //Iterate over each cell in the 10x10 board
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            // Print the coordinates of the current cell
            cout << "(" << x << "," << y << "): ";

            //Checks if the current cell exists in the cellMap
            auto it = cellMap.find({x, y});
            if (it != cellMap.end()) {
                //If the cell contains bug or bugs, display the info of the bug
                const vector<Bug*>& bugs = it->second;
                for (const Bug* bug : bugs) {
                    cout  << " " << bug->getId() << ", ";
                }
            } else {
                //Cell is empty
                cout << "empty";
            }

            cout << endl;
        }
    }
}
 * */


