#pragma once
#ifndef _SHIP_
#define _SHIP_
#include <SDL.h>
#include <vector>
#include <random>

enum {
	Vertical = 10,
	Horizontal = 1
};

class Ship
{
public:
	void Initialize(int s)
	{
		size = s;
		destroyed = false;
	}

	//Randomly create a location for the ship
	void GenerateLocation(int range)
	{
		location.clear();

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, range - 1);
		location.push_back(dis(gen));

		std::uniform_int_distribution<> dist(1, 2);
		dist(gen) == 1 ? orientation = Horizontal : orientation = Vertical;

		if (size < 2) { return; };

		std::cout << "Starting: " << location[0] << std::endl;
		for (int i = 0; i < size - 1; i++)
		{
			//Prevent Out of Scope exceptions and row hopping
			//If start location is Out of Scope --or-- next location is near the end of the row 
			if (location[0] >= range - size || location[0] % 10 >= 7)
			{
				if (location[i] - orientation < 0)
				{
					MoveForward();
					location.push_back(location[i] - orientation);
				}
				else
				{
					location.push_back(location[i] - orientation);
				}
				continue;
			}
			else if (location[i] + orientation >= range)
			{
				MoveBackward();
				std::cout << "Restricting to: " << location[i] + orientation << std::endl;
				location.push_back(location[i] + orientation);
			}

			std::cout << "Default pushing to: " << location[i] + orientation << std::endl;
			location.push_back(location[i] + orientation);
		}
	}

	void MoveForward()
	{
		//Shift the positions in locations vec forward. Relative to ships orientation
		for (int r = 0; r < location.size(); r++)
		{
			std::cout << "\n\nRewriting: " << location[r] << " to ";
			location[r] += orientation;
			std::cout << location[r] << "\n\n";
		}
	}

	void MoveBackward()
	{
		//Shift the positions in locations vec backwards. Relative to ships orientation
		for (int r = 0; r < location.size(); r++)
		{
			std::cout << "\n\nRewriting: " << location[r] << " to ";
			location[r] -= orientation;
			std::cout << location[r] << "\n\n";
		}
	}

	std::vector<int> GetLocation() { return location; }

private:
	int size;
	bool destroyed;
	int orientation;
	std::vector<int> location;
};
#endif // !_SHIP_