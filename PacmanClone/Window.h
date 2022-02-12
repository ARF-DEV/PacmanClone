#pragma once
#include<SDL.h>
#include<string>
#include<iostream>
class Window {
public:
	Window(std::string title = "", int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, int w = 1024, int h = 658, Uint32 flags = 0) {

		pWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
		
		//Add Exception Later
		if (pWindow == nullptr) {
			std::cout << "Failed to create window : " << SDL_GetError() << '\n';
		}
		
	}
	~Window() {
		SDL_DestroyWindow(pWindow);
		pWindow = nullptr;
	}

	SDL_Window* getWindow() {
		return pWindow;
	}
private:
	SDL_Window* pWindow = nullptr;
};