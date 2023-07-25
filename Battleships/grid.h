#pragma once
#ifndef _GRID_
#define _GRID_

#include <SDL.h>
#include <iostream>
#include <vector>

class Grid {
public:
	//Array holding the size of the grid to be used.
	//Index 0 controls the # of rows. Index 1; the # of columns.

	Grid() {};
	~Grid() {};

	//Supposed to be used between rounds to augment grid size
	void Initialize(int row, int column, int screenWidth, int screenHeight);

	void Listen(int mouseX, int mouseY);
	void Update();
	void Draw(SDL_Renderer * renderer, int Xstart, int Ystart, int Xend, int Yend);
	void Clear();

private:
	int size[2]; //Number of rows and columns in the grid always size[2]
	int WIDTH; //Screen Height, used to instantiate cell objects
	int HEIGHT; //Screen Width, used to instantiate cell objects
	int cellCount; //Product of both indecies of the 'size[]' member array
	std::vector<std::unique_ptr<Cell>> cellArr; //Container for cell object pointers
};

#endif // !_GRID_
