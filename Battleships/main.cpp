#include <SDL.h>
#include "unity_build.h"

#define WIDTH 1920
#define HEIGHT 1080

int main(int argc, char* args[]) {
	Game::GetInstance()->Initialize("Battleships", WIDTH, HEIGHT, false);

	while (Game::GetInstance()->Running())
	{
		Game::GetInstance()->Handle();
		Game::GetInstance()->Update();
		Game::GetInstance()->Render();
	}

	Game::GetInstance()->Clean();

	return 0;
}