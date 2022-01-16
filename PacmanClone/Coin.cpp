#include "Coin.h"

void Coin::draw(Renderer& renderer)
{
	animation.draw(topLeft.x, topLeft.y, renderer.getRenderer());
}
