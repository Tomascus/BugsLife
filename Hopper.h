//
// Created by Thomas on 10/04/2024.
//

#ifndef BUGSLIFE_HOPPER_H
#define BUGSLIFE_HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
public:
    using Bug::Bug;  //Allows to use constructor from Parent Class "Bug"

private:
    int hopLength = std::rand() % 4 + 2;

    void move() override;  //Overrides the virtual function in Bug class to Crawler bug
    Direction RandomDirection();
    void moveInDirection(Direction direction, int hopLength);
};

#endif //BUGSLIFE_HOPPER_H
