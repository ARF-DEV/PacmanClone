#include "Coin.h"

void Coin::draw(Renderer& renderer)
{
	animation.draw(topLeft.x, topLeft.y, renderer.getRenderer());
	SDL_Rect renderColRect = getCollisionRect();
	SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0x0, 0x0, 0xFF);
	SDL_RenderDrawRect(renderer.getRenderer(), &renderColRect);
}
