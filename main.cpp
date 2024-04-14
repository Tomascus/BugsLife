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

int main() {

    vector<Bug*> bug_vector; //Create a vector of pointers to bug objects

    //Reads the bugs from file and populate the vector
    bugFileReader(bug_vector);


    //Display the board
    Board board;
    board.display();

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

//Feature 1

void readBugsFromFile(vector<Bug*>& bug_vector) {

    ifstream fin("bugs.txt");

    if (fin) // ensures the file input stream is opened correctly
    {
        char type;
        int id, x, y, direction, size;
        int hop; // Additional value for Hopper bug

        while (fin >> type >> id >> x >> y >> direction >> size) {
            if (type == 'H') {
                fin >> hop; // Read additional data for Hopper bug
            }

            //Allocating bugs on heap, pointer/address to it is allocated on bug_vector
            if (type == 'C') {
                bug_vector.push_back(new Crawler(id, make_pair(x, y), static_cast<Direction>(direction), size));
            } else if (type == 'H') {
                bug_vector.push_back(new Hopper(id, make_pair(x, y), static_cast<Direction>(direction), size, hop));
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
