#pragma once
#ifndef _CARRIER_
#define _CARRIER_
#include "ship.h"

class Carrier : public Ship
{
public:
	Carrier() { Initialize(5, "Battlship"); };
};

#endif // !_CARRIER_