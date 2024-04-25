//
// Created by Thomas on 10/04/2024.
//

#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <unistd.h>

using namespace sf;
using namespace std;

Board::Board() {
    // Initialize the board
    for (int i = 0; i < boardSize; ++i) { //Define a board height and width
        vector<RectangleShape> row;
        for (int j = 0; j < boardSize; ++j) {
            RectangleShape cell(Vector2f(50, 50)); // Defined size of each cell
            cell.setPosition(j * 50, i * 50); //Position the cell on the board based on the for loop state
            if ((i + j) % 2 == 0) {
                cell.setFillColor(Color(76, 153, 0)); //Custom RGB Green color for even cells
            } else {
                cell.setFillColor(Color(102, 51, 0)); //Custom RGB Brown color for odd cells
            }
            row.push_back(cell); //Pushes cells to row vector of the board
        }
        board.push_back(row); //Pushes each cell from rows to 2D vector of the board
    }


}

void Board::display() {
    RenderWindow window(VideoMode(500, 500), "Bug Board");

    // Main loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        // Draw the board cells
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                window.draw(board[i][j]);
            }
        }

        window.display();
    }
}

//Feature 9

void Board::runSimulation() {

    bugFileReader();
    cout << "Welcome to the Bug's Life, The Game!" << endl;
    displayAllBugs();
    cout << "" << endl;

    //Run simulation until the game is over
    while (bugCount != 1) {

        tapBugBoard();
        string output = displayBugHistory(vector<Bug *>());
        cout << output << endl;
        displayAllCells();
        cout << "" << endl;
        //Wait for 1 second
        sleep(1);
    }
    exit();
}

//Feature 7

void Board::displayAllCells() {

    if (bugMap.empty()) {
        populateBugMap(); //Create a map of bugs if it is not defined yet
    }

    //Loop that goes through all cell positions and displays them
    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            pair<int, int> pos = make_pair(x, y); //Create a pair of current position
            cout << "(" << x << "," << y << "): ";

            //Check if Bug map contains bug/bugs on a current tile/square
            if (bugMap.empty()) {
                cout << "empty" << endl;
            } else {
                const vector<Bug*>& bugs = bugMap[pos]; //Create a vector of bugs for current square in case there are multiple bugs inside
                for (int i = 0; i < bugs.size(); ++i) {
                    Bug* bug = bugs[i]; //Pointer to bug in the vector
                    if (dynamic_cast<Crawler*>(bug)) {
                        cout << "Crawler " << bug->getId() << " ";
                    } else if (dynamic_cast<Hopper*>(bug)) {
                        cout << "Hopper " << bug->getId() << " ";
                    }
                }
                cout << endl;
            }
        }
    }
}

//Bug Map - Maps position to the bugs

void Board::populateBugMap() {
    for (Bug* bug : bug_vector) { //Goes through the bug vector and pushes position to the bug map
        pair<int, int> pos = bug->getPosition();
        bugMap[pos].push_back(bug);
    }
}

//Feature 6

void Board::exit() {
    //Create the name for the file
    string filename = "bugs_life_history_" + getCurrentDateTime() + ".out";
    ofstream fout(filename); //Create file output stream

    if (fout) {
        fout << displayBugHistory(bug_vector); //Write bug history to the file

        fout.close(); //Close the file
        cout << "Bug life history saved to: " << filename << endl;
    } else {
        cout << "Unable to open file for writing" << endl;
    }
}

//Feature 5

string Board::displayBugHistory(const vector<Bug *>& bug_vector) {
    string history;

    for (const auto& bug : bug_vector) { //Iterate through bug vector
        history += to_string(bug->getId()) + " "; //Display Bug ID

        //Display Bug Type
        if (dynamic_cast<Crawler*>(bug)) {
            history += "Crawler ";
        } else if (dynamic_cast<Hopper*>(bug)) {
            history += "Hopper ";
        }

        //Display path taken
        history += "Path: ";
        const list<pair<int, int>>& path = bug->getPath(); //Get the path of the bug through reference called path
        if (!path.empty()) {
            //Display each position in the bug's path
            for (const auto& pos : path) {
                history += "(" + to_string(pos.first) + "," + to_string(pos.second) + ")";
            }
        } else {
            history += "No path recorded";
        }
        if (!bug->isAlive()) {
            history += " Eaten by " + winnerID;
        } else {
            history += " Alive!";  //Display that the bug is alive
        }
        history += "\n"; //Add newline for formatting
    }
    return history;
}


//Feature 4 && Feature 8

void Board::tapBugBoard() {

    bugCount = 0;

    if (bugMap.empty()) {
        populateBugMap(); //Create a map of bugs if it is not defined yet
    }

    //Iterate over each bug in the bug_vector and move it
    for (Bug* bug : bug_vector) {
        bug->move();
        if (bug->isAlive()) {
            bugCount++;
        }

        //Get the new position of the bug
        pair<int, int> pos = bug->getPosition();

        //Update the bug's position on the bugMap
        bugMap[pos].push_back(bug);
    }

    //Iterate over the bug map
    for (auto & iter : bugMap) {
        //Get the bugs in the current cell
        const vector<Bug*>& bugs = iter.second; //Gets the second value that is mapped to the location, in our case that is bug vector
                                                //After, we create a bugs variable that holds all bugs in the current square


        //If there are multiple bugs in the cell, fight
        if (bugs.size() > 1) {
            Bug* biggestBug = nullptr; //Set the bug pointer as nullptr until we assign a bug to it
            int totalSize = 0;
            vector<Bug*> equalBugs; //Vector that holds all bugs with the same size in a square

            //Go through bugs vector and find the biggest bug and get total size of the square
            for (Bug* bug : bugs) {
                if (!biggestBug || bug->getSize() > biggestBug->getSize()) { //We need !biggestBug as it is set to nullptr at the start
                    biggestBug = bug;
                }
                else if (bug->getSize() == biggestBug->getSize())
                {
                    equalBugs.push_back(bug);
                }
                totalSize += bug->getSize(); //Total size of the square needed for the final bug growth at the end of the fight
            }

            //If there are multiple bugs with equal size, randomly select one as the winner
            if (equalBugs.size() > 1) {
                biggestBug = equalBugs[rand() % equalBugs.size()]; //Determines the winner randomly, selecting random number from the equal bugs vector size
            }

            //Handles logic of removing dead bugs
            for (Bug* bug : bugs) {
                if (bug != biggestBug) {
                    bug->setAlive(false); // Mark the bug as dead
                    bug->setSize(0); // Update its size to 0
                    bugCount--;
                }
            }

            //Biggest bug grows based on eaten bugs size
            if (biggestBug) {
                biggestBug->setSize(biggestBug->getSize() + totalSize);
                winnerID = (biggestBug->getId());
            }
        }
    }
}

//Feature 3

void Board::findBugById() {
    int id;
    cout << "Enter an ID to find a bug: ";
    cin >> id;

    bool found = false;
    for (const auto& bug : bug_vector) { //iterator of bug_vector
        if (bug->getId() == id) {
            found = true;
            cout << "Bug found:" << endl;
            cout << "ID: " << bug->getId() << endl;
            if (dynamic_cast<Crawler*>(bug)) {
                cout << "Type: Crawler" << endl;
            } else if (dynamic_cast<Hopper*>(bug)) {
                cout << "Type: Hopper" << endl;
                Hopper* hopper = dynamic_cast<Hopper*>(bug);
                cout << "Hop Length: " << hopper->getHopLength() << endl; //Additional content for Hopper bug - hopLength
            }
            cout << "Location: (" << bug->getPosition().first << "," << bug->getPosition().second << ")" << endl;
            cout << "Size: " << bug->getSize() << endl;
            cout << "Direction: " << bug->directionToString(static_cast<int>(bug->getDirection())) << endl;
            cout << "Status: ";
            if (bug->isAlive()) {
                cout << "Alive" << endl;
            } else {
                cout << "Dead" << endl;
            }
            break; //Exits loop once bug is found
        }
    }

    if (!found) {
        cout << "Bug " << id << " not found." << endl;
    }
}


//Feature 2

void Board::displayAllBugs() {
    for (const auto& bug : bug_vector) { //Bug pointer to the bug_vector that iterates through it
        cout << bug->getId() << " "; //Display it based on current pointer to bug_vector
        if (dynamic_cast<Crawler*>(bug)) { //Dynamic cast required to determine what type of bug are we dealing with, if it is crawler display it
            cout << "Crawler "; //Display Crawler
        } else if (dynamic_cast<Hopper*>(bug)) { //Same here, it checks for type of bug
            cout << "Hopper "; //Display Hopper
            Hopper* hopper = dynamic_cast<Hopper*>(bug); //Create pointer to a hopper bug/object with hopper variable that we can use to display additional features of such bug
            cout << "(" << hopper->getHopLength() << ") "; //Display hopLength using hopper pointer
        }

        cout << "(" << bug->getPosition().first << "," << bug->getPosition().second << ") " //I have to get each coordinate separately, otherwise I would have to create an overloaded "<<" for pair to specify
             << bug->getSize() << " " //Displays Size
             << bug->directionToString(static_cast<int>(bug->getDirection())) << " "; //Displays direction Enum
        if (bug->isAlive()) { //Displays status - Alive or Dead
            cout << "Alive";
        } else {
            cout << "Dead";
        }
        cout << endl;
    }
}

//Feature 1

void Board::bugFileReader() {
    ifstream fin(R"(C:\Users\Thomas\CLionProjects\BugsLife\bugs.txt)");

    if (fin)
    {
        char type;
        int id, x, y, direction, size;
        int hop; //Additional value for Hopper bug
        bool alive = true; //Default value for alive status
        list<pair<int, int>> path; //Default value for list of paths taken

        char delimiter;
        while (fin >> type >> delimiter >> id >> delimiter >> x >> delimiter >> y >> delimiter >> direction >> delimiter >> size) {
            //Read additional data for Hopper bugs
            if (type == 'H') {
                fin >> delimiter >> hop;
            }

            //Allocating bugs on heap, pointer/address to it is allocated on bug_vector
            if (type == 'C') {
                bug_vector.push_back(new Crawler(id, make_pair(x, y), static_cast<Direction>(direction), size, alive, path));
            } else if (type == 'H') {
                bug_vector.push_back(new Hopper(id, make_pair(x, y), static_cast<Direction>(direction), size, alive, path, hop));
            } else {
                //Handle invalid type
                cout << "Invalid bug type: " << type << endl;
            }
        }

        fin.close(); //Close the file after reading
    } else {
        cout << "Unable to open file" << endl;
    }
}

string Board::getCurrentDateTime() {

    //Current time based on the computer system;
    time_t now = time(0);
    tm* ltm = localtime(&now); //Converts address of "now" to tm used for formatting stored in a ltm pointer

   stringstream ss; //Created a stringstream object to store date and time in one string
    ss << 1900 + ltm->tm_year << '-' //1900 is the start of year counting
       << 1 + ltm->tm_mon << '-' //holds 0-11, so we have to add 1 to start at correct month
       << ltm->tm_mday << '_' //Underscore to separate date and time
       << ltm->tm_hour << '-'
       << ltm->tm_min << '-'
       << ltm->tm_sec;

    return ss.str(); //Converts ss to string
}