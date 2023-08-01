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

	color = std::make_unique<Color>();

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

bool Cell::MouseEnter(int x, int y, bool selecting)
{
	if (x >= cellBody.x && x <= cellBody.x + cellBody.w && y >= cellBody.y && y <= cellBody.y + cellBody.h)
	{
		if (selecting)
		{
			target == false ? target = true : target = false;
		}

		if (active == true) { return true; }
		
		active = true;
		if (occupied) { std::cout << occupant << std::endl; }
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
	if (target)
	{
		color->R = 0;
		color->G = 0;
		color->B = 0;
	}
	else if (active && !target)
	{
		color->R = 0;
		color->G = 0;
		color->B = 50;
	}
	else
	{
		color->R = 50;
		color->G = 0;
		color->B = 0;
	}

	if (occupied == true)
	{
		if (occupant == "Carrier")
		{
			color->R = 50;
			color->G = 50;
			color->B = 50;
		}
		else if (occupant == "Battleship")
		{
			color->R = 50;
			color->G = 50;
			color->B = 0;
		}
		else if (occupant == "Cruiser")
		{
			color->R = 0;
			color->G = 50;
			color->B = 0;
		}
		else if (occupant == "Submarine")
		{
			color->R = 50;
			color->G = 0;
			color->B = 50;
		}
		else if (occupant == "Destroyer")
		{
			color->R = 0;
			color->G = 50;
			color->B = 50;
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

void Cell::Render(SDL_Renderer* renderer)
{
	SetRenderColor();
	SDL_SetRenderDrawColor(renderer, color->R, color->G, color->B, color->Trans);
	SDL_RenderFillRect(renderer, &cellBody);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, pointsArr, 5);
}