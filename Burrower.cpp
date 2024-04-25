//
// Created by Thomas on 25/04/2024.
//

#include <cstdlib>
#include <ctime>
#include "Burrower.h"

void Burrower::move() {
    if (isWayBlocked()) { //Implements Bug method isWayBlocked
        do {
            direction = RandomDirection();
        } while (isWayBlocked()); //Do while loop - first changes directions to attempt to face away from edges/walls
    }

    moveInDirection(direction); //Starts moving 1 unit in a defined direction
    path.push_back(position); //Pushes latest position to the path list
}

Direction Burrower::RandomDirection() {
    srand(time(nullptr));
    int randDirection = rand() % 4 + 1;
    switch (randDirection) {
        case 1:
            return Direction::NorthEast;
        case 2:
            return Direction::SouthEast;
        case 3:
            return Direction::SouthWest;
        case 4:
            return Direction::NorthWest;
    }
}

void Burrower::moveInDirection(Direction direction) {
    switch (direction) {
        case Direction::NorthEast:
            position.first += 1;
            position.second -= 1;
            break;
        case Direction::SouthEast:
            position.first += 1;
            position.second += 1;
            break;
        case Direction::SouthWest:
            position.first -= 1;
            position.second += 1;
            break;
        case Direction::NorthWest:
            position.first -= 1;
            position.second -= 1;
            break;
        default:
            break; //Does not move if any other direction is defined
    }
}