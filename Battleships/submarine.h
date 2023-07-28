#pragma once
#ifndef _SUB_
#define _SUB_
#include "ship.h"

class Submarine : public Ship
{
public:
	Submarine() { Initialize(3); };
};

#endif // !_SUB_