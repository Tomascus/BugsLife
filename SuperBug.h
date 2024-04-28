//
// Created by Thomas on 27/04/2024.
//

#ifndef BUGSLIFE_SUPERBUG_H
#define BUGSLIFE_SUPERBUG_H

#include <SFML/Window/Keyboard.hpp>
#include "Bug.h"

class SuperBug : public Bug {
public:
    using Bug::Bug;  //Allows to use constructor from Parent Class "Bug"

    void move() override; //Overrides the virtual function in Bug class to SuperBug
    void handleInput(sf::Keyboard::Key key);
    void moveInDirection(Direction direction);
};

#endif //BUGSLIFE_SUPERBUG_H
