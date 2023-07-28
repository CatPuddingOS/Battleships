#pragma once
#ifndef _GRID_
#define _GRID_

#include <SDL.h>
#include <iostream>
#include <vector>

class Grid {
public:
	int cellCount; //Product of both indecies of the 'size[]' member array

	Grid() {};
	~Grid() {};

	inline int GetGridSize();

	void Initialize(int row, int column, int screenWidth, int screenHeight);
	void CreateGrid();
	template<typename T>void CheckGrid(T& fleet);

	void Listen(int mouseX, int mouseY);
	void Update();
	void Draw(SDL_Renderer * renderer, int Xstart, int Ystart, int Xend, int Yend);
	void Clear();

private:
	int size[2]; //Number of rows and columns in the grid always size[2]
	int WIDTH; //Screen Height, used to instantiate cell objects
	int HEIGHT; //Screen Width, used to instantiate cell objects
	std::vector<std::unique_ptr<Cell>> cellArr; //Container for cell object pointers
};

#endif // !_GRID_
