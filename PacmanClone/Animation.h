#pragma once
#include<SDL.h>
#include<vector>

#include"Texture.h"
#include"Timer.h"

class Animation {
public:
	Animation(Texture& pTexture, int x, int y, int width, int height, int nFrames);
	void draw(int xPos, int yPos, SDL_Renderer* pRenderer);
	void setLoop(bool loop);
	void next();

private:
	std::vector<SDL_Rect> spriteBoxes;
	
	int nFrames;
	int curFrame = 0;
	bool isLooping = true;

	Texture& texture;
	Timer timer{0.1f};
	
};