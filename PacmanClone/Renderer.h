#pragma once
#include<SDL.h>
#include<iostream>
class Renderer {
public:
	Renderer(SDL_Window* pWindow, Uint32 flags) {
		pRenderer = SDL_CreateRenderer(pWindow, -1, flags);

		//Add Exception Later
		if (pRenderer == nullptr) {
			std::cout << "Failed to create renderer : " << SDL_GetError() << '\n';
		}
	}
	~Renderer() {
		SDL_DestroyRenderer(pRenderer);
		pRenderer = nullptr;
	}
	
	SDL_Renderer* getRenderer() {
		return pRenderer;
	}
private:
	SDL_Renderer* pRenderer;
};