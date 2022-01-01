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
	Entity(Vec2<int> _pos, Animation& _animation)
		:
		pos(_pos),
		animation(_animation)
	{}
	void start();
	void update(SDL_Event& e);
	void draw(Renderer& renderer);
private:
	
	Vec2<int> pos;
	Animation& animation;
};