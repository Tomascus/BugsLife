//
// Created by Thomas on 09/04/2024.
//

#ifndef BUGSLIFE_BUG_H
#define BUGSLIFE_BUG_H

#include <utility> //class that enables to use std::pair for position definition
#include <list> //class that enables to use std::list for path definition


enum class Direction { //separate enum class that includes all directions
    North = 1,
    East = 2,
    South = 3,
    West = 4
};

class Bug {
protected:
    int id;
    std::pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    std::list<std::pair<int,int>> path;

public:
    Bug(); //Empty constructor
    Bug(int id, std::pair<int, int> position, Direction direction, int size, bool alive, std::list<std::pair<int,int>> path);


    virtual void move() = 0;
    bool isWayBlocked(); //Implement after board creation
};



#endif //BUGSLIFE_BUG_H
