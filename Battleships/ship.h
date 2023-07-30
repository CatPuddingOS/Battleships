#pragma once
#ifndef _SHIP_
#define _SHIP_
#include <SDL.h>
#include <vector>
#include <random>

class Ship
{
public:
	void Initialize(int s, std::string name)
	{
		size = s;
		shipClass = name;
		destroyed = false;
	}

	void SetLocation(std::vector<int> vec) { location = vec; };

	std::vector<int> GetLocation() { return location; }
	std::string GetName() { return shipClass; };
	int GetSize() { return size; };

private:
	std::string shipClass;
	int size;
	bool destroyed;
	int orientation;
	std::vector<int> location;
};
#endif // !_SHIP_