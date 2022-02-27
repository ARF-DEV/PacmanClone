#include "Pacman.h"



void Pacman::update()
{
	std::cout << superPower << '\n';
	if (superPower) {
		superPowerTimer.updateTicks();
		if (!superPowerTimer.passing()) {
			superPowerTimer.updateTimePass();
		}
		else {
			superPower = false;
		}
	}

	/*
		direction of pacman will change if the inputed direction is the opposite of current direction
		if not then the inputed direction will be saved
	*/
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	if (currentKeyStates[SDL_SCANCODE_W]) {

		if (-dir == Vec2<int>{0, -1}) {
			dir = -dir;
		}
		else {
			savedDir = { 0, -1 };
			turnPoint = map.getTile(getCenter()).getCenter();
		}
	}
	else if (currentKeyStates[SDL_SCANCODE_S]) {
		

		if (-dir == Vec2<int>{0, 1}) {
			dir = -dir;
		}
		else {
			savedDir = { 0, 1 };
			turnPoint = map.getTile(getCenter()).getCenter();
		}
	}
	else if (currentKeyStates[SDL_SCANCODE_A]) {
		
		
		if (-dir == Vec2<int>{-1, 0}) {
			dir = -dir;
		}
		else {
			savedDir = { -1, 0 };
			turnPoint = map.getTile(getCenter()).getCenter();
		}
	}
	else if (currentKeyStates[SDL_SCANCODE_D]) {
		
		if (-dir == Vec2<int>{1, 0}) {
			dir = -dir;
		}
		else {
			savedDir = { 1, 0 };
			turnPoint = map.getTile(getCenter()).getCenter();
		}

	}
	
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
	/*
		the saved direction will become current direction if the tile in the direction of the saved direction is a road 
		and the center position is equal to turnPoint

		if those two condition doesnt met then, the turnPoint will become the center of the tile infront of the current tile.
	*/
	if (savedDir == Vec2<int>{0, -1} && map.getTopTile(getCenter()).checkFlags(Tile::TileState::Road) > 0 ||
		savedDir == Vec2<int>{0, 1} && map.getBottomTile(getCenter()).checkFlags(Tile::TileState::Road) > 0 ||
		savedDir == Vec2<int>{-1, 0}&& map.getLeftTile(getCenter()).checkFlags(Tile::TileState::Road) > 0 || 
		savedDir == Vec2<int>{1, 0}&& map.getRightTile(getCenter()).checkFlags(Tile::TileState::Road) > 0
		) {
		if ((turnPoint - getCenter()).getLength() <= turnThreshold) {
			dir = savedDir;
			savedDir = { 0,0 };
			turnPoint = { -1, -1 };
		}
	}
	
	else if (savedDir != Vec2<int>{0, 0}) {
		Vec2<int> pos = getCenter() - map.getTopLeft();
		int tileSize = map.getTileSize();
		turnPoint = map.getTileByIndex(pos.y  / tileSize + dir.y, pos.x / tileSize + dir.x).getCenter();
	}

	
}

void Pacman::lateUpdate()
{
	if (!map.wallInfront(getCenter(), dir)) {
		topLeft += dir;
	}
}

void Pacman::draw(Renderer& renderer)
{
	if (!dead) {
		Entity::draw(renderer);
		SDL_Rect rect = {turnPoint.x, turnPoint.y, animations[(int)currentAnimation]->getWidth()/4 ,animations[(int)currentAnimation]->getHeight()/4};
		SDL_SetRenderDrawColor(renderer.getRenderer(), 0x0, 0xFF, 0x0, 0xFF);
		SDL_RenderFillRect(renderer.getRenderer(), &rect);
		SDL_Rect renderColRect = getCollisionRect();
		SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0x0, 0x0, 0xFF);
		SDL_RenderDrawRect(renderer.getRenderer(), &renderColRect);
	}

}
