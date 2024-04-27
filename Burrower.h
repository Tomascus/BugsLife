//
// Created by Thomas on 25/04/2024.
//

#ifndef BUGSLIFE_BURROWER_H
#define BUGSLIFE_BURROWER_H

#include "Bug.h"

//New bug that moves diagonally

class Burrower : public Bug {
public:
    using Bug::Bug;  //Allows to use constructor from Parent Class "Bug"

    void move() override;  //Overrides the virtual function in Bug class to Crawler bug
    Direction RandomDirection();
    void moveInDirection(Direction direction);
};

#endif //BUGSLIFE_BURROWER_H
