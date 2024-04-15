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
void findBugById(const vector<Bug*>& bug_vector);
void tapBugBoard(vector<Bug*>& bug_vector);
string displayBugHistory(const vector<Bug*>& bug_vector);
void exit(const vector<Bug*>& bug_vector);

int main() {

    vector<Bug*> bug_vector; //Create a vector of pointers to bug objects

    //Reads the bugs from file and populate the vector
    bugFileReader(bug_vector);

    //Display all bugs in a formatted manner
    displayAllBugs(bug_vector);
    //findBugById(bug_vector);
    tapBugBoard(bug_vector);
    string output = displayBugHistory(bug_vector);
    cout << output << endl;
    exit(bug_vector);


    //Display the board
    /*Board board;
    board.display();*/


    //Basic version, without alive logic
    /*for (Bug* bug : bug_vector) { //Deletes bugs from heap
        delete bug;
    }*/

    return 0;
}

//Feature 6

void exit(const vector<Bug*>& bug_vector) {
    //Create the name for the file
    string filename = "bugs_life_history.out";
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

string displayBugHistory(const vector<Bug*>& bug_vector) {
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
            for (const auto& pos : path) { //Iterator of path list
                history += "(" + to_string(pos.first) + "," + to_string(pos.second) + "),";
            }
        } else {
            history += "No path recorded";
        }

        if (!bug->isAlive()) {
            history += " Eaten by "; //IMPLEMENT LATER WITH EAT FUNCTIONALITY
        } else {
            history += " Alive!"; // Display that the bug is alive
        }

        history += "\n"; //Add newline for formatting

    }
    return history;
}

//Feature 4

void tapBugBoard(vector<Bug*>& bug_vector) {
    for (Bug* bug : bug_vector) {
        bug->move();
    }
}

//Feature 3

void findBugById(const vector<Bug*>& bug_vector) {
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
            cout << "Direction: " << static_cast<int>(bug->getDirection()) << endl;
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

        cout << "(" << bug->getPosition().first << "," << bug->getPosition().second << ") " //I have to get each coordinate separately, otherwise I would have to create an overloaded "<<" for pair to specify
             << bug->getSize() << " " //Displays Size
             << static_cast<int>(bug->getDirection()) << " "; //Displays direction Enum
        if (bug->isAlive()) { //Displays status - Alive or Dead
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


