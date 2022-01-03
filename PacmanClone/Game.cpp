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
	pacman.update();
	
}

void Game::draw()
{
	// Draw Logic

	// Clear Rnederer
	SDL_SetRenderDrawColor(renderer.getRenderer(), 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(renderer.getRenderer());

	//REAL DRAWING SHIT HAPPENS HERE
	//map.draw(renderer);
	//SDL_Rect rect = { 0,0, 32, 32 };
	//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );        
	//SDL_RenderFillRect( renderer.getRenderer(), &rect );
	map.draw(renderer);
	pacman.draw(renderer);

	// Update Renderer
	SDL_RenderPresent(renderer.getRenderer());

}

void Game::run() {
	start();

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
