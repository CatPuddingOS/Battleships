#include <SDL.h>
#include "fleet.h"

void Fleet::FleetScatter(int range)
{
	for (int i = 0; i < fleetSize; i++)
	{
		fleetArr[i].GenerateLocation(range);
	}
}

int Fleet::GetSize()
{
	return fleetSize;
}