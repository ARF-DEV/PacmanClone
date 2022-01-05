#pragma once
#include "Renderer.h"
#include "Entity.h"
#include "Map.h"
class Pacman : public Entity {
public:
	Pacman(Vec2<int> _topLeft, Animation& anim, Map& _map)
		:
		Entity(_topLeft, anim),
		dir({0,0}),
		savedDir({0,0}),
		turnPoint({-1, -1}),
		map(_map)
	{}
	void update() override;
	void lateUpdate() override;
	void draw(Renderer& renderer) override;
private:
	Vec2<int> dir;
	Vec2<int> turnPoint;
	Vec2<int> savedDir;
	float turnThreshold = 1.5f;
	Map& map;
};