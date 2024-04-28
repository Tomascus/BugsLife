//
// Created by Thomas on 10/04/2024.
//


#include <random>
#include "Hopper.h"


Hopper::Hopper(int id, std::pair<int, int> position, Direction direction, int size, bool alive,
               std::list<std::pair<int, int>> path, int hopLength) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->path = path;
    this->hopLength = hopLength;
}

void Hopper::move() {
    if (isWayBlocked()) { //Implements Bug method isWayBlocked
        do {
            direction = RandomDirection(); // Choose a new random direction
        } while (isWayBlocked()); //Do while loop - first changes directions to attempt to face away from edges/walls
    }

    moveInDirection(direction, hopLength); //Hops 2-4 units in a direction facing
    path.push_back(position); //Pushes latest position to the path list
}

Direction Hopper::RandomDirection() {

    //I switched to c++ random library, because srand caused inefficient times for decisions in random direction function
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 4); //Random int distribution between numbers 1 and 4
    int randDirection = dist(gen); //Generates random number using previously specified dist and a generator
    switch (randDirection) {
        case 1:
            return Direction::North;
        case 2:
            return Direction::East;
        case 3:
            return Direction::South;
        case 4:
            return Direction::West;
    }
}

void Hopper::moveInDirection(Direction direction, int hopLength) {
    switch (direction) {
        case Direction::North:
            if (position.second - hopLength >= 0) { //Checks if hopping would cause it to still be on the board
                position.second -= hopLength;
            } else {
                position.second = 0; //If not, bounce back to the nearest edge
            }
            break;
        case Direction::East:
            if (position.first + hopLength <= 9) {
                position.first += hopLength;
            } else {
                position.first = 9;
            }
            break;
        case Direction::South:
            if (position.second + hopLength <= 9) {
                position.second += hopLength;
            } else {
                position.second = 9;
            }
            break;
        case Direction::West:
            if (position.first - hopLength >= 0) {
                position.first -= hopLength;
            } else {
                position.first = 0;
            }
            break;
    }
}

int Hopper::getHopLength() const {
    return hopLength;
}

void Hopper::setHopLength(int hopLength) {
    this->hopLength = hopLength;
}


