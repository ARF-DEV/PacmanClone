#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <math.h>

#include "Tile.h"
#include "Vec2.h"
#include "Renderer.h"
#include "Coin.h"
class Map {
public:
	Map(Vec2<int> _topLeft = {0, 0}, int _mapWidth = 32, int _mapHeight = 32, int _tileSize = 32)
		:
		topLeft(_topLeft),
		mapWidth(_mapWidth),
		mapHeight(_mapHeight),
		tileSize(_tileSize),
		tiles(nullptr)
	{}
	~Map();

	Tile& getTile(Vec2<int> pos);
	Tile& getLeftTile(Vec2<int> pos);
	Tile& getRightTile(Vec2<int> pos);
	Tile& getTopTile(Vec2<int> pos);
	Tile& getBottomTile(Vec2<int> pos);
	Tile& getTileByIndex(int i, int j);
	std::vector<Vec2<int>> getGhostSpawns() {
		return ghostSpawns;
	}
	bool wallInfront(Vec2<int> pos, Vec2<int> dir);
	void loadMapFromImage(std::string path);
	void loadMapFromVector(std::vector<int> mapVector, Animation&& coinAnim, Animation&& bigCoinAnim, int _mapWidth, int _mapHeight);
	void draw(Renderer& renderer);
	int getTileSize();
	void reset() {
		for (auto& coin : listOfCoin) {
			coin.setEaten(false);
		}
	}
	Vec2<int> getTopLeft() {
		return topLeft;
	}
	Vec2<int> getPlayerSpawn() {
		return playerSpawn;
	}
	std::vector<Coin>& getListOfVector() {
		return listOfCoin;
	}
	std::vector<Tile> getNeibouringRoads(Vec2<int> pos);
private:
	Vec2<int> topLeft;
	Vec2<int> playerSpawn;
	std::vector<Vec2<int>> ghostSpawns{4};
	std::vector<Coin> listOfCoin;
	int mapWidth, mapHeight;
	int tileSize;
	Tile* tiles;
	
};