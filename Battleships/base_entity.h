#pragma once
#ifndef _BASE_ENTITY_
#define _BASE_ENDTITY_
#include <SDL.h>

//Master class
class BaseEntity
{
public:
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void Clean() = 0;
};

#endif // !_BASE_ENTITY_