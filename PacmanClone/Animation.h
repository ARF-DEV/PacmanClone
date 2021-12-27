#pragma once
#include"Texture.h"
#include<SDL.h>
#include<vector>

class Animation {
public:
	Animation(std::string pathToTexture, SDL_Renderer* pRenderer, int x, int y, int width, int height, int nFrames);
	Animation(Texture* pTexture, int x, int y, int width, int height, int nFrames);
	Animation(const Animation& other) = delete;
	Animation& operator=(const Animation& other) = delete;
	~Animation();
	void draw(int xPos, int yPos, SDL_Renderer* pRenderer);
	void setLoop(bool loop);
	void next();

private:
	std::vector<SDL_Rect> spriteBoxes;
	Texture* pTexture;
	int nFrames;
	int curFrame = 0;
	static constexpr float nextDelay = 0.1f;
	float timePass = 0;
	float prev = 0;
	float now = 0;
	bool isLooping = true;
};