#include "pacman.h"
#include "constants.h"
#include <SDL2/SDL.h>

Pacman::Pacman(Map* m)
{
	if (!load())
	{
		printf("Failed to load pacman texture!\n");
		return;
	}

	posX = PACMAN_STARTX;
	posY = PACMAN_STARTY;

	mapX = posX / TILE_WIDTH;
	mapY = posY / TILE_HEIGHT;

	currMode = MODE_RIGHT;
	newMode = currMode;
	modeChanged = false;
	frame = 0;
	halt = 0;

	score = 0;

	map = m;
	map->set_pacman_x(mapX);
	map->set_pacman_y(mapY);

	inChaseMode = false;
}

bool Pacman::load()
{
	if (!texture.load_from_file("./textures/pacman.png"))
	{
		return false;
	}

	for (int i = 0; i < NUM_OF_MODES; i++)
	{
		for (int j = 0; j < NUM_OF_FRAMES_PER_MODE; j++)
		{
			clips[i][j].x = j * CLIP_WIDTH;
			clips[i][j].y = i * CLIP_HEIGHT;
			clips[i][j].w = CLIP_WIDTH;
			clips[i][j].h = CLIP_HEIGHT;
		}
	}

	return true;
}

void Pacman::handle_event(SDL_Event &e)
{
	// if a key was pressed
	if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		switch ( e.key.keysym.sym )
		{
			case SDLK_RIGHT: 
				modeChanged = (currMode == MODE_RIGHT)? false : true;
				newMode = MODE_RIGHT; 
				break;
			case SDLK_LEFT: 
				modeChanged = (currMode == MODE_LEFT)? false : true;
				newMode = MODE_LEFT;
				break;
			case SDLK_DOWN:
				modeChanged = (currMode == MODE_DOWN)? false : true;
				newMode = MODE_DOWN;
				break;
			case SDLK_UP:
				modeChanged = (currMode == MODE_UP)? false : true;
				newMode = MODE_UP;
				break;	
		}
	}
}

void Pacman::move()
{
	bool changeMode = false;
	// first check if new mode is doable

	if (halt == 0 && !dead)
	{
		if (modeChanged)
		{
			switch (newMode)
			{
			case MODE_LEFT:
				posX -= PAC_VEL;
				if ((posY % TILE_HEIGHT == 0) && (map->is_moveable_tile(mapX - 1, mapY)))
				{
					changeMode = true;
					currMode = newMode;
				}
				else
				{
					posX += PAC_VEL;
				}
				break;
			case MODE_RIGHT:
				posX += PAC_VEL;
				if ((posY % TILE_HEIGHT == 0) && (map->is_moveable_tile(mapX + 1, mapY)))
				{
					changeMode = true;
					currMode = newMode;
				}
				else
				{
					posX -= PAC_VEL;
				}
				break;
			case MODE_DOWN:
				posY += PAC_VEL;
				if ((posX % TILE_WIDTH == 0) && (map->is_moveable_tile(mapX, mapY + 1)))
				{
					changeMode = true;
					currMode = newMode;
				}
				else
				{
					posY -= PAC_VEL;
				}
				break;
			case MODE_UP:
				posY -= PAC_VEL;
				if ((posX % TILE_WIDTH == 0) && (map->is_moveable_tile(mapX, mapY - 1)))
				{
					changeMode = true;
					currMode = newMode;
				}
				else
				{
					posY += PAC_VEL;
				}
				break;	
			}
		}

		if (!changeMode)
		{				
			switch (currMode)
			{
			case MODE_LEFT:
				posX -= PAC_VEL;
				if ((posY % TILE_HEIGHT != 0) || (!map->is_moveable_tile(mapX - 1, mapY)))
				{
					posX += PAC_VEL;
				}
				break;
			case MODE_RIGHT:
				posX += PAC_VEL;

				if ((posY % TILE_HEIGHT != 0) || (!map->is_moveable_tile(mapX + 1, mapY)))
				{
					posX -= PAC_VEL;
				}
				break;
			case MODE_DOWN:
				posY += PAC_VEL;
				if ((posX % TILE_WIDTH != 0) || (!map->is_moveable_tile(mapX, mapY + 1)))
				{
					posY -= PAC_VEL;
				}
				break;
			case MODE_UP:
				posY -= PAC_VEL;
				if ((posX % TILE_WIDTH != 0) || (!map->is_moveable_tile(mapX, mapY - 1)))
				{
					posY += PAC_VEL;
				}
				break;	
			}
		}
		else
		{
			map->set_pacman_dir(currMode);
		}

		if (posX % TILE_WIDTH == 0)
		{
			mapX = posX / TILE_WIDTH;
			map->set_pacman_x(mapX);
		}

		if (posY % TILE_HEIGHT == 0)
		{
			mapY = posY / TILE_HEIGHT;
			map->set_pacman_y(mapY);
		}

		if ((mapX == PORTAL_LEFT_X) && (mapY == PORTAL_LEFT_Y))
		{
			posX = (PORTAL_RIGHT_X - 1) * TILE_WIDTH;
			posY = PORTAL_RIGHT_Y * TILE_HEIGHT;

			mapX = PORTAL_RIGHT_X - 1;
			mapY = PORTAL_RIGHT_Y;
		}

		if ((mapX == PORTAL_RIGHT_X) && (mapY == PORTAL_RIGHT_Y))
		{
			posX = (PORTAL_LEFT_X + 1) * TILE_WIDTH;
			posY = PORTAL_LEFT_Y * TILE_HEIGHT;

			mapX = PORTAL_LEFT_X + 1;
			mapY = PORTAL_LEFT_Y;
		}

		int tileState = map->get_tile_state(mapX, mapY);

		switch (tileState)
		{
		case SMALL_DOT:
			score += SMALL_DOT_POINT;
			halt = SMALL_DOT_HALT;
			break;
		case LARGE_DOT:
			score += LARGE_DOT_POINT;
			halt = LARGE_DOT_HALT;

			inChaseMode = true;
			map->init_chase_mode();
			break;
		case GHOST:
			if (inChaseMode)
			{
				score += GHOST_POINT;
			}
			else
			{
				dead = true;
				deathTimer = NUM_OF_FRAMES_PER_MODE;
				frame = 0;
				currMode = MODE_DYING;
			}
			break;
		}
	}
	else if (dead)
	{
		if (deathTimer <= 0)
		{
			dead = false;
			currMode = MODE_RIGHT;

			posX = PACMAN_STARTX;
			posY = PACMAN_STARTY;
		}

		deathTimer--;
	}
	else
	{
		halt--;
	}
}

void Pacman::render()
{
	SDL_Rect scaleRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};

	if (!dead)
	{
		texture.render(posX, posY, &clips[currMode][frame / ANIMATION_SLOW], &scaleRect);
	}
	else
	{
		texture.render(posX, posY, &clips[currMode][frame / (ANIMATION_SLOW * 4)], &scaleRect);
	}


	frame++;
	if (frame / ANIMATION_SLOW >= NUM_OF_FRAMES_PER_MODE)
	{
		frame = 0;
	}
}

int Pacman::get_score()
{
	return score;
}

Pacman::~Pacman()
{
	texture.free();	
}
