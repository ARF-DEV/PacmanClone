#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
class Texture {
private:
	void free();
public:
	Texture();
	Texture(std::string path, SDL_Renderer* pRenderer);
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	~Texture();

	bool loadTextureNonChroma(std::string path, SDL_Renderer* renderer);
	bool loadTexture(std::string path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void renderTexture(int x, int y, SDL_Renderer* renderer, SDL_Rect* srcRect = NULL);
	void renderTexture(int x, int y, int width, int height, SDL_Renderer* renderer, SDL_Rect* srcRect = NULL);
	int getWidth();
	int getHeight();
private:
	int vWidth;
	int vHeight;

	SDL_Texture* pTexture;
};