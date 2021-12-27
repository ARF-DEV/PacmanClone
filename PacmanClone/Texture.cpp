#include "Texture.h"
void Texture::free()
{
	if (pTexture != nullptr) {
		SDL_DestroyTexture(pTexture);
		vWidth = 0;
		vHeight = 0;
	}
}
Texture::Texture()
	:
	pTexture(nullptr),
	vWidth(0),
	vHeight(0)
{

}

Texture::Texture(std::string path, SDL_Renderer* pRenderer)
{
	loadTextureNonChroma(path, pRenderer);
}

Texture::~Texture()
{
	free();
}

bool Texture::loadTextureNonChroma(std::string path, SDL_Renderer* renderer)
{
	free();

	SDL_Surface* nSurf = IMG_Load(path.c_str());

	if (nSurf == nullptr) {
		std::cout << "Cannot load Surface : " << IMG_GetError() << '\n';
		return false;
	}

	pTexture = SDL_CreateTextureFromSurface(renderer, nSurf);
	
	if (pTexture == nullptr) {
		std::cout << "Cannot create Texture : " << SDL_GetError() << '\n';
		return false;
	}

	vWidth = nSurf->w;
	vHeight = nSurf->h;

	SDL_FreeSurface(nSurf);

	
	return true;
}
	

bool Texture::loadTexture(std::string path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	free();

	SDL_Surface* nSurf = IMG_Load(path.c_str());

	if (nSurf == nullptr) {
		std::cout << "Cannot load Surface : " << IMG_GetError() << '\n';
		return false;
	}

	SDL_SetColorKey(nSurf, SDL_TRUE, SDL_MapRGB(nSurf->format, r, g, b));

	pTexture = SDL_CreateTextureFromSurface(renderer, nSurf);

	if (pTexture == nullptr) {
		std::cout << "Cannot create Texture : " << SDL_GetError() << '\n';
		return false;
	}

	vWidth = nSurf->w;
	vHeight = nSurf->h;

	SDL_FreeSurface(nSurf);

	return true;
}

void Texture::renderTexture(int x, int y, SDL_Renderer* renderer, SDL_Rect* srcRect)
{
	SDL_Rect renderRect = { x, y, vWidth, vHeight };
	
	SDL_RenderCopy(renderer, pTexture, srcRect, &renderRect);
}
void Texture::renderTexture(int x, int y, int width, int height, SDL_Renderer* renderer, SDL_Rect* srcRect)
{
	SDL_Rect renderRect = { x, y, width, height };
	SDL_RenderCopy(renderer, pTexture, srcRect, &renderRect);
}


int Texture::getWidth()
{
	return vWidth;
}

int Texture::getHeight()
{
	return vHeight;
}

