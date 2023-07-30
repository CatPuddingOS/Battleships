#pragma once
#ifndef _FLEET_
#define _FLEET_

#include <iostream>
#include "ships.h"

class Fleet
{
public:
	std::vector<Ship> fleetArr;

	Fleet() : fleetDestroyed(0), fleetSize(5) 
	{  
		carrierInstance = std::make_unique<Carrier>();
		battleshipInstance = std::make_unique<Battleship>();
		cruiserInstance = std::make_unique<Cruiser>();
		submarineInstance = std::make_unique<Submarine>();
		destroyerInstance = std::make_unique<Destroyer>();

		fleetArr.reserve(fleetSize);
		fleetArr.push_back(*carrierInstance);
		fleetArr.push_back(*battleshipInstance);
		fleetArr.push_back(*cruiserInstance);
		fleetArr.push_back(*submarineInstance);
		fleetArr.push_back(*destroyerInstance);
	}

	void FleetScatter(int range); //randomly place the fleet of ships on a grid. Ships are placed vertically and horizontally.
	int GetSize();

private:
	std::unique_ptr<Ship> carrierInstance;
	std::unique_ptr<Ship> battleshipInstance;
	std::unique_ptr<Ship> cruiserInstance;
	std::unique_ptr<Ship> submarineInstance;
	std::unique_ptr<Ship> destroyerInstance;
	bool fleetDestroyed;
	int fleetSize;
};
#endif // !_FLEET_