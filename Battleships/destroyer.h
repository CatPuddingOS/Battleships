#pragma once
#ifndef _DESTROYER_
#define _DESTROYER_
#include "ship.h"

class Destroyer : public Ship
{
public:
	Destroyer() { Initialize(2, "Destroyer"); };
};

#endif // !_DESTROYER_