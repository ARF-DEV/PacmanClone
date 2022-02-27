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

	if (TTF_Init() == -1) {
		std::cout << "Failed to init SDL2_ttf : " << SDL_GetError() << '\n';
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

void Game::resetGame()
{
	gh1.reset();
	gh1.setCenterPos(map.getGhostSpawns()[0]);
	gh1.setHomePos(map.getGhostSpawns()[0]);
	pacman.reset();
	pacman.setCenterPos(map.getPlayerSpawn());
}


void Game::start()
{
	map.loadMapFromVector(
		{
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
			1,2,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,
			1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,10,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,
			1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,10,0,0,1,
			1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,
			1,0,0,1,0,1,0,5,0,0,0,0,0,1,0,1,10,0,1,
			1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,
			1,0,0,0,0,0,0,1,6,7,8,1,0,0,0,0,0,0,1,
			1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,
			1,0,0,1,0,1,0,0,0,9,0,0,0,1,0,1,0,0,1,
			1,1,1,1,0,1,1,1,0,1,10,1,1,1,0,1,1,1,1,
			1,0,0,0,0,1,0,0,0,1,0,0,0,1,10,0,0,0,1,
			1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,
			1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		}, Animation(coinSpriteSheet, 0, 0, 16, 16, 24, 24, 8), Animation(bigCoinSpriteSheet, 0, 0, 16, 16, 24, 24, 8), 19, 19);
	gFont = TTF_OpenFont("assets/pacmanFont.TTF", 50);
	minecraftFont = TTF_OpenFont("assets/Minecraft.ttf", 24);
	startTextTexture.createTextureFromText(renderer.getRenderer(), gFont, "PACMAN", { 255, 255, 255 });
	gameOverTextTexture.createTextureFromText(renderer.getRenderer(), gFont, "GameOver", { 255, 255, 255 });
	pressEnterToRestartTexture.createTextureFromText(renderer.getRenderer(), minecraftFont, "Press Enter To Restart", { 255, 255, 255 });
	pressEnterToStartTexture.createTextureFromText(renderer.getRenderer(), minecraftFont, "Press Enter to Start", { 255, 255, 255 });
	//pacman.setCenterPos({ 0, 0 });
	resetGame();
	//textTexture.createTextureFromText(renderer.getRenderer(), gFont, "HELLOOO", { 255,0, 0 });
}

void Game::update()
{
	//Events & game Logic
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			state = GameState::quit;
		}
		
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_RETURN) {
				switch (state)
				{
				case Game::GameState::menu:
					state = Game::GameState::gameplay;
					break;
				case Game::GameState::gameover:
					resetGame();
					state = Game::GameState::gameplay;
					break;
				case Game::GameState::quit:
					break;
				default:
					break;
				}
			}
		}
	}

	switch (state)
	{
	case Game::GameState::menu:
		break;
	case Game::GameState::gameplay:
		pacman.update();
		gh1.update();

		// IMPLEMENT TIMER FOR FRIGHTENED IN GHOST

		break;
	case Game::GameState::gameover:
		break;
	case Game::GameState::quit:
		break;
	default:
		break;
	}
	
}

void Game::lateUpdate()
{
	switch (state)
	{
	case Game::GameState::menu:
		break;
	case Game::GameState::gameplay: {
		pacman.lateUpdate();

		auto& listOfCoin = map.getListOfVector();
		for (Coin& coin : listOfCoin) {
			if (!coin.isEaten() && isColliding(pacman.getCollisionRect(), coin.getCollisionRect())) {
				if (coin.isBigCoin()) {
					gh1.flip();
					gh1.setState(Ghost::GhostState::Frightened);
				}
				coin.setEaten(true);
				++coinAmount;
				std::cout << coinAmount << '\n';
			}
		}
		if (isColliding(gh1.getCollisionRect(), pacman.getCollisionRect())) {
			if (gh1.isFrightened())
			{
				gh1.setState(Ghost::GhostState::Eaten);
				gh1.flip();
			}
			else if (!gh1.isEaten()) {
				pacman.deadIsTrue();
				state = GameState::gameover;
				
			}
			
		}
		break;

	}
	case Game::GameState::gameover:
		break;
	case Game::GameState::quit:
		break;
	default:
		break;
	}
}

void Game::draw()
{
	// Draw Logic

	// Clear Rnederer
	SDL_SetRenderDrawColor(renderer.getRenderer(), 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(renderer.getRenderer());

	//REAL DRAWING SHIT HAPPENS HERE

	switch (state)
	{
	case Game::GameState::menu:
		startTextTexture.renderTexture(512- startTextTexture.getWidth() / 2, 100, renderer.getRenderer());
		pressEnterToStartTexture.renderTexture(512 - pressEnterToStartTexture.getWidth() / 2, 300, renderer.getRenderer());
		break;
	case Game::GameState::gameplay:
		map.draw(renderer);
		pacman.draw(renderer);
		gh1.draw(renderer);
		break;
	case Game::GameState::gameover:
		gameOverTextTexture.renderTexture(512 - gameOverTextTexture.getWidth() / 2, 100, renderer.getRenderer());
		pressEnterToRestartTexture.renderTexture(512 - pressEnterToRestartTexture.getWidth() / 2, 300, renderer.getRenderer());
		break;
	case Game::GameState::quit:
		break;
	default:
		break;
	}

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



Game::~Game()
{
	IMG_Quit();
	SDL_Quit();
}
