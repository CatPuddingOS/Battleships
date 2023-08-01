#pragma once
#ifndef _FLEET_
#define _FLEET_

#include <iostream>
#include "ships.h"

class Fleet
{
public:
	std::vector<std::unique_ptr<Ship>> fleetArr;

	Fleet() : shouldScatter(false), fleetDestroyed(0), fleetSize(5)
	{  
		carrierInstance = std::make_unique<Carrier>();
		battleshipInstance = std::make_unique<Battleship>();
		cruiserInstance = std::make_unique<Cruiser>();
		submarineInstance = std::make_unique<Submarine>();
		destroyerInstance = std::make_unique<Destroyer>();

		fleetArr.reserve(fleetSize);
		fleetArr.push_back(std::move(carrierInstance));
		fleetArr.push_back(std::move(battleshipInstance));
		fleetArr.push_back(std::move(cruiserInstance));
		fleetArr.push_back(std::move(submarineInstance));
		fleetArr.push_back(std::move(destroyerInstance));
	}

	void FleetScatter() { shouldScatter == true ? shouldScatter = false : shouldScatter = true; }; //Toggles the shouldScatter member.
	bool GetScatterStatus() { return shouldScatter; };
	int GetSize() { return fleetSize; };

private:
	std::unique_ptr<Ship> carrierInstance;
	std::unique_ptr<Ship> battleshipInstance;
	std::unique_ptr<Ship> cruiserInstance;
	std::unique_ptr<Ship> submarineInstance;
	std::unique_ptr<Ship> destroyerInstance;
	bool shouldScatter;
	bool fleetDestroyed;
	int fleetSize;
};
#endif // !_FLEET_