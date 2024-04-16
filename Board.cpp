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

//Feature 7

void Board::displayAllCells() {

    //NO MAPS FOR NOW
    //Goes through the board and find coordinates of current cell
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            cout << "(" << i << "," << j << "): ";

            //Checks if the current cell contains any bugs
            bool hasBugs = false;
            for (const auto& bug : bug_vector) { //Iterates through bug vector to look for bugs
                const pair<int, int>& pos = bug->getPosition();
                if (pos.first == i && pos.second == j) { //If bugs position in bug vector is the same as current cell set hasBugs to true
                    hasBugs = true;

                    //Check for type
                    if (dynamic_cast<Crawler*>(bug)) {
                        cout << "Crawler " << bug->getId() << " ";
                    } else if (dynamic_cast<Hopper*>(bug)) {
                        cout << "Hopper " << bug->getId() << " ";
                    }
                }
            }

            //If no bugs are found, prints empty instead;
            if (!hasBugs) {
                cout << "Empty";
            }

            cout << endl; //Newline start
        }
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
            history += " Eaten by "; //IMPLEMENT LATER WITH EAT FUNCTIONALITY
        } else {
            history += " Alive!";  //Display that the bug is alive
        }
        history += "\n"; //Add newline for formatting
    }
    return history;
}


//Feature 4

void Board::tapBugBoard() {
    for (Bug* bug : bug_vector) {
        bug->move();
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
        int hop; // Additional value for Hopper bug
        bool alive = true; //Default value for alive status
        list<pair<int, int>> path; //Default value for list of paths taken

        char delimiter;
        while (fin >> type >> delimiter >> id >> delimiter >> x >> delimiter >> y >> delimiter >> direction >> delimiter >> size) {
            // Read additional data for Hopper bugs
            if (type == 'H') {
                fin >> delimiter >> hop;
            }

            //Allocating bugs on heap, pointer/address to it is allocated on bug_vector
            if (type == 'C') {
                bug_vector.push_back(new Crawler(id, make_pair(x, y), static_cast<Direction>(direction), size, alive, path));
            } else if (type == 'H') {
                bug_vector.push_back(new Hopper(id, make_pair(x, y), static_cast<Direction>(direction), size, alive, path, hop));
            } else {
                // Handle invalid type
                cout << "Invalid bug type: " << type << endl;
            }
        }

        fin.close(); // Close the file after reading
    } else {
        cout << "Unable to open file" << endl;
    }
}

string Board::getCurrentDateTime() {

    //Current time based on the computer system;
    time_t now = time(0);
    tm* ltm = localtime(&now); //Converts address of "now" to tm used for formatting stored in a ltm pointer

   stringstream ss; //Created a stringsteam object to store date and time in one string
    ss << 1900 + ltm->tm_year << '-' //1900 is the start of year counting
       << 1 + ltm->tm_mon << '-' //holds 0-11, so we have to add 1 to start at correct month
       << ltm->tm_mday << '_' //Underscore to separate date and time
       << ltm->tm_hour << '-'
       << ltm->tm_min << '-'
       << ltm->tm_sec;

    return ss.str(); //Converts ss to string
}