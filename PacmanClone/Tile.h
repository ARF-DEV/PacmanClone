#pragma once
#include <cstdint>
#include <iostream>

#include "Vec2.h"
#include "Renderer.h"

class Tile {
public:
	enum TileState
	{
		PacmanSpawn = 1,
		Road = 2,
		Coin = 4,
		GhostSpawn = 8,
		Wall = 16,
	};

	Tile()
		:
		flags(TileState::Wall),
		pos({0,0}),
		width(0),
		height(0)
	{}

	Tile(uint8_t _flags)
		:
		flags(_flags)
	{}

	void setFlags(uint8_t _flags) {
		flags = _flags;
	}

	void resetFlags() {
		flags = 0;
	}

	void setPosition(Vec2<int> pos) {
		this->pos = pos;
	}
	void setSize(int width, int height) {
		this->height = height;
		this->width = width;
	}

	void draw(Renderer& renderer) {
		
		//std::cout << "draw at" << "{" << pos.getX() << "," << pos.getY() << "}" << '\n';
		if ((flags & TileState::Wall) > 0) {
			const SDL_Rect drawRect = { pos.getX(), pos.getY(), width, height };
			SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0x0, 0x0, 0xFF);
			SDL_RenderFillRect(renderer.getRenderer(), &drawRect);
		}

	}
private:
	uint8_t flags;
	Vec2<int> pos;
	int width, height;
};