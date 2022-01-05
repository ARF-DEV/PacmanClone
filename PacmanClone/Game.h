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
	void start();
	void update();
	void lateUpdate();
	void draw();
	bool init();
	bool isColliding(SDL_Rect& rect1, SDL_Rect& rect2);
private:

	GameState state;
	SDL_Event e;
	Window window{"Testing"};
	Renderer renderer{window.getWindow(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC };
	Texture texture{"assets/blueGhost.png", renderer.getRenderer() };
	Animation anim{texture, 0, 0, 16, 16, 32, 32, 8};
	Map map{ {32 , 32} };
	Pacman pacman{ {64, 64}, anim, map };

};

