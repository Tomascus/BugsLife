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


bool Bug::isWayBlocked()
{
//Implement after board creation
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



