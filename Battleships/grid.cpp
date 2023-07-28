#include <SDL.h>
#include "unity_build.h"

inline int Grid::GetGridSize()
{
	return cellCount;
}

void Grid::Initialize(int row, int col, int screenWidth, int screenHeight) {
	//Lazy because 'default contructor'
	size[0] = row;
	size[1] = col;
	WIDTH = screenWidth;
	HEIGHT = screenHeight;
	cellCount = row * col;
	cellArr.resize(cellCount);
}

void Grid::CreateGrid()
{
	float newCellWidth = WIDTH / size[0]; //Distance between X lines (Vertical)
	float newCellHeight = HEIGHT / size[1]; //Distance between Y lines (Horizontal)
	int lastPointX = 0;
	int lastPointY = 0;

	//Populate cells[] with properly sized and positioned cells
	for (int i = 0; i < cellCount; i++)
	{
		cellArr[i] = (std::make_unique<Cell>());
		cellArr[i]->Initialize(i, lastPointX, lastPointY, newCellWidth, newCellHeight);
		lastPointX += newCellWidth;
		if (lastPointX >= WIDTH)
		{
			lastPointX = 0;
			lastPointY += newCellHeight;
		}
	}
}

template<typename T> void Grid::CheckGrid(T &fleet)
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
		}
	}
}

void Grid::Listen(int mouseX, int mouseY)
{
	//Listen for changes in each cell of the grid
	for (int i = 0; i < cellCount; i++)
	{
		cellArr[i]->Listen(mouseX, mouseY);
	}
}

void Grid::Draw(SDL_Renderer * renderer, int Xstart, int Ystart, int Xend, int Yend) 
{
	for (int c = 0; c < cellCount; c++)
	{
		cellArr[c]->Render(renderer);
	}
}
