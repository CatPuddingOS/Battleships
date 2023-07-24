#pragma once
#ifndef _GAME_OBJ_
#define _GAME_OBJ_

#include <SDL.h>
#include <iostream>

/// <summary>
/// Game class - Handles main loop
/// </summary>
class Game
{
public:
	Game();
	~Game();

	static std::unique_ptr<Game>& GetInstance()
	{
		if (gameInstance != nullptr) { return gameInstance; }
		else { return gameInstance = std::make_unique<Game>(); }
	}

	void Initialize(const char* title, int width, int height, bool fullscreen);

	void Update();
	void Handle();
	void Render();
	void Clean();

	bool Running();
	void Quit();

private:
	bool running;
	SDL_Window* window;
	SDL_Renderer* renderer;
	static std::unique_ptr<Game> gameInstance;
};
#endif // !_GAME_OBJ_