//
// Created by Thomas on 09/04/2024.
//

#include <cstdlib>
#include <ctime>
#include "Crawler.h"

void Crawler::move() {
    if (isWayBlocked()) { //Implements Bug method isWayBlocked
        do {
            direction = RandomDirection();
        } while (isWayBlocked()); //Do while loop - first changes directions to attempt to face away from edges/walls
    }

    moveInDirection(direction); //Starts moving 1 unit in a defined direction
    path.push_back(position); //Pushes latest position to the path list
}

Direction Crawler::RandomDirection() {
    std::srand(std::time(nullptr)); //current time for random seed
    int randDirection = std::rand() % 4 + 1; //Random generator from 1 to 4 for directions
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

void Crawler::moveInDirection(Direction direction) { //Basic move implementation as of now
    switch (direction) {
        case Direction::North:
            position.second -= 1;
            break;
        case Direction::East:
            position.first += 1;
            break;
        case Direction::South:
            position.second += 1;
            break;
        case Direction::West:
            position.first -= 1;
            break;
    }
}