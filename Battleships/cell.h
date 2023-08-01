#pragma once
#ifndef _CELL_
#define _CELL_
#include <SDL.h>
#include <vector>

struct Color
{
	int R, G, B, Trans;

	Color() : R(255), G(255), B(255), Trans(255) {};
};

class Cell
{
public:
	int ID; //Handle for the cell.
	bool struck; // True if the selected cell has been struck once.
	bool active;
	bool target;
	bool occupied; //True if there is an occupant object in the selected cell.
	std::string occupant;
	float Width, Height;
	int X, Y;

	SDL_Rect cellBody; //Center rectangle of a cell
	SDL_Point pointsArr[5]; //Points used to render lines


	void Initialize(int id, float xpos, float ypos, float width, float height);
	bool MouseEnter(int x, int y, bool selecting); //Returns true if the mouse intersects the cell, false otherwise
	void MouseLeave(); //Sets active member variable to false
	void SetRenderColor();
	void ResetCell();

	void Listen(int mouseX, int mouseY, bool selecting);
	void Update();
	void Render(SDL_Renderer* renderer);

	/*DEGUG*/
private:
	std::unique_ptr<Color> color;
};

#endif // !_CELL_