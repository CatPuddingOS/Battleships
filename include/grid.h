#pragma once
#ifndef _GRID_
#define _GRID_

#include <iostream>
#include <vector>

#include "cell.h"
#include "fleet.h"

enum {
	Vertical = 10,
	Horizontal = 1
};

class Grid {
public:
	int cellCount; //Product of both indecies of the 'size[]' member array

	Grid() {};
	~Grid() {};

	inline int GetGridSize();

	void Initialize(int row, int column, int screenWidth, int screenHeight);
	void CreateGrid();
	std::vector<int> AssignLocation(int size);
	std::vector<int> ShiftForward(std::vector<int> vec, int orientation);
	std::vector<int> ShiftBackward(std::vector<int> vec, int orientation);
	void ResetGrid();

	template<typename T> void CheckGrid(T& fleet)
	{
		//Reset occupied for all cells (band-aid fix)
		for (int c = 0; c < cellCount; c++)
		{
			cellArr[c]->occupied = false;
		}

		//Set cells that match the ships location are flagged occupied
		std::vector<int> vec;
		for (int s = 0; s < fleet->GetSize(); s++)
		{
			vec = fleet->fleetArr[s].GetLocation();
			for (int i = 0; i < vec.size(); i++)
			{
				cellArr[vec[i]]->occupied = true;
				cellArr[vec[i]]->occupant = fleet->fleetArr[s].GetName();
			}
		}
	}

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
