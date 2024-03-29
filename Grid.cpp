#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.h"

sf::Color stateColors[6] = {
    sf::Color(64, 64, 64),
    sf::Color(255, 0, 0),
    sf::Color(0, 0, 255),
    sf::Color(0, 255, 0),
    sf::Color(255, 165, 0),
    sf::Color(255, 0, 255)
};

Grid::Grid(int gridWidthCells, float cellSpacingPx, sf::Vector2f containerSizePx) {
	float minDimension = fminf(containerSizePx.x, containerSizePx.y);
	this->cellSizePx = (minDimension - (cellSpacingPx * gridWidthCells)) / gridWidthCells;
    this->grid = new sf::RectangleShape**[gridWidthCells];
    this->gridWidthCells = gridWidthCells;
    this->cellSpacingPx = cellSpacingPx;

    float posIncrement = this->cellSizePx + cellSpacingPx;
    for (int x = 0; x < gridWidthCells; x++) {
        this->grid[x] = new sf::RectangleShape*[gridWidthCells];

        for (int y = 0; y < gridWidthCells; y++) {
            sf::RectangleShape* square = new sf::RectangleShape(sf::Vector2f(this->cellSizePx, this->cellSizePx));
            square->setPosition(sf::Vector2f(x * posIncrement, y * posIncrement));
            square->setFillColor(stateColors[(int)Grid::CellState::Empty]);
            this->grid[x][y] = square;
        }
    }
}

void Grid::setCellState(int xPos, int yPos, Grid::CellState state) {
    sf::RectangleShape* cell = this->grid[xPos][yPos];
    sf::Color cellColor = stateColors[(int)state];
    cell->setFillColor(cellColor);
}

Grid::CellState Grid::getCellState(int xPos, int yPos) {
    sf::RectangleShape* cell = this->grid[xPos][yPos];
    sf::Uint32 cellColor = cell->getFillColor().toInteger();

    for (int x = Grid::CellState::Empty; x != Grid::CellState::Last; x++) {
        sf::Color color = stateColors[x];
        if (color.toInteger() == cellColor) {
            return (Grid::CellState)x;
        }
    }
}

/*
    Converts a pixel screen position to the position of a cell in the grid.
    If no conversion can be made a vector of (-1, -1) will be returned.
*/
const sf::Vector2i Grid::screenPositionToCellPosition(float x, float y) {
    float increment = this->cellSizePx + this->cellSpacingPx;
    int cellX = floorf(x / increment);
    int cellY = floorf(y / increment);

    sf::Vector2f cellTopLeft(cellX * increment, cellY * increment);
    sf::Vector2f cellBottomRight = cellTopLeft + sf::Vector2f(this->cellSizePx, this->cellSizePx);
    bool isWithinCell = (x >= cellTopLeft.x && x <= cellBottomRight.x) && (y >= cellTopLeft.y && y <= cellBottomRight.y);
    bool isCellWithinGrid = (cellX < this->gridWidthCells && cellY < this->gridWidthCells) && (cellX >= 0 && cellY >= 0);

    if (isWithinCell && isCellWithinGrid) {
        return sf::Vector2i(cellX, cellY);
    }
    else {
        return sf::Vector2i(-1, -1);
    }
}

const void Grid::drawGrid(sf::RenderWindow* window) {
    for (int x = 0; x < this->gridWidthCells; x++) {
        for (int y = 0; y < this->gridWidthCells; y++) {
            sf::RectangleShape cell = *this->grid[x][y];
            window->draw(cell);
        }
    }
}

Grid::~Grid() {
    //Unallocate memory used for the grid
    for (int x = 0; x < this->gridWidthCells; x++) {
        delete[] this->grid[x];
    }
    delete[] this->grid;
}