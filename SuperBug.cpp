//
// Created by Thomas on 27/04/2024.
//

#include "SuperBug.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

void SuperBug::move() { //Only path history is required for move function as player moved by pressing keys using handleInput
        path.push_back(position); //Pushes latest position to the path list
}

void SuperBug::handleInput(Keyboard::Key key) { //handleInput method that is invoked in the board class to check player's input
    Direction direction;
    switch (key) {
        case Keyboard::Up:
            direction = Direction::North;
            break;
        case Keyboard::Down:
            direction = Direction::South;
            break;
        case Keyboard::Left:
            direction = Direction::West;
            break;
        case Keyboard::Right:
            direction = Direction::East;
            break;
        default:
            return; //Ignores other keys pressed
    }
    moveInDirection(direction);
}

void SuperBug::moveInDirection(Direction direction) {
    switch (direction) {
        case Direction::North:
                if (position.second > 0) { //Checks if the movement would take the bug outside the board boundaries
                    position.second -= 1; //Move by one
                } else {
                    position.second = 0; //If so, teleport the player back
                }
            break;
        case Direction::South:
                if (position.second < 9) {
                    position.second += 1;
                } else {
                    position.second = 9;
                }
            break;
        case Direction::East:
                if (position.first < 9) {
                    position.first += 1;
                } else {
                    position.first = 9;
                }
            break;
        case Direction::West:
                if (position.first > 0) {
                    position.first -= 1;
                } else {
                    position.first = 0;
                }
            break;
    }
}



