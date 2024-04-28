//
// Created by Thomas on 10/04/2024.
//

#ifndef BUGSLIFE_HOPPER_H
#define BUGSLIFE_HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
public:
    using Bug::Bug;  //Allows to use constructor from Parent Class "Bug"
    Hopper(int id, std::pair<int, int> position, Direction direction, int size, bool alive, std::list<std::pair<int,int>> path, int hopLength);

private:
    int hopLength;
public:
    int getHopLength() const;
    void setHopLength(int hopLength);
private:
    void move() override;  //Overrides the virtual function in Bug class to Crawler bug
    Direction RandomDirection();
    void moveInDirection(Direction direction, int hopLength);

};

#endif //BUGSLIFE_HOPPER_H
