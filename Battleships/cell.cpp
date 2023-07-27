#include <SDL.h>
#include "unity_build.h"

//X and Y are the intervals at which each line will be drawn
void Cell::Initialize(int id, float xpos, float ypos, float width, float height)
{
	ID = id;
	occupied = false;
	struck = false;
	active = false;
	
	X = xpos;
	Y = ypos;
	Width = width;
	Height = height;

	cellBody.x = X;
	cellBody.y = Y;
	cellBody.w = Width;
	cellBody.h = Height;

	//Needs a cleanup
	for (int i = 0; i < 5; i++)
	{
		pointsArr[i].x = X; 
		pointsArr[i].y = Y;

		if (i == 1)
		{
			X + Width == 1920 ? pointsArr[i].x = X + Width - 1.f : pointsArr[i].x = X + Width; 
			pointsArr[i].y = Y;
		}
		else if (i == 2)
		{
			X + Width == 1920 ? pointsArr[i].x = X + Width - 1.f : pointsArr[i].x = X + Width;
			Y + Height == 1080 ? pointsArr[i].y = Y + Height - 1.f : pointsArr[i].y = Y + Height;
		}
		else if (i == 3)
		{
			pointsArr[i].x = X;
			Y + Height == 1080 ? pointsArr[i].y = Y + Height - 1.f : pointsArr[i].y = Y + Height;
		}
		else if (i == 4)
		{
			pointsArr[i].x = X;
			pointsArr[i].y = Y;
		}
	}
}

bool Cell::MouseEnter(int x, int y)
{
	if (x >= cellBody.x && x <= cellBody.x + cellBody.w && y >= cellBody.y && y <= cellBody.y + cellBody.h)
	{
		if (active == true) { return true; }

		//std::cout << "\n\nEntered Cell " << ID << "\n\n";
		active = true;
		return true;
	}
	return false;
}

void Cell::MouseLeave()
{
	//std::cout << "\n\nLeft Cell " << ID << "\n\n";
	active = false;
}

void Cell::Listen(int mouseX, int mouseY)
{
	if (!MouseEnter(mouseX, mouseY) && active == true)
	{
		MouseLeave();
	}
}

void Cell::Render(SDL_Renderer* renderer)
{
	active == true ? SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255) : SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);
	if (occupied == true)
	{
		SDL_SetRenderDrawColor(renderer, 0, 50, 0, 255);
	}
	SDL_RenderFillRect(renderer, &cellBody);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, pointsArr, 5);
}