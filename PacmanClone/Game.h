#pragma once
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>

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
	bool init();
	void update();
	void draw();
	bool initWindow(std::string title = "SDL_WINDOW", int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, int w = 960, int h = 540, Uint8 flags = 0);
	bool initRenderer();
private:
	SDL_Texture* pTexture;

	SDL_Renderer* pRenderer;
	SDL_Window* pWindow;
	GameState state;
	SDL_Event e;
};

