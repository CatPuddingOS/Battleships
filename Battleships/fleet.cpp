#include <SDL.h>
#include "fleet.h"

void Fleet::FleetScatter()
{
	shouldScatter == true ? shouldScatter = false : shouldScatter = true;
}

bool Fleet::GetScatterStatus()
{
	return shouldScatter;
}

int Fleet::GetSize()
{
	return fleetSize;
}