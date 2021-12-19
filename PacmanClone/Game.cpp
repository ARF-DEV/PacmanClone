#include "Game.h"
bool Game::init()
{
	// NEED TO ADD AUDIO ETC
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to init window : " << SDL_GetError() << '\n';
		return false;
	}

	if (!initWindow())
		return false;

	if (!initRenderer())
		return false;

	int imgflags = IMG_INIT_PNG;
	if (!(IMG_Init(imgflags) & imgflags)) {
		std::cout << "Failed to init SDL2_image : " << SDL_GetError() << '\n';
		return false;
	}

	return true;
}

void Game::update()
{
	//Events & game Logic
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			state = GameState::quit;
		}
	}
}

void Game::draw()
{
	// Draw Logic

	// Clear Rnederer
	SDL_SetRenderDrawColor(pRenderer, 0x0, 0x0, 0x0, 0x0);
	SDL_RenderClear(pRenderer);

	// Stuff


	// Update Renderer
	SDL_RenderPresent(pRenderer);

}

void Game::run() {
	if (!init())
		return;
	while (state != GameState::quit) {
		update();
		draw();
	}
}

Game::Game()
	:
	state(GameState::gameplay)
{
}

Game::~Game()
{
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);

	IMG_Quit();
	SDL_Quit();
}

bool Game::initWindow(std::string title, int x, int y, int w, int h, Uint8 flags)
{
	pWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);

	if (pWindow == nullptr) {
		std::cout << "Failed to create window : " << SDL_GetError() << '\n';
		return false;
	}
	return true;
}

bool Game::initRenderer()
{
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	
	if (pRenderer == nullptr) {
		std::cout << "Failed to create renderer : " << SDL_GetError() << '\n';
		return false;
	}
	return true;
}
