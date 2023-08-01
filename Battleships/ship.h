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
		shipHp = s;
		shipSize = s;
		shipClass = name;
		shipDestroyed = false;
	}

	void SetLocation(std::vector<int> vec) { shipLocation = vec; };
	void ShipDestroyed() { shipDestroyed = true; };

	std::vector<int> GetLocation() { return shipLocation; }
	std::string GetName() { return shipClass; };
	int GetSize() { return shipSize; };

private:
	bool shipDestroyed;
	int shipHp, shipSize, orientation;
	std::string shipClass;
	std::vector<int> shipLocation;
};
#endif // !_SHIP_