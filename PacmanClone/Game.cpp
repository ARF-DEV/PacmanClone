#include "Game.h"
bool Game::init()
{
	// NEED TO ADD AUDIO ETC
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to init window : " << SDL_GetError() << '\n';
		return false;
	}

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
	SDL_SetRenderDrawColor(renderer.getRenderer(), 0x0, 0x0, 0x0, 0x0);
	SDL_RenderClear(renderer.getRenderer());

	//REAL DRAWING SHIT HAPPENS HERE
	anim.draw(0, 0, renderer.getRenderer());

	// Update Renderer
	SDL_RenderPresent(renderer.getRenderer());

}

void Game::run() {
	
	while (state != GameState::quit) {
		update();
		draw();
	}
}

Game::Game()
	:
	state(GameState::gameplay)
{
	std::cout << "game" << std::endl;
	init();
}

Game::~Game()
{
	IMG_Quit();
	SDL_Quit();
}
