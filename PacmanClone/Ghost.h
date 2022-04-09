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
#include <functional>
class Ghost : public Entity {
public:
	enum class GhostState
	{
		Chase,
		Scatter,
		Frightened,
		Eaten
	};
	Ghost(Vec2<int> _topLeft, Animation&& anim, SDL_Rect collisionRect, Map& _map, Pacman& pacman, Vec2<int> chaseTargetPos, std::function<Vec2<int>()> processTargetPosFunc)
		:
		Entity(_topLeft, std::move(anim), collisionRect),
		map(_map),
		pacman(pacman),
		scatterTargetPos(scatterTargetPos),
		processTargetPosFunc(processTargetPosFunc),
		homePos(_topLeft),
		frightenedTimer(10.0f),
		scatterTimer(10.0f)
	{
		std::cout << sizeof(animations) / sizeof(std::unique_ptr<Animation>) << std::endl;
	}

	void setTarget(Vec2<int> targetPos);
	void update() override;
	void draw(Renderer& renderer) override;
	Tile findNearestTile();
	void moveToPos(Vec2<int> pos);
	void setState(GhostState _state) {
		state = _state;
	}
	void reset() {
		dir = { 0, 0 };
		target = { 0, 0 };
		turnPoint = { 0, 0 };
	}

	void setHomePos(Vec2<int> _homePos) {
		homePos = _homePos;
	}
	void flip() {
		auto neighbouringTiles = getNeighbouringTiles();
		Tile targetTile = map.getTile(getCenter());
		int minDistance = 1e9;
		for (auto i = neighbouringTiles.begin(); i != neighbouringTiles.end(); i++) {
			if (i->first == -dir && !i->second.checkFlags(Tile::TileState::Wall)) {
				targetTile = i->second;
				break;
			}
		}
		turnPoint = targetTile.getCenter();
		dir = -dir;
	}
	bool isEaten() {
		return state == GhostState::Eaten;
	}
	bool targetReached() {
		return abs((target - getCenter()).getLength()) < 0.2f;
	}
	bool isFrightened() {
		return state == GhostState::Frightened;
	}

	void scatter() {
		scatterTimer.resetTimePass();
		flip();
		state = Ghost::GhostState::Scatter;
	}
	void frightened() {
		frightenedTimer.resetTimePass();
		flip();
		state = Ghost::GhostState::Frightened;
	}
	void setScatterTarget(Vec2<int> pos) {
		scatterTargetPos = pos;
	}
	Vec2<int> getScatterTarget() {
		return scatterTargetPos;
	}
	std::unordered_map<Vec2<int>, Tile&, Vec2<int>::Vei2Hasher> getNeighbouringTiles();
private:
	GhostState state = GhostState::Chase;
	Pacman& pacman;
	Map& map;
	float turnThreshold = 0.5f;
	Timer frightenedTimer;
	Timer scatterTimer;
	std::random_device rd;
	std::mt19937 rng{rd()};
	std::function<Vec2<int>()> processTargetPosFunc = nullptr;
	Vec2<int> dir = { 0, 0 };
	Vec2<int> turnPoint;
	Vec2<int> target;
	Vec2<int> scatterTargetPos;
	Vec2<int> homePos;
	int speed = 2;
};