#pragma once
#include<SDL.h>
#include<vector>

#include"Texture.h"
#include"Animation.h"
#include"Vec2.h"
#include"Texture.h"
#include"Renderer.h"
class Entity {
public:
	Entity() = default;
	Entity(Vec2<int> _topLeft, Animation& _animation)
		:
		topLeft(_topLeft),
		animation(_animation)
	{}
	virtual void start();
	virtual void update();
	virtual void lateUpdate();
	virtual void draw(Renderer& renderer);

	SDL_Rect getRect(); 
	Vec2<int> getCenter();
	void setCenterPos(Vec2<int> centerPos) {
		topLeft = {centerPos.x - animation.getWidth() / 2, centerPos.y - animation.getHeight() / 2};
	}
protected:	
	Vec2<int> topLeft;
	Animation& animation;
};