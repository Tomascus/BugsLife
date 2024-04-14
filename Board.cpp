//
// Created by Thomas on 10/04/2024.
//

#include "Board.h"
using namespace sf;

Board::Board() {
    for (int i = 0; i < boardSize; ++i) { //Define a board height and width
        std::vector<RectangleShape> row;
        for (int j = 0; j < boardSize; ++j) {
            RectangleShape cell(Vector2f(50, 50)); // Defined size of each cell
            cell.setPosition(j * 50, i * 50); // Position the cell on the board based on the for loop state
            if ((i + j) % 2 == 0) {
                cell.setFillColor(Color(76,153,0)); // Custom RGB Green color for even cells
            } else {
                cell.setFillColor(Color(102, 51, 0)); // Custom RGB Brown color for odd cells
            }
            row.push_back(cell); //Pushes cells to row vector of the board
        }
        board.push_back(row); //Pushes each cell from rows to 2D vector of the board
    }
}

void Board::display() {
    sf::RenderWindow window(VideoMode(500, 500), "Bug Board");

    // Main loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        // Draw the board cells
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                window.draw(board[i][j]);
            }
        }

        window.display();
    }
}