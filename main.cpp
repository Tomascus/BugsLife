#include <SFML/Graphics.hpp>
#include <iostream>
#include "Crawler.h"
#include "Hopper.h"
#include "Board.h"
#include <vector>
#include <fstream>

using namespace sf;
using namespace std;

void bugFileReader(vector<Bug*>& bug_vector);
void displayAllBugs(const vector<Bug*>& bug_vector);

int main() {

    vector<Bug*> bug_vector; //Create a vector of pointers to bug objects

    //Reads the bugs from file and populate the vector
    bugFileReader(bug_vector);

    //Display all bugs in a formatted manner
    displayAllBugs(bug_vector);


    //Display the board
    /*Board board;
    board.display();*/

    //Basic version, without mouse click
    for (Bug* bug : bug_vector) {  //Starts "move", specific to each bug type
        bug->move();
    }

    //Basic version, without alive logic
    /*for (Bug* bug : bug_vector) { //Deletes bugs from heap
        delete bug;
    }*/

    return 0;
}

//Feature 2

void displayAllBugs(const vector<Bug*>& bug_vector) {
    for (const auto& bug : bug_vector) { //Bug pointer to the bug_vector that iterates through it
        cout << bug->getId() << " "; //Display it based on current pointer to bug_vector
        if (dynamic_cast<Crawler*>(bug)) { //Dynamic cast required to determine what type of bug are we dealing with, if it is crawler display it
            cout << "Crawler "; //Display Crawler
        } else if (dynamic_cast<Hopper*>(bug)) { //Same here, it checks for type of bug
            cout << "Hopper "; //Display Hopper
            Hopper* hopper = dynamic_cast<Hopper*>(bug); //Create pointer to a hopper bug/object with hopper variable that we can use to display additional features of such bug
            cout << "(" << hopper->getHopLength() << ") "; //Display hopLength using hopper pointer
        }
        // Display location, size, direction, and status
        cout << "(" << bug->getPosition().first << "," << bug->getPosition().second << ") " //I have to get each coordinate separately, otherwise I would have to create an overloaded "<<" for pair to specify
             << bug->getSize() << " " //Displays Size
             << static_cast<int>(bug->getDirection()) << " "; //Displays direction Enum
        if (bug->isAlive()) {
            cout << "Alive";
        } else {
            cout << "Dead";
        }
        cout << endl;
    }
}

//Feature 1

void bugFileReader(vector<Bug*>& bug_vector) {

    ifstream fin(R"(C:\Users\Thomas\CLionProjects\BugsLife\bugs.txt)");

    if (fin) //Ensures the file input stream is opened correctly
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


