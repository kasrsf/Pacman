#include <SDL2/SDL.h>
#include "blinky.h"
#include "constants.h"
#include "map.h"
#include "ghost.h"

Blinky::Blinky(Texture* t1, Texture* t2, Texture* t3, Map* m) 
	: Ghost(t1, t2, t3, m)
{
	posX = BLINKY_STARTX;
	posY = BLINKY_STARTY;

	mapX = posX / TILE_WIDTH;
	mapY = posY / TILE_HEIGHT;

	targetX = 1;
	targetY = 1;

	ghostId = BLINKY_ID;

	direction = MODE_LEFT;
}

void Blinky::set_target()
{
	if (!is_in_house() && !dead)
	{
		canPassFence = false;

		if (SDL_GetTicks() - map->get_start_time() < GHOST_SCATTER_INTERVAL)
		{
			targetX = BLINKY_SCATTERX;
			targetY = BLINKY_SCATTERY;
		}
		else if (map->in_chase_mode())
		{
			targetX = BLINKY_SCATTERX;
			targetY = BLINKY_SCATTERY;
		}
		else
		{
			targetX = map->get_pacman_x();
			targetY = map->get_pacman_y();
		}
	}
	else if (dead)
	{
		canPassFence = true;
		targetX = BLINKY_STARTX / TILE_WIDTH;
		targetY = BLINKY_STARTY / TILE_HEIGHT;

		if ((mapX == targetX) && (mapY == targetY))
		{
			dead = false;
		}
	}
	else 
	{
		targetX = GHOST_HOUSE_EXITX;
		targetY = GHOST_HOUSE_EXITY;
	}
}

int Blinky::get_x()
{
	return mapX;
}

int Blinky::get_y()
{
	return mapY;
}

Blinky::~Blinky()
{
	normalTexture = NULL;
	scaredTexture = NULL;
	map = NULL;
}
