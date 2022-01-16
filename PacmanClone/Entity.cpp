#include "Entity.h"
void Entity::start()
{}
void Entity::update()
{}

void Entity::lateUpdate()
{}

void Entity::draw(Renderer& renderer)
{
	animation.draw(topLeft.x, topLeft.y, renderer.getRenderer());
}

SDL_Rect Entity::getRect()
{
	return { topLeft.x, topLeft.y, animation.getWidth(), animation.getHeight() };
}

SDL_Rect Entity::getCollisionRect()
{
	return {collisionRect.x + topLeft.x, collisionRect.y + topLeft.y, collisionRect.w, collisionRect.h};
}

Vec2<int> Entity::getCenter()
{
	return { topLeft.x + getRect().w / 2, topLeft.y + getRect().h / 2 };
}
