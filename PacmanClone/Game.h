#pragma once
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>

#include"Texture.h"
#include"Animation.h"
#include"Renderer.h"
#include"Window.h"
#include"Vec2.h"
#include"Pacman.h"
#include"Map.h"

class Game {
private:
	enum class GameState
	{
		menu,
		gameplay,
		gameover,
		quit
	};
public:
	void run();
	Game();
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	~Game();
	
private:
	void start() {
		map.loadMapFromVector(
			{
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1
			}, 10, 10);
	}
	void update();
	void draw();
	bool init();
private:

	GameState state;
	SDL_Event e;
	Window window{"Testing"};
	Renderer renderer{window.getWindow(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC };
	Texture texture{"assets/blueGhost.png", renderer.getRenderer() };
	Animation anim{texture, 0, 0, 16, 16, 8};
	Pacman pacman{ {0, 0}, anim };
	Map map;

};

