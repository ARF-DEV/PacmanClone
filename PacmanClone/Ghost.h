#pragma once
#include <SDL.h>
#include <unordered_map>

#include "Entity.h"
#include "Map.h"
#include "Vec2.h"
#include "Animation.h"
#include "Pacman.h"

class Ghost : public Entity{
public:
	Ghost(Vec2<int> _topLeft, Animation& anim, SDL_Rect collisionRect, Map& _map, Pacman& pacman)
		:
		Entity(_topLeft, anim, collisionRect),
		map(_map),
		pacman(pacman)
	{}

	void setTarget(Vec2<int> targetPos);
	void update() override;
	//void lateUpdate() override;
	void draw(Renderer& renderer) override;
	Tile findNearestTile();
	void moveToPos(Vec2<int> pos);

private:
	Vec2<int> dir = { 0, 0 };
	Vec2<int> turnPoint;
	Vec2<int> target;

	Pacman& pacman;
	Tile nextTargetTile;
	Map& map;
	float turnThreshold = 0.5f;
};