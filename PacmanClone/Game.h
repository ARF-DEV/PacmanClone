#pragma once
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>


#include"Texture.h"
#include"Animation.h"
#include"Renderer.h"
#include"Window.h"
#include"Vec2.h"
#include"Pacman.h"
#include"Map.h"
#include"Coin.h"
#include"Ghost.h"

class Game {
private:
	enum class GameState
	{
		menu,
		gameplay,
		gameover,
		win,
		quit
	};
public:
	void run();
	Game()
		:
		window("Pacmon"),
		pacmanSprite("assets/pacmanSprite.png", renderer.getRenderer()),
		coinSpriteSheet("assets/coin.png", renderer.getRenderer()),
		bigCoinSpriteSheet("assets/bigCoin.png", renderer.getRenderer()),
		textColor(SDL_Color(255,255,255)),
		renderer(window.getWindow(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
		state(GameState::menu),
		map({32, 32}),
		pacman(Vec2<int>(64, 64), std::move(Animation(pacmanSprite, 0, 32, 16, 16, 32, 32, 3 )), SDL_Rect(8, 8, 16, 16), map),
		gh1({ 64, 256 }, std::move(Animation( pacmanSprite, 0, 80, 16, 16, 32, 32, 2 )), { 8, 8, 16, 16 }, map, pacman, { 0, 0 }, [this]() -> Vec2<int> {
			return this->pacman.getCenter() + (this->pacman.getDir() * 32 * 1);
		}),
		gh2({ 64, 256 }, std::move(Animation(pacmanSprite, 0, 96, 16, 16, 32, 32, 2)), { 8, 8, 16, 16 }, map, pacman, { 0, 0 }, [this]() -> Vec2<int> {
			return this->pacman.getCenter() + (this->pacman.getDir() * 32 * 4);
		}),
		gh3({ 64, 256 }, std::move(Animation(pacmanSprite, 0, 112, 16, 16, 32, 32, 2)), { 8, 8, 16, 16 }, map, pacman, { 0, 0 }, [this]() -> Vec2<int> {
			const auto target = (this->gh1.getCenter() - (this->pacman.getDir() * 32 * 1));
			return target;
		}),
		gh4({ 64, 256 }, std::move(Animation(pacmanSprite, 0, 128, 16, 16, 32, 32, 2)), { 8, 8, 16, 16 }, map, pacman, { 0, 0 }, [this]() -> Vec2<int> {
			constexpr int range = 120;
			const int distance = (this->gh4.getCenter() - this->pacman.getCenter()).getLength();
	
			if (distance <= range) {
				return this->gh4.getScatterTarget();
			}
			else {
				return this->pacman.getCenter();
			}

		})

	{
		pacman.addAnimation(Entity::AnimState::DOWN, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 48, 16, 16, 32, 32, 3))));
		pacman.addAnimation(Entity::AnimState::LEFT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 0, 16, 16, 32, 32, 3))));
		pacman.addAnimation(Entity::AnimState::RIGHT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 16, 16, 16, 32, 32, 3))));
		gh1.addAnimation(Entity::AnimState::DOWN, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 32, 80, 16, 16, 32, 32, 2))));
		gh1.addAnimation(Entity::AnimState::LEFT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 64, 80, 16, 16, 32, 32, 2))));
		gh1.addAnimation(Entity::AnimState::RIGHT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 96, 80, 16, 16, 32, 32, 2))));
		gh1.addAnimation(Entity::AnimState::FRIGHTENED, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 144, 16, 16, 32, 32, 2))));
		gh1.addAnimation(Entity::AnimState::G_EATEN_UP, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 160, 16, 16, 32, 32, 1))));
		gh1.addAnimation(Entity::AnimState::G_EATEN_DOWN, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 16, 160, 16, 16, 32, 32, 1))));
		gh1.addAnimation(Entity::AnimState::G_EATEN_LEFT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 32, 160, 16, 16, 32, 32, 1))));
		gh1.addAnimation(Entity::AnimState::G_EATEN_RIGHT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 48, 160, 16, 16, 32, 32, 1))));

		gh2.addAnimation(Entity::AnimState::DOWN, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 32, 96, 16, 16, 32, 32, 2))));
		gh2.addAnimation(Entity::AnimState::LEFT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 64, 96, 16, 16, 32, 32, 2))));
		gh2.addAnimation(Entity::AnimState::RIGHT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 96, 96, 16, 16, 32, 32, 2))));
		gh2.addAnimation(Entity::AnimState::FRIGHTENED, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 144, 16, 16, 32, 32, 2))));
		gh2.addAnimation(Entity::AnimState::G_EATEN_UP, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 160, 16, 16, 32, 32, 1))));
		gh2.addAnimation(Entity::AnimState::G_EATEN_DOWN, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 16, 160, 16, 16, 32, 32, 1))));
		gh2.addAnimation(Entity::AnimState::G_EATEN_LEFT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 32, 160, 16, 16, 32, 32, 1))));
		gh2.addAnimation(Entity::AnimState::G_EATEN_RIGHT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 48, 160, 16, 16, 32, 32, 1))));

		gh3.addAnimation(Entity::AnimState::DOWN, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 32, 112, 16, 16, 32, 32, 2))));
		gh3.addAnimation(Entity::AnimState::LEFT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 64, 112, 16, 16, 32, 32, 2))));
		gh3.addAnimation(Entity::AnimState::RIGHT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 96, 112, 16, 16, 32, 32, 2))));
		gh3.addAnimation(Entity::AnimState::FRIGHTENED, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 144, 16, 16, 32, 32, 2))));
		gh3.addAnimation(Entity::AnimState::G_EATEN_UP, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 160, 16, 16, 32, 32, 1))));
		gh3.addAnimation(Entity::AnimState::G_EATEN_DOWN, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 16, 160, 16, 16, 32, 32, 1))));
		gh3.addAnimation(Entity::AnimState::G_EATEN_LEFT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 32, 160, 16, 16, 32, 32, 1))));
		gh3.addAnimation(Entity::AnimState::G_EATEN_RIGHT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 48, 160, 16, 16, 32, 32, 1))));

		gh4.addAnimation(Entity::AnimState::DOWN, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 32, 128, 16, 16, 32, 32, 2))));
		gh4.addAnimation(Entity::AnimState::LEFT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 64, 128, 16, 16, 32, 32, 2))));
		gh4.addAnimation(Entity::AnimState::RIGHT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 96, 128, 16, 16, 32, 32, 2))));
		gh4.addAnimation(Entity::AnimState::FRIGHTENED, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 144, 16, 16, 32, 32, 2))));
		gh4.addAnimation(Entity::AnimState::G_EATEN_UP, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 0, 160, 16, 16, 32, 32, 1))));
		gh4.addAnimation(Entity::AnimState::G_EATEN_DOWN, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 16, 160, 16, 16, 32, 32, 1))));
		gh4.addAnimation(Entity::AnimState::G_EATEN_LEFT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 32, 160, 16, 16, 32, 32, 1))));
		gh4.addAnimation(Entity::AnimState::G_EATEN_RIGHT, std::make_unique<Animation>(std::move(Animation(pacmanSprite, 48, 160, 16, 16, 32, 32, 1))));
		init();
	}
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	~Game();
	
private:
	void start();
	void update();
	void lateUpdate();
	void draw();
	bool init();
	bool isColliding(SDL_Rect rect1, SDL_Rect rect2);
	void setStateToGameplay() {
		state = GameState::gameplay;
	}
	void resetGame();

private:
	int coinAmount = 0;

	GameState state;
	SDL_Event e;
	Window window;
	TTF_Font* gFont;
	TTF_Font* minecraftFont;
	Renderer renderer;
	Texture pacmanSprite;
	Texture coinSpriteSheet;
	Texture bigCoinSpriteSheet;
	Texture startTextTexture;
	Texture pressEnterToStartTexture;
	Texture pressEnterToRestartTexture;
	Texture gameOverTextTexture;
	Texture winGameTextTexture;
	SDL_Color textColor;
	Map map;
	Pacman pacman;
	Ghost gh1;
	Ghost gh2;
	Ghost gh3;
	Ghost gh4;
};

