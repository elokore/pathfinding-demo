#pragma once
#include <SFML/Graphics.hpp>

class Grid {

public:
	enum CellState {
		Empty = 0,
		Obstacle = 1,
		Path = 2,
		PathEnd = 3,
		PathSearch = 4,
		PathStart = 5,
		Last
	};

	Grid(int gridSize, float gridSpacingPx, sf::Vector2f containerSizePx);
	~Grid();

	const void drawGrid(sf::RenderWindow* window);
	void setCellState(int xPos, int yPos, CellState state);
	CellState getCellState(int xPos, int yPos);
	const sf::Vector2i screenPositionToCellPosition(float x, float y);
private:
	int gridWidthCells;
	float cellSpacingPx;
	float cellSizePx;
	float spacingPx;
	sf::Vector2f containerSizePx;
	sf::RectangleShape*** grid;
};