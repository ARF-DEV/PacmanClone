#pragma once
#include "Entity.h"
class Pacman : public Entity {
public:
	Pacman(Vec2<int> _pos, Animation& anim) 
		:
		Entity(_pos, anim),
		dir({0,0})
	{}
	void update() override;
private:
	Vec2<int> dir;
};