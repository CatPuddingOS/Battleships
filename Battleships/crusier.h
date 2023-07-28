#pragma once
#ifndef _CRUSIER_
#define _CRUSIER_
#include "ship.h"

class Crusier : public Ship
{
public:
	Crusier() { Initialize(3); };
};

#endif // !_CRUSIER_