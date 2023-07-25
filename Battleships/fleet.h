#pragma once
#ifndef _FLEET_
#define _FLEET_

#include <iostream>
#include "destroyer.h"


class Fleet
{
public:
	std::unique_ptr<Destroyer> destroyerInstance;

	Fleet() : fleetDestroyed(0), fleetSize(1) { destroyerInstance = std::make_unique<Destroyer>(); }

	void FleetScatter(); //randomly place the fleet of ships on a grid. Ships are placed vertically and horizontally.

private:
	bool fleetDestroyed;
	int fleetSize;
};
#endif // !_FLEET_