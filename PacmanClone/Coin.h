#pragma once


#include "Entity.h"
#include "Renderer.h"

class Coin : public Entity {
public:
	Coin(Vec2<int> centerPos, Animation&& coinAnim, Animation&& bigCoinAnim, SDL_Rect collisionRect, bool isBigCoin = false)
		:
		Entity({ 0, 0 }, std::move(coinAnim), collisionRect),
		bigCoin(isBigCoin)
	{
		setCenterPos(centerPos);
		addAnimation(AnimState::BIG_COIN, std::make_unique<Animation>(std::move(bigCoinAnim)));
		if (bigCoin) {
			currentAnimation = AnimState::BIG_COIN;
		}
	}

	void draw(Renderer& renderer) override;
	bool isEaten() {
		return eaten;
	}
	void setEaten(bool bVal) {
		eaten = bVal;
	}
	bool isBigCoin() {
		return bigCoin;
	}
private:
	bool eaten = false;
	bool bigCoin = false;
};