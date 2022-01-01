#include "Entity.h"
void Entity::start()
{}
void Entity::update()
{}

void Entity::draw(Renderer& renderer)
{
	animation.draw(pos.getX(), pos.getY(), renderer.getRenderer());
}
