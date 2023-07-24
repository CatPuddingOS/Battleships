#include <SDL.h>
#include "unity_build.h"

void Grid::Initialize(int row, int col, int screenWidth, int screenHeight) {
	//Lazy because 'default contructor'
	size[0] = row;
	size[1] = col;
	WIDTH = screenWidth;
	HEIGHT = screenHeight;
	cellCount = row * col;
	cellArr.resize(cellCount);

	float projectedX = WIDTH / size[0]; //Distance between X lines (Vertical)
	float projectedY = HEIGHT / size[1]; //Distance between Y lines (Horizontal)
	int lastX = 0;
	int lastY = 0;

	//Populate cells[] with properly sized and positioned cells
	for (int i = 0; i < cellCount; i++)
	{
		cellArr[i] = (std::make_unique<Cell>());
		cellArr[i]->Initialize(i, lastX, lastY, projectedX, projectedY);
		lastX += projectedX;
		if (lastX >= WIDTH)
		{
			lastX = 0;
			lastY += projectedY;
		}
	}
}

void Grid::Listen(int mouseX, int mouseY)
{
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
