#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

#include "Tile.h"
#include "Vec2.h"
#include "Renderer.h"
class Map {
public:
	Map(Vec2<int> _startPos = {0, 0}, int _mapWidth = 32, int _mapHeight = 32, int _tileWidth = 32, int _tileHeight = 32)
		:
		startPos(_startPos),
		mapWidth(_mapWidth),
		mapHeight(_mapHeight),
		tileWidth(_tileWidth),
		tileHeight(_tileHeight),
		tiles(nullptr)
	{}
	~Map() {
		delete[] tiles;
		tiles = nullptr;
	}

	Tile& getTile(Vec2<int> pos);
	void loadMapFromImage(std::string path);
	void loadMapFromVector(std::vector<int> mapVector, int _mapWidth, int _mapHeight);
	void draw(Renderer& renderer);
private:
	Vec2<int> startPos;
	int mapWidth, mapHeight;
	int tileWidth, tileHeight;
	Tile* tiles;
};