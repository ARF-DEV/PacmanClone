#pragma once


#include "Entity.h"
#include "Renderer.h"

class Coin : public Entity {
public:
	Coin(Vec2<int> centerPos, Animation& anim, SDL_Rect collisionRect)
		:
		Entity({0, 0}, anim, collisionRect)
	{
		setCenterPos(centerPos);
	}

	void draw(Renderer& renderer) override;
	bool isEaten() {
		return eaten;
	}
	void setEaten(bool bVal) {
		eaten = bVal;
	}
private:
	bool eaten = false;
};