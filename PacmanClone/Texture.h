#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
class Texture {
private:
	void free();
public:
	Texture();
	Texture(std::string path, SDL_Renderer* pRenderer);
	Texture(const Texture& other) = delete;
	Texture(Texture&& other) noexcept {
		vWidth = other.vWidth;
		vHeight = other.vHeight;
		pTexture = other.pTexture;
		other.pTexture = nullptr;
	};
	Texture(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color textColor);
	Texture& operator=(const Texture& other) = delete;
	~Texture();

	bool loadTextureNonChroma(std::string path, SDL_Renderer* renderer);
	bool loadTexture(std::string path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	bool createTextureFromText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color textColor);
	void renderTexture(int x, int y, SDL_Renderer* renderer, SDL_Rect* srcRect = NULL);
	void renderTexture(int x, int y, int width, int height, SDL_Renderer* renderer, SDL_Rect* srcRect = NULL);
	int getWidth();
	int getHeight();
private:
	int vWidth;
	int vHeight;

	SDL_Texture* pTexture;
};