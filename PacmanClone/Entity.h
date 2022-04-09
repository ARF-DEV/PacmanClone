#pragma once
#include<SDL.h>
#include<vector>
#include<memory>
#include<array>

#include"Texture.h"
#include"Animation.h"
#include"Vec2.h"
#include"Texture.h"
#include"Renderer.h"

class Entity {
public:
	enum class AnimState {
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
		PACMAN_COUNT,
		FRIGHTENED,
		GHOST_COUNT,
		BIG_COIN,
		G_EATEN_UP,
		G_EATEN_DOWN,
		G_EATEN_LEFT,
		G_EATEN_RIGHT,
		G_COUNT,
	};
public:
	Entity() = default;
	Entity(Vec2<int> _topLeft, Animation&& _animation, SDL_Rect _collisionRect = {0, 0, 0, 0})
		:
		topLeft(_topLeft),
		collisionRect(_collisionRect)
	{
		addAnimation(AnimState::UP, std::make_unique<Animation>(std::move(_animation)));
	}
	virtual void start();
	virtual void update();
	virtual void lateUpdate();
	virtual void draw(Renderer& renderer);

	SDL_Rect getRect();
	SDL_Rect getCollisionRect();
	Vec2<int> getCenter();
	void setCenterPos(Vec2<int> centerPos) {
		topLeft = {centerPos.x - animations[(int)currentAnimation]->getWidth() / 2, centerPos.y - animations[(int)currentAnimation]->getHeight() / 2};
	}
	void addAnimation(AnimState key, std::unique_ptr<Animation> animation) {
		animations[(int)key] = std::move(animation);
	}

	void setCurrentAnimation(AnimState key) {
		currentAnimation = key;
	}
protected:	
	Vec2<int> topLeft;
	std::unique_ptr<Animation> animations[(int)AnimState::G_COUNT];
	AnimState currentAnimation = AnimState::UP;
	SDL_Rect collisionRect;
};