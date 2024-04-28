#include <iostream>
#include <iomanip>
#include "Board.h"

using namespace std;

int main() {

    //Display the board
    Board board;

    int option;
    bool quit = false;

    do {
        cout << "Menu Items" << endl;
        cout << "1. Initialize Bug Board (load data from file)" << endl;
        cout << "2. Display all Bugs" << endl;
        cout << "3. Find a Bug (given an id)" << endl;
        cout << "4. Tap the Bug Board (causes move all, then fight/eat)" << endl;
        cout << "5. Display Life History of all Bugs (path taken)" << endl;
        cout << "6. Display all Cells listing their Bugs" << endl;
        cout << "7. Run simulation (generates a Tap every second)" << endl;
        cout << "8. Exit (write Life History of all Bugs to file)" << endl;
        cout << endl;

        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                //Read bugs from file and populate the vector
                board.bugFileReader();
                cout << "The bug vector has been filled with bugs from the file" << endl;
                break;
            case 2:
                //Display all bugs in a formatted manner
                board.displayAllBugs();
                cout << "Make sure to select option 1. first to initialize the bugs from the file" << endl;
                break;
            case 3:
                //Find a bug by inputting an ID
                board.findBugById();
                break;
            case 4:
                //Simulates bug movement
                board.tapBugBoard();
                cout << "The board has been tapped" << endl;
                break;
            case 5:
                //Displays bug history
                cout << board.displayBugHistory() << endl;
                break;
            case 6:
                //Displays all cells on the board
                board.displayAllCells();
                break;
            case 7:
                //Runs simulation
                board.runSimulation();
                break;
            case 8:
                //Creates .out file with custom date and time containing bug history
                board.exit();
                quit = true;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
                break;
        }

        cout << endl;

    } while (!quit);

    return 0;
}