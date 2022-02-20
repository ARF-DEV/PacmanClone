#include "Ghost.h"

void Ghost::setTarget(Vec2<int> targetPos)
{
	target = targetPos;
}
void Ghost::update()
{

	Tile nextTargetTile;
	if ((turnPoint - getCenter()).getLength() <= turnThreshold || turnPoint == Vec2<int>{0, 0}) {
		
		switch (state)
		{
		case Ghost::GhostState::Chase:
		{
			Vec2<int> a = processTargetPosFunc(pacman);
			std::cout << pacman.getCenter().x << ' ' << pacman.getCenter().y << '\n';
			std::cout << a.x << ' ' << a.y << '\n';
			setTarget(a);
			break;
		}
		case Ghost::GhostState::Scatter:
			setTarget(scatterTargetPos);
			break;
		case Ghost::GhostState::Frightened:
		{
			auto neighbouringRoads = map.getNeibouringRoads(getCenter());
			neighbouringRoads.erase(std::remove_if(neighbouringRoads.begin(), neighbouringRoads.end(), [this](Tile& tile) {
				return (tile.getCenter() - getCenter()).normalize() == -dir;
			}), neighbouringRoads.end());
			
			if (neighbouringRoads.size() != 0) {
 				std::uniform_int_distribution<int> dist{ 0, static_cast<int>(neighbouringRoads.size() - 1)};
				int randInt = dist(rng);
				setTarget(neighbouringRoads[randInt].getCenter());
			}
			break;
		}
		case Ghost::GhostState::Eaten:
			// Back to Bases
			break;
		default:
			break;
		}
		
		
		nextTargetTile = findNearestTile();
		turnPoint = nextTargetTile.getCenter();
	}
	
	if (state != GhostState::Frightened) {
		if (currentAnimation != AnimState::UP && dir == Vec2<int>{0, -1}) {
			currentAnimation = AnimState::UP;
		}
		else if (currentAnimation != AnimState::DOWN && dir == Vec2<int>{0, 1}) {
			currentAnimation = AnimState::DOWN;
		}
		else if (currentAnimation != AnimState::LEFT && dir == Vec2<int>{-1, 0}) {
			currentAnimation = AnimState::LEFT;
		}
		else if (currentAnimation != AnimState::RIGHT && dir == Vec2<int>{1, 0}) {
			currentAnimation = AnimState::RIGHT;
		}
	}
	else {
		currentAnimation = AnimState::FRIGHTENED;
	}

	moveToPos(turnPoint);
}

void Ghost::draw(Renderer& renderer)
{
	Entity::draw(renderer);

	SDL_Rect rect = { target.x, target.y, animations[(int)currentAnimation]->getWidth() / 4 ,animations[(int)currentAnimation]->getHeight() / 4 };
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
