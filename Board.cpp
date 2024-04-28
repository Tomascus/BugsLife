//
// Created by Thomas on 10/04/2024.
//

#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Burrower.h"
#include "SuperBug.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <unistd.h>
#include <valarray>

using namespace sf;
using namespace std;

Board::Board() {
    //Initialize the board
    for (int i = 0; i < boardSize; ++i) { //Define a board height and width
        vector<RectangleShape> row;
        for (int j = 0; j < boardSize; ++j) {
            RectangleShape cell(Vector2f(80, 80)); // Defined size of each cell
            cell.setPosition(j * 80, i * 80); //Position the cell on the board based on the for loop state
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



//Sprites from: https://admurin.itch.io/admurins-flora-and-fauna-0 and https://admurin.itch.io/admurins-insects
void Board::loadTextures() //Separate method for loading textures/sprites, so they only generate once at the start
{
    if (!texture1.loadFromFile("sprites/Crawler.png")) { //Checks if it correctly loads the texture
        cout << "Failed to load texture1 from file" << endl;
    }
    if (!texture2.loadFromFile("sprites/Hopper.png")) {
        cout << "Failed to load texture2 from file" << endl;
    }
    if (!texture3.loadFromFile("sprites/Burrower.png")) {
        cout << "Failed to load texture3 from file" << endl;
    }
    if (!texture4.loadFromFile("sprites/Superbug.png")) {
        cout << "Failed to load texture4 from file" << endl;
    }
}

//Feature 9

void Board::runSimulation() {

    loadTextures();
    bugFileReader();
    cout << "Welcome to the Bug's Life, The Game!" << endl;
    cout << endl;
    displayAllBugs();
    cout << "" << endl;

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Bug Board");

    //Runs the game until there is one bug left
    while (bugCount != 1) {
        window.clear(sf::Color::White); //Clears the window

        // Event loop
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    for (const auto& bug : bug_vector) { //Go through the bug vector until we find the superbug
                        if (dynamic_cast<SuperBug*>(bug)) {
                            superBug = dynamic_cast<SuperBug*>(bug); //Create a variable superBug
                            break;
                        }
                    }
                    if (superBug) { //use superBug variable to handle input (key press) from the superbug class
                        superBug->handleInput(event.key.code);
                    }
                    break;
                default:
                    break;
            }
        }

        //Draw the board squares
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                window.draw(board[i][j]);
            }
        }

        //Draw bugs on the board
        for (const auto& bug : bug_vector) {

            sf::Sprite sprite; //Created SFML sprite for the bug that is checked based on its type to decide which one to use
            if (dynamic_cast<Crawler*>(bug)) {
                sprite.setTexture(texture1);
            } else if (dynamic_cast<Hopper*>(bug)) {
                sprite.setTexture(texture2);
            } else if (dynamic_cast<Burrower*>(bug)) {
                sprite.setTexture(texture3);
            } else if (dynamic_cast<SuperBug*>(bug)) {
                sprite.setTexture(texture4);
            }

            float scale = 10; //Scale value used to scale the initial bug, as all of them are based on bugSize, which is very small at the start
            float bugSize = sqrt(bug->getSize()); //Used math(Square root) to slow the incremental size gaining, so that bugs do not overflow the squares very fast

            //Setting scale based on the initial bug size divided by the texture sizes to keep the aspect ratio
            sprite.setScale(scale * bugSize / sprite.getTexture()->getSize().x, scale * bugSize / sprite.getTexture()->getSize().y);

            //Calculate the center position of the square that is 80x80, using offset of half a square for centering
            int squareX = (bug->getPosition().first + 0.5) * 80;
            int squareY = (bug->getPosition().second + 0.5) * 80;

            //Sets the origin of the sprite to the center based on x and y coordinates
            sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);

            //Sets the position of the sprite on the square
            sprite.setPosition(squareX, squareY);

            //Draw the bug on the window/board
            window.draw(sprite);
        }


        //Display the window/board
        window.display();

        //Starts the movement
        tapBugBoard();

        //Additional information while the game is running, can be uncommented for testing purposes
        /*string output = displayBugHistory();
        cout << output << endl;
        displayAllCells();
        displayAllBugs();
        cout << "" << endl;
        cout << bugCount << endl;
        cout << endl;*/

        //Wait for 1 second
        sleep(1);
    }
    exit(); //Exits the game when one bug remains and outputs the bug history to the file

    //Free up memory
    for (auto& bug : bug_vector) {
        delete bug;
    }
    bug_vector.clear(); //Clears the vector, making it empty, ready to be used again
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
            if (bugMap.count(pos)) {
                const vector<Bug*>& bugs = bugMap[pos]; //Create a vector of bugs for current square in case there are multiple bugs inside
                for (int i = 0; i < bugs.size(); ++i) {
                    Bug* bug = bugs[i]; //Pointer to bug in the vector
                    if (dynamic_cast<Crawler*>(bug)) {
                        cout << "Crawler " << bug->getId() << " ";
                    } else if (dynamic_cast<Burrower*>(bug)) {
                        cout << "Burrower " << bug->getId() << " ";
                    } else if (dynamic_cast<SuperBug*>(bug)) {
                        cout << "SuperBug " << bug->getId() << " ";
                    } else if (dynamic_cast<Hopper*>(bug)) {
                        cout << "Hopper " << bug->getId() << " ";
                    }
                }
            } else {
                cout << "empty"; //No bugs in this cell
            }
            cout << endl;
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
        fout << displayBugHistory(); //Write bug history to the file

        fout.close(); //Close the file
        cout << "Bug life history saved to: " << filename << endl;
    } else {
        cout << "Unable to open file for writing" << endl;
    }
}

//Feature 5

string Board::displayBugHistory() {
    string history;

    for (const auto& bug : bug_vector) { //Iterate through bug vector
        history += to_string(bug->getId()) + " "; //Display Bug ID

        //Display Bug Type
        if (dynamic_cast<Crawler*>(bug)) {
            history += "Crawler ";
        } else if (dynamic_cast<Burrower*>(bug)) {
            history += "Burrower ";
        } else if (dynamic_cast<SuperBug*>(bug)) {
            history += "SuperBug ";
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
            history += " Eaten by " + to_string(bug->getWinnerID());
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
    bugMap.clear();

    //Iterate over each bug in the bug_vector and move it
    for (Bug* bug : bug_vector) {
        if (bug->isAlive()) { //Dead bugs do not move
            bug->move();
        } if (bug->isAlive() || bug->getSize()!=0) {
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


        //If there is at least one bug in the cell, fight - needed if superbug invades other squares with one bug
        if (!bugs.empty()) {
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
                totalSize += bug->getSize(); //Calculation of bug sizes inside the square
            }

            //If there are multiple bugs with equal size, randomly select one as the winner
            if (equalBugs.size() > 1) {
                biggestBug = equalBugs[rand() % equalBugs.size()]; //Determines the winner randomly, selecting random number from the equal bugs vector size
            }

            //Handles logic of fight outcome, deciding winner and losers
            for (auto it = bugs.begin(); it != bugs.end(); ++it) {
                Bug* bug = *it;
                bug->setWinnerID(biggestBug->getId()); // Set the winnerID
                if (bug != biggestBug) {
                    bug->setAlive(false); //Change the alive status to false
                    bug->setSize(0); //Update the size to 0
                }
            }
            //Biggest bug grows based on eaten bugs size
            biggestBug->setSize(biggestBug->getSize() + totalSize - biggestBug->getSize()); //We subtract the current size from the new size so that the bug only grows by the totalSize, not its own size aswell
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
            } else if (dynamic_cast<Burrower*>(bug)) {
                cout << "Type: Burrower" << endl;
            } else if (dynamic_cast<SuperBug*>(bug)) {
                cout << "Type: SuperBug" << endl;
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
        } else if (dynamic_cast<Burrower*>(bug)) { //Dynamic cast required to determine what type of bug are we dealing with, if it is burrower display it
            cout << "Burrower "; //Display Crawler
        } else if (dynamic_cast<SuperBug*>(bug)) { //Dynamic cast required to determine what type of bug are we dealing with, if it is superbug display it
            cout << "SuperBug "; //Display Crawler
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
    ifstream fin("bugs.txt");

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
            } else if (type == 'B') {
                bug_vector.push_back(new Burrower(id, make_pair(x, y), static_cast<Direction>(direction), size, alive, path));
            } else if (type == 'S') {
                bug_vector.push_back(new SuperBug(id, make_pair(x, y), static_cast<Direction>(direction), size, alive, path));
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
