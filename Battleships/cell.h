#pragma once
#ifndef _CELL_
#define _CELL_
#include <SDL.h>
#include <vector>

struct Color
{
	int cellR, cellG, cellB, borderR, borderG, borderB, Trans;

	Color() : cellR(255), cellG(255), cellB(255), borderR(255), borderG(255), borderB(255), Trans(255) {};
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



	void Initialize(int id, int xpos, int ypos, int width, int height);
	bool MouseEnter(int x, int y, bool selecting); //Returns true if the mouse intersects the cell, false otherwise
	void MouseLeave(); //Sets active member variable to false
	void SetRenderColor();
	void ResetCell();
	void CallHit();

	void Listen(int mouseX, int mouseY, bool selecting);
	void Update();
	void Render(SDL_Renderer* renderer);

	/*DEGUG*/
private:
	std::unique_ptr<Color> color;
	SDL_Rect cellBody; //Center rectangle of a cell
	SDL_Point pointsArr[5]; //Points used to render lines


	/*The mere presence of this array is crippling performance, memory usage, and code reliability.
	When assigned to by iterative value (i) it causes the color object to delete itself and leak memory?
	The overlay its data is used to generate is a gaint memory hog and barely works.
	Cool ide but I may need to trash it.*/
	SDL_Point hitOverlay[4]; //Points used for the X overlay
};

#endif // !_CELL_