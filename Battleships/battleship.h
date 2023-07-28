#pragma once
#ifndef _BATTLESHIP_
#define _BATTLESHIP_
#include "ship.h"

class Battleship : public Ship
{
public:
	Battleship() { Initialize(4); };
};

#endif // !_BATTLESHIP_