#include <SDL.h>
#include "fleet.h"

void Fleet::FleetScatter(int range)
{
	destroyerInstance->GenerateLocation(range);
}