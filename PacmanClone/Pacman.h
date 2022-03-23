#pragma once
#include "Renderer.h"
#include "Entity.h"
#include "Map.h"
#include "Timer.h"
class Pacman : public Entity {
public:
	Pacman(Vec2<int> _topLeft, Animation&& anim, SDL_Rect collisionRect, Map& _map)
		:
		Entity(_topLeft, std::move(anim), collisionRect),
		dir({0,0}),
		savedDir({0,0}),
		turnPoint({-1, -1}),
		map(_map)
	{}
	void update() override;
	void lateUpdate() override;
	void draw(Renderer& renderer) override;
	bool isDead() {
		return dead;
	}
	void deadIsTrue() {
		dead = true;
	}
	void reset() {
		dir = { 0, 0 };
		dead = false;
		turnPoint = { 0, 0 };
		savedDir = { -1, -1 };
	}

	Vec2<int> getDir() {
		return dir;
	}
private:
	Vec2<int> dir;
	Vec2<int> turnPoint;
	Vec2<int> savedDir;
	float turnThreshold = 4;
	Map& map;
	bool dead = false;
	int speed = 2;
};