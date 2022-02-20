#include "Animation.h"

Animation::Animation(Texture& pTexture, int x, int y, int _srcWidth, int _srcHeight, int _renderWidth, int _renderHeight, int _nFrames)
	:
	texture(pTexture),
	nFrames(_nFrames),
	srcWidth(_srcWidth),
	srcHeight(_srcHeight),
	renderWidth(_renderWidth),
	renderHeight(_renderHeight)
{
	std::cout << "animation" << std::endl;
	for (int i = 0; i < nFrames; i++) {
		int xBox = i * srcWidth;
		SDL_Rect spriteBox = { x + xBox, y, srcWidth, srcHeight };
		spriteBoxes.push_back(spriteBox);
	}
}

void Animation::draw(int xPos, int yPos, SDL_Renderer* pRenderer)
{
	timer.updateTicks();
	texture.renderTexture(xPos, yPos, renderWidth, renderHeight, pRenderer, &spriteBoxes[curFrame]);
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

int Animation::getWidth()
{
	return renderWidth;
}

int Animation::getHeight()
{
	return renderHeight;
}
