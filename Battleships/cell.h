#pragma once
#ifndef _CELL_
#define _CELL_
#include <SDL.h>
#include <vector>
//Board Numbering
enum
{
	A = 11,
	B = 12,
	C = 13,
	D = 14,
	E = 15,
	F = 16,
	G = 17,
	H = 18,
	I = 19,
	J = 20
};

struct Properties
{
public:
	Properties(float Xpos, float Ypos, int width, int height)
	{
		X = Xpos;
		Y = Ypos;
		Width = width;
		Height = height;
	}

	float X, Y; //Position of the SDL_Rect, Doubles as starting points for SDL_RenderDrawLines()
	int Width, Height; //Size of the SDL_Rect, Doubles as line spacing for SDL_RenderDrawLines()
};

class Cell
{
public:
	int ID; //Handle for the cell.
	bool occupied; //True if there is an occupant object in the selected cell.
	bool struck; // True if the selected cell has been struck once.
	bool active;
	int X, Y; //Position of the SDL_Rect, Doubles as starting points for SDL_RenderDrawLines()
	float Width, Height; //Size of the SDL_Rect, Doubles as line spacing for SDL_RenderDrawLines()

	SDL_Rect cellBody; //Center rectangle of a cell
	SDL_Point pointsArr[5]; //Points used to render lines


	void Initialize(int id, float xpos, float ypos, float width, float height);
	void MouseEnter();
	void MouseLeave();

	void Listen(int mouseX, int mouseY);
	void Update();
	void Render(SDL_Renderer* renderer);

};

#endif // !_CELL_