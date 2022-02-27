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
		map(_map),
		superPowerTimer(10.0f)
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

	void enableSuperPower() {
		superPowerTimer.resetTimePass();
		superPower = true;
	}
	void disableSuperPower() {
		superPower = false;
	}
	bool isSuper() {
		return superPower;
	}
private:
	Vec2<int> dir;
	Vec2<int> turnPoint;
	Vec2<int> savedDir;
	float turnThreshold = 1.5f;
	Map& map;
	bool superPower = false;
	bool dead = false;
	Timer superPowerTimer;
};