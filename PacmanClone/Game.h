#pragma once
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include"Texture.h"
#include"Animation.h"

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
	void draw();
	bool init();
	bool initWindow(std::string title = "SDL_WINDOW", int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, int w = 960, int h = 540, Uint8 flags = 0);
	bool initRenderer();
private:


	SDL_Renderer* pRenderer = nullptr;
	SDL_Window* pWindow = nullptr;
	GameState state;
	SDL_Event e;

	Texture* texture;
	Animation* anim;
};

