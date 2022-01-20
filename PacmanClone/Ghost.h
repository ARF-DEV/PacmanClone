#pragma once
#include <SDL.h>
#include <unordered_map>
#include <random>
#include <algorithm>

#include "Entity.h"
#include "Map.h"
#include "Vec2.h"
#include "Animation.h"
#include "Pacman.h"

class Ghost : public Entity {
public:
	enum class GhostState
	{
		Chase,
		Scatter,
		Frightened,
		Eaten
	};

	Ghost(Vec2<int> _topLeft, Animation& anim, SDL_Rect collisionRect, Map& _map, Pacman& pacman, Vec2<int> chaseTargetPos)
		:
		Entity(_topLeft, anim, collisionRect),
		map(_map),
		pacman(pacman),
		chaseTargetPos(chaseTargetPos)
	{}

	void setTarget(Vec2<int> targetPos);
	void update() override;
	void draw(Renderer& renderer) override;
	Tile findNearestTile();
	void moveToPos(Vec2<int> pos);
	void setState(GhostState _state) {
		state = _state;
	}

private:
	Vec2<int> dir = { 0, 0 };
	Vec2<int> turnPoint;
	Vec2<int> target;
	Vec2<int> chaseTargetPos;
	GhostState state = GhostState::Chase;

	Pacman& pacman;
	Map& map;
	float turnThreshold = 0.5f;
	std::random_device rd;
	std::mt19937 rng{rd()};
	
};