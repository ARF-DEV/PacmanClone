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

bool Game::isColliding(SDL_Rect rectA, SDL_Rect rectB)
{
	Vec2<int> topLeftA = { rectA.x, rectA.y }, bottomRightA = { rectA.x + rectA.w, rectA.y + rectA.h };
	Vec2<int> topLeftB = { rectB.x, rectB.y }, bottomRightB = { rectB.x + rectB.w, rectB.y + rectB.h };

	if (bottomRightA.x <= topLeftB.x ||
		topLeftA.x >= bottomRightB.x ||
		bottomRightA.y <= topLeftB.y ||
		topLeftA.y >= bottomRightB.y) {
		return false;
	}
	return true;
}


void Game::start()
{
	map.loadMapFromVector(
		{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 0, 2, 2, 2, 0, 0, 0, 0, 1,
			1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 2, 1,
			1, 0, 1, 1, 0, 1, 1, 1, 2, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 2, 1,
			1, 0, 1, 1, 0, 1, 2, 1, 2, 1,
			1, 0, 1, 1, 0, 1, 1, 1, 2, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 2, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		}, coinAnim, 10, 10);

	//pacman.setCenterPos({ 0, 0 });
}

void Game::update()
{
	//Events & game Logic
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			state = GameState::quit;
		}
		
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_q) {
				gh1.setState(Ghost::GhostState::Chase);
			}
			if (e.key.keysym.sym == SDLK_e) {
				gh1.setState(Ghost::GhostState::Scatter);
			}
		}
	}
	pacman.update();
	gh1.update();
}

void Game::lateUpdate()
{
	pacman.lateUpdate();

	auto& listOfCoin = map.getListOfVector();
	for (Coin& coin : listOfCoin) {
		if (!coin.isEaten() && isColliding(pacman.getCollisionRect(), coin.getCollisionRect())) {
			coin.setEaten(true);
			++coinAmount;
			std::cout << coinAmount << '\n';
		}
	}
}

void Game::draw()
{
	// Draw Logic

	// Clear Rnederer
	SDL_SetRenderDrawColor(renderer.getRenderer(), 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(renderer.getRenderer());

	//REAL DRAWING SHIT HAPPENS HERE
	map.draw(renderer);
	pacman.draw(renderer);
	gh1.draw(renderer);
	// Update Renderer
	SDL_RenderPresent(renderer.getRenderer());

}

void Game::run() {
	start();

	while (state != GameState::quit) {
		update();
		lateUpdate();
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
