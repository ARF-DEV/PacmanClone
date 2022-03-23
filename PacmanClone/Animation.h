#pragma once
#include<SDL.h>
#include<vector>

#include"Texture.h"
#include"Timer.h"

class Animation {
public:
	Animation(Texture& pTexture, int x, int y, int srcWidth, int srcHeight, int renderWidth, int renderHeight, int nFrames);
	Animation& operator=(const Animation& other) = default;
	Animation(const Animation& other) = default;
	void draw(int xPos, int yPos, SDL_Renderer* pRenderer);
	void setLoop(bool loop);
	void next();
	int getWidth();
	int getHeight();
private:
	std::vector<SDL_Rect> spriteBoxes;
	
	int nFrames;
	int curFrame = 0;
	int srcWidth;
	int srcHeight;
	int renderHeight;
	int renderWidth;
	bool isLooping = true;

	Texture& texture;
	Timer timer{0.05f};
};