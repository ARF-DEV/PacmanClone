#include "Pacman.h"

void Pacman::update()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	if (currentKeyStates[SDL_SCANCODE_W])
		dir = { 0, -1 };
	else if (currentKeyStates[SDL_SCANCODE_S])
		dir = { 0, 1 };
	else if (currentKeyStates[SDL_SCANCODE_A])
		dir = { -1, 0 };
	else if (currentKeyStates[SDL_SCANCODE_D])
		dir = { 1, 0 };

	pos += dir;
}
