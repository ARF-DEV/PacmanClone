#include "Animation.h"

Animation::Animation(std::string pathToTexture, SDL_Renderer* pRenderer, int x, int y, int width, int height, int _nFrames)
	:
	nFrames(_nFrames)
{
	pTexture = new Texture(pathToTexture, pRenderer);
	
	for (int i = 0; i < nFrames; i++) {
		int rX = i * width;
		SDL_Rect spriteBox = { x, y, width, height };
		spriteBoxes.push_back(spriteBox);
	}
}

Animation::Animation(Texture* pTexture, int x, int y, int width, int height, int _nFrames)
	:
	pTexture(pTexture),
	nFrames(_nFrames)
{
	for (int i = 0; i < nFrames; i++) {
		int xBox = i * width;
		SDL_Rect spriteBox = { xBox, y, width, height };
		spriteBoxes.push_back(spriteBox);
	}
}

Animation::~Animation()
{
	delete pTexture;
}

void Animation::draw(int xPos, int yPos, SDL_Renderer* pRenderer)
{
	prev = now;
	now = SDL_GetTicks64() / 1000.0f;
	pTexture->renderTexture(xPos, yPos, spriteBoxes[curFrame].w, spriteBoxes[curFrame].h, pRenderer, &spriteBoxes[curFrame]);
	if (timePass < nextDelay) {
		timePass += (now - prev);
	}
	else {
		next();
		timePass = 0;
	}
}

void Animation::setLoop(bool loop)
{
	isLooping = loop;
}

void Animation::next()
{
	curFrame = ++curFrame % this->nFrames;
}
