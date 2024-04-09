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

bool Bug::isWayBlocked()
{
//Implement after board creation
}