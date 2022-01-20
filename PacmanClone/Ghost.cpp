#include "Ghost.h"

void Ghost::setTarget(Vec2<int> targetPos)
{
	target = targetPos;
}

void Ghost::update()
{
	if ((turnPoint - getCenter()).getLength() <= turnThreshold || turnPoint == Vec2<int>{0, 0}) {
		setTarget(pacman.getCenter());
		nextTargetTile = findNearestTile();
		turnPoint = nextTargetTile.getCenter();
	}
	
	moveToPos(nextTargetTile.getCenter());
}

void Ghost::draw(Renderer& renderer)
{
	Entity::draw(renderer);

	SDL_Rect rect = { turnPoint.x, turnPoint.y, animation.getWidth() / 4 ,animation.getHeight() / 4 };
	SDL_SetRenderDrawColor(renderer.getRenderer(), 0x0, 0x0, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer.getRenderer(), &rect);
	SDL_Rect renderColRect = getCollisionRect();
	SDL_SetRenderDrawColor(renderer.getRenderer(), 0x0, 0x0, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer.getRenderer(), &renderColRect);

}

Tile Ghost::findNearestTile()
{
	std::unordered_map<Vec2<int>, Tile&, Vec2<int>::Vei2Hasher> neighbouringTiles{
		{{0, -1}, map.getTopTile(getCenter())},
		{{1, 0}, map.getRightTile(getCenter())},
		{{0, 1},map.getBottomTile(getCenter())},
		{{-1, 0}, map.getLeftTile(getCenter())}
	};
	Tile nearestTile;
	int minDistance = 1e9;
	for (auto i = neighbouringTiles.begin(); i != neighbouringTiles.end(); i++) {

		if (i->first == -dir || i->second.checkFlags(Tile::TileState::Wall))
			continue;
		std::cout << dir.x << " " << dir.y << " ";
		std::cout << i->first.x << " " << i->first.y << std::endl;
		int distance = (target - i->second.getCenter()).getLength();
		if (distance < minDistance) {
			minDistance = distance;
			nearestTile = i->second;
		}
	}

	return nearestTile;
}

void Ghost::moveToPos(Vec2<int> pos)
{
	dir = (pos - getCenter()).normalize();

	setCenterPos(getCenter() + (dir * 1));
}
