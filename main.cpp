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




