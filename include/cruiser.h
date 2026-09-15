#pragma once
#ifndef _CRUSIER_
#define _CRUSIER_
#include "ship.h"

class Cruiser : public Ship
{
public:
	Cruiser() { Initialize(3, "Cruiser"); };
};

#endif // !_CRUSIER_