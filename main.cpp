#include <SFML/Graphics.hpp>
#include <iostream>
#include "Crawler.h"
#include "Hopper.h"
#include "Board.h"
#include <vector>

using namespace sf;
using namespace std;

int main() {

    Board board;

    // Display the board
    board.display();

    std::vector<Bug*> bug_vector; //Create a vector of pointers to bug objects

    //Create specific bugs on heap
    Bug* crawler = new Crawler();
    Bug* hopper = new Hopper();

    //Store addresses of specific bugs in vector
    bug_vector.push_back(crawler);
    bug_vector.push_back(hopper);

    //Basic version, without mouse click
    for (Bug* bug : bug_vector) {  //Starts "move", specific to each bug type
        bug->move();
    }

    //Basic version, without alive logic
    for (Bug* bug : bug_vector) { //Deletes bugs from heap
        delete bug;
    }

    return 0;


}
