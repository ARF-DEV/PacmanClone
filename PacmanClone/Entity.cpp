#include "Entity.h"
void Entity::update(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN) {
		int x = 0 , y = 0;
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			y = -1;
			break;
		case SDLK_s:
			y = 1;
			break;
		case SDLK_a:
			x = -1;
			break;
		case SDLK_d:
			x = 1;
			break;
		default:
			break;
		}
		pos += {x, y};
	}
}

void Entity::draw(Renderer& renderer)
{
	animation.draw(pos.getX(), pos.getY(), renderer.getRenderer());
}
