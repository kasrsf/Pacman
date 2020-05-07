#include <SDL2/SDL.h>
#include "map.h"
#include "clyde.h"
#include "constants.h"
#include "ghost.h"

Clyde::Clyde(Texture* t1, Texture* t2, Texture* t3, Map* m) 
	: Ghost(t1, t2, t3, m)
{
	posX = CLYDE_STARTX;
	posY = CLYDE_STARTY;

	mapX = posX / TILE_WIDTH;
	mapY = posY / TILE_HEIGHT;

	targetX = 1;
	targetY = 1;

	ghostId = CLYDE_ID;

	direction = MODE_LEFT;
}

void Clyde::set_target()
{
	if (!is_in_house() && !dead)
	{
		canPassFence = false;
	
		if (SDL_GetTicks() - map->get_start_time() < GHOST_SCATTER_INTERVAL)
		{
			targetX = CLYDE_SCATTERX;
			targetY = CLYDE_SCATTERY;
		}
		else if (map->in_chase_mode())
		{
			targetX = CLYDE_SCATTERX;
			targetY = CLYDE_SCATTERY;
		}
		else
		{
			targetX = map->get_pacman_x();
			targetY = map->get_pacman_y();

			if (get_squared_distance(mapX, mapY) <= (CLYDE_TRAIL_RADIUS * CLYDE_TRAIL_RADIUS))
			{
				targetX = CLYDE_SCATTERX;
				targetY = CLYDE_SCATTERY;
			}
		}
	}
	else if (dead)
	{
		canPassFence = true;
		targetX = CLYDE_STARTX / TILE_WIDTH;
		targetY = CLYDE_STARTY / TILE_HEIGHT;

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

Clyde::~Clyde()
{
	normalTexture = NULL;
	scaredTexture = NULL;	
	map = NULL;
}
