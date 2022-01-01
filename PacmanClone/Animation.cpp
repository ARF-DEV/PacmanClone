#include "Animation.h"

Animation::Animation(Texture& pTexture, int x, int y, int width, int height, int _nFrames)
	:
	texture(pTexture),
	nFrames(_nFrames)
{
	std::cout << "animation" << std::endl;
	for (int i = 0; i < nFrames; i++) {
		int xBox = i * width;
		SDL_Rect spriteBox = { xBox, y, width, height };
		spriteBoxes.push_back(spriteBox);
	}
}

void Animation::draw(int xPos, int yPos, SDL_Renderer* pRenderer)
{
	timer.updateTicks();
	texture.renderTexture(xPos, yPos, spriteBoxes[curFrame].w, spriteBoxes[curFrame].h, pRenderer, &spriteBoxes[curFrame]);
	if (!timer.passing()) {
		timer.updateTimePass();
	}
	else {
		next();
		timer.resetTimePass();
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
