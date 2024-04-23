//
// Created by Thomas on 10/04/2024.
//

#include <cstdlib>
#include <ctime>
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
            direction = RandomDirection();
        } while (isWayBlocked()); //Do while loop - first changes directions to attempt to face away from edges/walls
    }

    moveInDirection(direction, hopLength); //Hops 2-4 units in a direction facing
    path.push_back(position); //Pushes latest position to the path list
}

Direction Hopper::RandomDirection() {
    srand(time(nullptr)); //current time for random seed
    int randDirection = rand() % 4 + 1; //Random generator from 1 to 4 for directions
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

void Hopper::moveInDirection(Direction direction, int hopLength) { //Basic move implementation as of now
    switch (direction) {
        case Direction::North:
            position.second -= hopLength;
            break;
        case Direction::East:
            position.first += hopLength;
            break;
        case Direction::South:
            position.second += hopLength;
            break;
        case Direction::West:
            position.first -= hopLength;
            break;
    }
}

int Hopper::getHopLength() const {
    return hopLength;
}

void Hopper::setHopLength(int hopLength) {
    this->hopLength = hopLength;
}


