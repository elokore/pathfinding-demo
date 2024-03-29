// pathfinding-demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grid.h"

const int gridSize = 32;
sf::Vector2f screenSize(1600.0f, 800.0f);
Grid grid(gridSize, 4.0f, sf::Vector2f(800.0f, 800.0f));

static void onMouseButtonPressed(sf::Event* event) {
    sf::Vector2i cellLocation = grid.screenPositionToCellPosition(event->mouseButton.x, event->mouseButton.y);
    if (cellLocation.x < 0 || cellLocation.y < 0) return;
    
    grid.setCellState(cellLocation.x, cellLocation.y, Grid::CellState::Obstacle);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode((int) screenSize.x, (int) screenSize.y), "Pathfinding Demo");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
                onMouseButtonPressed(&event);
            }
        }

        window.clear();
        grid.drawGrid(&window);
        window.display();
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
