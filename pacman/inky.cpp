#include <SDL2/SDL.h>
#include "inky.h"
#include "map.h"
#include "constants.h"
#include "ghost.h"

Inky::Inky(Texture* t1, Texture* t2, Texture* t3, Map* m, Blinky* b) 
	: Ghost(t1, t2, t3, m)
{
	posX = INKY_STARTX;
	posY = INKY_STARTY;

	mapX = posX / TILE_WIDTH;
	mapY = posY / TILE_HEIGHT;

	targetX = 1;
	targetY = 1;

	direction = MODE_LEFT;

	ghostId = INKY_ID;

	blinky = b;
}

void Inky::set_target()
{
	if (!is_in_house() && !dead)
	{
		canPassFence = false;

		if (SDL_GetTicks() - map->get_start_time() < GHOST_SCATTER_INTERVAL)
		{
			targetX = INKY_SCATTERX;
			targetY = INKY_SCATTERY;
		}
		else if (map->in_chase_mode())
		{
			targetX = INKY_SCATTERX;
			targetY = INKY_SCATTERY;
		}
		else
		{
			// get pacman info
			int pacX = map->get_pacman_x();
			int pacY = map->get_pacman_y();
			int pacDir = map->get_pacman_dir();

			// get blinky info
			int blinkX = blinky->get_x();
			int blinkY = blinky->get_y();

			switch (pacDir)
			{
			case MODE_UP:
				targetX = pacX;
				targetY = pacY - INKY_TARGET_OFFSET;
				break;
			case MODE_DOWN:
				targetX = pacX;
				targetY = pacY + INKY_TARGET_OFFSET;
				break;
			case MODE_LEFT:
				targetX = pacX - INKY_TARGET_OFFSET;
				targetY = pacY;
				break;
			case MODE_RIGHT:
				targetX = pacX + INKY_TARGET_OFFSET;
				targetY = pacY;
				break;
			}

			targetX += targetX - blinkX;
			targetY += targetY - blinkY;
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

Inky::~Inky()
{
	normalTexture = NULL;
	scaredTexture = NULL;	blinky = NULL;
	map = NULL;
}
