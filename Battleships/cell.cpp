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

	for (int i = 0; i < 5; i++)
	{
		pointsArr[i].x = X; 
		pointsArr[i].y = Y;
		break;

		if (i == 1)
		{
			X + Width == 1920 ? pointsArr[i].x = X + Width - 1.f : pointsArr[i].x = X + Width; 
			pointsArr[i].y = Y;
			break;
		}
		else if (i == 2)
		{
			X + Width == 1920 ? pointsArr[i].x = X + Width - 1.f : pointsArr[i].x = X + Width;
			Y + Height == 1080 ? pointsArr[i].y = Y + Height - 1.f : pointsArr[i].y = Y + Height;
			break;
		}
		else if (i == 3)
		{
			pointsArr[i].x = X;
			Y + Height == 1080 ? pointsArr[i].y = Y + Height - 1.f : pointsArr[i].y = Y + Height;
			break;
		}
		else if (i == 4)
		{
			pointsArr[i].x = X;
			pointsArr[i].y = Y;
			break;
		}
	}
}

void Cell::MouseEnter()
{
	std::cout << "\n\n\nEntered Cell " << ID << "\n\n\n";
	active = true;
}

void Cell::MouseLeave()
{
	active = false;
}

void Cell::Listen(int mouseX, int mouseY)
{
	if (active == true) { return; };

	if (mouseX >= cellBody.x && mouseX <= cellBody.x + cellBody.w && mouseY >= cellBody.y && mouseY <= cellBody.y + cellBody.h)
	{ MouseEnter(); }
}

void Cell::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);
	SDL_RenderFillRect(renderer, &cellBody);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, pointsArr, 5);
}