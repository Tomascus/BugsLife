//
// Created by Thomas on 09/04/2024.
//

#ifndef BUGSLIFE_BUG_H
#define BUGSLIFE_BUG_H

#include <utility> //class that enables to use std::pair for position definition
#include <list> //class that enables to use std::list for path definition
#include <string>


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

    //Getters & Setters
public:
    int getId() const;
    void setId(int id);
    const std::pair<int, int> &getPosition() const;
    void setPosition(const std::pair<int, int> &position);
    Direction getDirection() const;
    void setDirection(Direction direction);
    std::string directionToString(int dir);
    int getSize() const;
    void setSize(int size);
    bool isAlive() const;
    void setAlive(bool alive);
    const std::list<std::pair<int, int>> &getPath() const;
    void setPath(const std::list<std::pair<int, int>> &path);

public:
    Bug(); //Empty constructor
    Bug(int id, std::pair<int, int> position, Direction direction, int size, bool alive, std::list<std::pair<int,int>> path);
    Bug(int id, std::pair<int, int> position, Direction direction, int size);

    virtual void move() = 0;
    bool isWayBlocked();
};



#endif //BUGSLIFE_BUG_H