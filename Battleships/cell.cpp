#include <SDL.h>
#include "unity_build.h"

//X and Y are the intervals at which each line will be drawn
void Cell::Initialize(int id, int xpos, int ypos, int width, int height)
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

	color = std::make_unique<Color>();

	//Needs a cleanup
	for (int i = 0; i < 5; i++)
	{
		if (i == 1)
		{
			X + Width == 1920 ? pointsArr[i].x = X + Width - 1 : pointsArr[i].x = X + Width; 
			hitOverlay[2].x = pointsArr[i].x;
			hitOverlay[2].y = pointsArr[i].y = Y;
		}
		else if (i == 2)
		{
			X + Width == 1920 ? pointsArr[i].x = X + Width - 1 : pointsArr[i].x = X + Width;
			Y + Height == 1080 ? pointsArr[i].y = Y + Height - 1 : pointsArr[i].y = Y + Height;
			hitOverlay[1].x = pointsArr[i].x;
			hitOverlay[1].y = pointsArr[i].y;
		}
		else if (i == 3)
		{
			pointsArr[i].x = X;
			Y + Height == 1080 ? pointsArr[i].y = Y + Height - 1 : pointsArr[i].y = Y + Height;
			hitOverlay[3].x = pointsArr[i].x;
			hitOverlay[3].y = pointsArr[i].y;
		}
		else if (i == 4)
		{
			pointsArr[i].x = X;
			pointsArr[i].y = Y;
		}
		else
		{
			hitOverlay[0].x = pointsArr[i].x = X;
			hitOverlay[0].y = pointsArr[i].y = Y;
		}
	}
}

bool Cell::MouseEnter(int x, int y, bool selecting)
{
	if (x >= cellBody.x && x <= cellBody.x + cellBody.w && y >= cellBody.y && y <= cellBody.y + cellBody.h)
	{
		if (selecting)
		{
			target == false ? target = true : target = false;
			CallHit();
		}

		if (active == true) { return true; }
		
		active = true;
		//if (occupied) { std::cout << occupant << std::endl; }
		return true;
	}
	return false;
}

void Cell::MouseLeave()
{
	//std::cout << "\n\nLeft Cell " << ID << "\n\n";
	active = false;
}

void Cell::Listen(int mouseX, int mouseY, bool selecting)
{
	if (!MouseEnter(mouseX, mouseY, selecting) && active == true)
	{
		MouseLeave();
	}
}

void Cell::SetRenderColor()
{
	if (occupied && target)
	{
		color->cellR = 50;
		color->cellG = 0;
		color->cellB = 0;
	}
	else if (target)
	{
		color->cellR = 50;
		color->cellG = 0;
		color->cellB = 0;
	}
	else if (active && !target)
	{
		color->cellR = 0;
		color->cellG = 0;
		color->cellB = 50;
	}
	else
	{
		color->cellR = 0;
		color->cellG = 0;
		color->cellB = 20;
	}

	if (false)
	{
		if (occupant == "Carrier")
		{
			color->cellR = 50;
			color->cellG = 50;
			color->cellB = 50;
		}
		else if (occupant == "Battleship")
		{
			color->cellR = 50;
			color->cellG = 50;
			color->cellB = 0;
		}
		else if (occupant == "Cruiser")
		{
			color->cellR = 0;
			color->cellG = 50;
			color->cellB = 0;
		}
		else if (occupant == "Submarine")
		{
			color->cellR = 50;
			color->cellG = 0;
			color->cellB = 50;
		}
		else if (occupant == "Destroyer")
		{
			color->cellR = 0;
			color->cellG = 50;
			color->cellB = 50;
		}
	}
}

void Cell::ResetCell()
{
	occupied = false;
	occupant = "";
	struck = false;
	target = false;
}

void Cell::CallHit()
{
	if (occupant != "")
	{
		std::cout << "\n!!! Hit !!!\n";
	}
	else
	{
		std::cout << "\nMiss\n";
	}
}

void Cell::Render(SDL_Renderer* renderer)
{
	SetRenderColor();
	SDL_SetRenderDrawColor(renderer, color->cellR, color->cellG, color->cellB, color->Trans);
	SDL_RenderFillRect(renderer, &cellBody);

	SDL_SetRenderDrawColor(renderer, color->borderR, color->borderG, color->borderB, color->Trans);
	SDL_RenderDrawLines(renderer, pointsArr, 5);

	if (target && occupied)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLines(renderer, hitOverlay, 4);
	}
}