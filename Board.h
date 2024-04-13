//
// Created by Thomas on 10/04/2024.
//

#ifndef BUGSLIFE_BOARD_H
#define BUGSLIFE_BOARD_H

#include <vector>

#include <SFML/Graphics.hpp>


class Board {
public:
    Board(); // Constructor for board
    void display();
private:
    static constexpr int boardSize = 10; //Size of the board
    std::vector<std::vector<sf::RectangleShape>> cells; // vector for board cells
};


#endif //BUGSLIFE_BOARD_H
