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
		flags(_flags),
		width(0),
		height(0)
	{}

	void setFlags(uint8_t _flags) {
		flags = _flags;
	}

	void resetFlags() {
		flags = 0;
	}

	uint8_t checkFlags(uint8_t _flags) {
		return flags & _flags;
	}
	void setPosition(Vec2<int> pos) {
		this->pos = pos;
	}
	void setSize(int width, int height) {
		this->height = height;
		this->width = width;
	}

	void draw(Renderer& renderer) {
		
		//std::cout << "draw at" << "{" << pos.x << "," << pos.y << "}" << '\n';
		if ((flags & TileState::Wall) > 0) {
			const SDL_Rect drawRect = { pos.x, pos.y, width, height };
			SDL_SetRenderDrawColor(renderer.getRenderer(), 0x0, 0x0, 0xFF, 0xFF);
			SDL_RenderFillRect(renderer.getRenderer(), &drawRect);
		}

		#if PA_DEBUG == 1
		if ((flags & TileState::Road) > 0) {
			const SDL_Rect drawRect = { pos.x, pos.y, width, height };
			SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0x0, 0x0, 0xFF);
			SDL_RenderDrawRect(renderer.getRenderer(), &drawRect);
		}
		#endif

	}

	SDL_Rect getRect() {
		return { pos.x, pos.y, width, height };
	}

	Vec2<int> getCenter() {
		return { pos.x + getRect().w / 2, pos.y + getRect().h / 2 };
	}

private:
	uint8_t flags;
	Vec2<int> pos;
	int width, height;
};