//
// Created by Thomas on 09/04/2024.
//

#ifndef BUGSLIFE_CRAWLER_H
#define BUGSLIFE_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    using Bug::Bug;  //Allows to use constructor from Parent Class "Bug"

    void move() override;  //Overrides the virtual function in Bug class to Crawler bug
    Direction RandomDirection();
    void moveInDirection(Direction direction);
};

#endif //BUGSLIFE_CRAWLER_H
