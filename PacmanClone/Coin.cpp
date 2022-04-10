#include "Coin.h"

void Coin::draw(Renderer& renderer)
{
	animations[(int)currentAnimation]->draw(topLeft.x, topLeft.y, renderer.getRenderer());

	#if PA_DEBUG == 1
	SDL_Rect renderColRect = getCollisionRect();
	SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0x0, 0x0, 0xFF);
	SDL_RenderDrawRect(renderer.getRenderer(), &renderColRect);
	#endif
}
