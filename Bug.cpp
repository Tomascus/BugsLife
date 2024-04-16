//
// Created by Thomas on 09/04/2024.
//

#include "Bug.h"

Bug::Bug() //Default constructor
{
    this->id = 1;
    this->position = std::make_pair(0, 0); //Default position - top left corner of the map
    this->direction = Direction::North;
    this->size = 1;
    this->alive = true;
    this->path = std::list<std::pair<int,int>>(); //Empty path
}

Bug::Bug(int id, std::pair<int, int> position, Direction direction, int size, bool alive, std::list<std::pair<int,int>> path)
{
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->path = path;
}

Bug::Bug(int id, std::pair<int, int> position, Direction direction, int size)
{
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
}


bool Bug::isWayBlocked() {

    std::pair<int, int> currentPosition = getPosition(); //Get current position of a bug

    //Check if the bug is at any edge of the board in the direction it is currently facing
    switch (getDirection()) { //Switch statement with cases with each direction to check for corners/edges
        case Direction::North:
            if (currentPosition.second == 0) { //Way is blocked at the north edge of the board
                return true;
            }
            break;
        case Direction::East:
            if (currentPosition.first == 9) { //Way is blocked at the east edge of the board
                return true;
            }
            break;
        case Direction::South:
            if (currentPosition.second == 9) { //Way is blocked at the south edge of the board
                return true;
            }
            break;
        case Direction::West:
            if (currentPosition.first == 0) { //Way is blocked at the west edge of the board
                return true;
            }
            break;
    }
    return false; //Way is not blocked in the bugs current facing direction
}

int Bug::getId() const {
    return id;
}

void Bug::setId(int id) {
    Bug::id = id;
}

const std::pair<int, int> &Bug::getPosition() const {
    return position;
}

void Bug::setPosition(const std::pair<int, int> &position) {
    Bug::position = position;
}

Direction Bug::getDirection() const {
    return direction;
}

void Bug::setDirection(Direction direction) {
    Bug::direction = direction;
}

std::string Bug::directionToString(int dir) {
    switch (dir) {
        case 1:
            return "North";
        case 2:
            return "East";
        case 3:
            return "South";
        case 4:
            return "West";
        default:
            return "Unknown";
    }
}

int Bug::getSize() const {
    return size;
}

void Bug::setSize(int size) {
    Bug::size = size;
}

bool Bug::isAlive() const {
    return alive;
}

void Bug::setAlive(bool alive) {
    Bug::alive = alive;
}

const std::list<std::pair<int, int>> &Bug::getPath() const {
    return path;
}

void Bug::setPath(const std::list<std::pair<int, int>> &path) {
    Bug::path = path;
}



