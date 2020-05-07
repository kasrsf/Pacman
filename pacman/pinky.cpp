#include <SDL2/SDL.h>
#include "map.h"
#include "pinky.h"
#include "constants.h"
#include "ghost.h"

Pinky::Pinky(Texture* t1, Texture* t2, Texture* t3, Map* m) 
	: Ghost(t1, t2, t3, m)
{
	posX = PINKY_STARTX;
	posY = PINKY_STARTY;

	mapX = posX / TILE_WIDTH;
	mapY = posY / TILE_HEIGHT;

	direction = MODE_LEFT;

	ghostId = PINKY_ID;
}

void Pinky::set_target()
{
	if (!is_in_house() && !dead)
	{
		canPassFence = false;

		if (SDL_GetTicks() - map->get_start_time() < GHOST_SCATTER_INTERVAL)
		{
			targetX = PINKY_SCATTERX;
			targetY = PINKY_SCATTERY;
		}
		else if (map->in_chase_mode())
		{
			targetX = PINKY_SCATTERX;
			targetY = PINKY_SCATTERY;
		}
		else
		{
			// get pacman info
			int pacX = map->get_pacman_x();
			int pacY = map->get_pacman_y();
			int pacDir = map->get_pacman_dir();

			switch (pacDir)
			{
			case MODE_UP:
				targetX = pacX;
				targetY = pacY - PINKY_TARGET_OFFSET;
				break;
			case MODE_DOWN:
				targetX = pacX;
				targetY = pacY + PINKY_TARGET_OFFSET;
				break;
			case MODE_LEFT:
				targetX = pacX - PINKY_TARGET_OFFSET;
				targetY = pacY;
				break;
			case MODE_RIGHT:
				targetX = pacX + PINKY_TARGET_OFFSET;
				targetY = pacY;
				break;
			}
		}
	}
	else if (dead)
	{
		canPassFence = true;
		targetX = INKY_STARTX / TILE_WIDTH;
		targetY = INKY_STARTY / TILE_HEIGHT;

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

Pinky::~Pinky()
{
	normalTexture = NULL;
	scaredTexture = NULL;	
	map = NULL;
}
