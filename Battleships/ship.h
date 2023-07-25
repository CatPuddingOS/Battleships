#pragma once
#ifndef _SHIP_
#define _SHIP_
#include <SDL.h>
#include <vector>

class Ship
{
public:
	void Initialize(int s, int pos[])
	{
		size = s;
		destroyed = false;

		for (int i = 0; i < size; i++)
		{
			location.push_back(pos[i]);
		}
	}

	std::vector<int> GetLocation() { return location; }

private:
	int size;
	bool destroyed;
	std::vector<int> location;
};


#endif // !_SHIP_
