#include <SDL.h>
#include "unity_build.h"

Game::Game() {}
Game::~Game() {}

bool checkSpawn = false;

std::unique_ptr<Game> Game::gameInstance = nullptr;
std::unique_ptr<Grid> gridInstance = nullptr;
std::unique_ptr<Fleet> fleetInstance = nullptr;

void Game::Initialize(const char* title, int width, int height, bool fullscreen) 
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "!!! SDL_Init() has failed !!!" << std::endl; running = false;
	}
	else {
		std::cout << "### SDL Initialized ###" << std::endl;
	}

	//Create window and renderer
	if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) {
		std::cout << "!!! SDL_Create() has failed !!!" << std::endl;
	}
	else {
		std::cout << "### Window and renderer created ###" << std::endl;
		SDL_SetWindowResizable(window, SDL_TRUE);
	}
	
	gridInstance = std::make_unique<Grid>();
	gridInstance->Initialize(10, 10, width, height);
	gridInstance->CreateGrid();

	fleetInstance = std::make_unique<Fleet>();
	fleetInstance->FleetScatter(gridInstance->cellCount);

	gridInstance->CheckGrid(fleetInstance); 

	running = true;
}

void Game::Update() 
{
	gridInstance->CheckGrid(fleetInstance);
}

void Game::Handle()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	SDL_Scancode key;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:	Game::GetInstance()->Quit(); break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				std::cout << "\n\n### --- RESETTING --- ###\n\n";
				fleetInstance->FleetScatter(gridInstance->cellCount);
				break;
			default:
				break;
			}
		case SDL_MOUSEMOTION:
			gridInstance->Listen(e.motion.x, e.motion.y);
			break;
		default:
			break;
		}

		if (keyStates[SDL_SCANCODE_ESCAPE])
		{
			Game::GetInstance()->Quit();
		}
	}
}

void Game::Render() 
{
	//SetRenderer (Background)

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Colorize Viewport (Queue Rendering)
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	gridInstance->Draw(renderer, 0, 0, 1920, 0);

	//Present Renering (Draw)
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	std::cout << "### Scrubbing Game ###" << std::endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "### SDL Renderer, Window, and Game class were cleaned ###" << std::endl;
}

bool Game::Running()
{
	return running;
}

void Game::Quit() 
{
	running = false;
}