//
// Created by Thomas on 10/04/2024.
//

#include "Board.h"

Board::Board() {
    for (int i = 0; i < boardSize; ++i) { //Define a board height and width
        std::vector<sf::RectangleShape> row;
        for (int j = 0; j < boardSize; ++j) {
            sf::RectangleShape cell(sf::Vector2f(50, 50)); // Defined size of each cell
            cell.setPosition(j * 50, i * 50); // Position the cell on the board based on the for loop state
            if ((i + j) % 2 == 0) {
                cell.setFillColor(sf::Color(76,153,0)); // Custom RGB Green color for even cells
            } else {
                cell.setFillColor(sf::Color(102, 51, 0)); // Custom RGB Brown color for odd cells
            }
            row.push_back(cell); //Pushes cells to row vector of the board
        }
        cells.push_back(row); //Pushes each cell from rows to 2D vector of the board
    }
}

//Handles SFML board display

void Board::display() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Board Example");

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Draw the board cells
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                window.draw(cells[i][j]);
            }
        }

        window.display();
    }
}