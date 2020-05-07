#include "ghost.h"
#include "map.h"
#include "constants.h"
#include <vector>

Ghost::Ghost(Texture* t1, Texture* t2, Texture *t3, Map* m)
{
	normalTexture = t1;
	scaredTexture = t2;
	deadTexture = t3;
	map = m;
	frame = 0;
	dead = false;

	for (int i = 0; i < NUM_OF_DIRECTIONS; i++)
	{
		for (int j = 0; j < NUM_OF_FRAMES_PER_MODE; j++)
		{
			clips[i][j].x = j * CLIP_WIDTH;
			clips[i][j].y = i * CLIP_HEIGHT;
			clips[i][j].w = CLIP_WIDTH;
			clips[i][j].h = CLIP_HEIGHT;
		}

		deadClips[i].x = 0;
		deadClips[i].y = i * CLIP_HEIGHT;
		deadClips[i].w = CLIP_WIDTH;
		deadClips[i].h = CLIP_HEIGHT;
	}

	canPassFence = true;
}

void Ghost::move()
{
	std::vector<int> directions = available_directions();

	if ((directions.size() > 0) && (posX % TILE_WIDTH == 0) && (posY % TILE_HEIGHT == 0)) //direction can be changed
	{
		double distance = 99999;

		for (int i = 0; i < directions.size(); i++)
		{
			double newDistance;
			switch (directions[i])
			{
			case MODE_LEFT:
				newDistance = get_squared_distance(mapX - 1, mapY);
				if (newDistance < distance)
				{
					distance = newDistance;
					direction = MODE_LEFT;
				}
				break;
			case MODE_RIGHT:
				newDistance = get_squared_distance(mapX + 1, mapY);
				if (newDistance < distance)
				{
					distance = newDistance;
					direction = MODE_RIGHT;
				}
				break;
			case MODE_DOWN:
				newDistance = get_squared_distance(mapX, mapY + 1);
				if (newDistance < distance)
				{
					distance = newDistance;
					direction = MODE_DOWN;
				}
				break;
			case MODE_UP:
				newDistance = get_squared_distance(mapX, mapY - 1);
				if (newDistance < distance)
				{
					distance = newDistance;
					direction = MODE_UP;
				}
				break;
			}
		}
	}

	switch (direction)
	{
	case MODE_LEFT:
		posX -= GHOST_VEL;
		break;
	case MODE_RIGHT:
		posX += GHOST_VEL;
		break;
	case MODE_UP:
		posY -= GHOST_VEL;
		break;
	case MODE_DOWN:
		posY += GHOST_VEL;
		break;
	}

	if (posX % TILE_WIDTH == 0)
	{
		mapX = posX / TILE_WIDTH;
	}
	if (posY % TILE_HEIGHT == 0)
	{
		mapY = posY / TILE_HEIGHT;
	}

	map->set_ghost_loc(ghostId, mapX, mapY);
	
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

	if ((mapX == map->get_pacman_x()) && (mapY == map->get_pacman_y())
			&& map->in_chase_mode())
	{
		dead = true;
		deathTime = SDL_GetTicks();
	}
/*
	if (dead && (SDL_GetTicks() - deathTime >= GHOST_DEATH_DURATION))
	{
		dead = false;
	}*/
}

double Ghost::get_squared_distance(int x, int y)
{
	return ((targetX - x) * (targetX - x)) + ((targetY - y) * (targetY - y));
}

void Ghost::render()
{
	SDL_Rect scaleRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};

	if (dead)
	{
		deadTexture->render(posX, posY, &deadClips[direction], &scaleRect);	
	}
	else if (!map->in_chase_mode())
	{
		normalTexture->render(posX, posY, &clips[direction][frame / ANIMATION_SLOW], &scaleRect);
	}
	else
	{
		scaredTexture->render(posX, posY, &clips[direction][frame / ANIMATION_SLOW], &scaleRect);
	}

	frame++;
	if (frame / ANIMATION_SLOW >= NUM_OF_FRAMES_PER_MODE)
	{
		frame = 0;
	}
}

std::vector<int> Ghost::available_directions()
{
	std::vector<int> v;

	if ((direction != MODE_LEFT) && ((map->is_moveable_tile(mapX + 1, mapY)) 
									|| ((canPassFence && map->get_tile_state(mapX + 1, mapY) == FENCE))))
	{
		v.push_back(MODE_RIGHT);
	}

	if ((direction != MODE_RIGHT) && ((map->is_moveable_tile(mapX - 1, mapY))
									|| ((canPassFence && map->get_tile_state(mapX - 1, mapY) == FENCE))))
	{
		v.push_back(MODE_LEFT);
	}

	if ((direction != MODE_DOWN) && ((map->is_moveable_tile(mapX, mapY - 1))
									|| ((canPassFence && map->get_tile_state(mapX, mapY - 1) == FENCE))))
	{
		v.push_back(MODE_UP);
	}

	if ((direction != MODE_UP) && ((map->is_moveable_tile(mapX, mapY + 1))
									|| ((canPassFence && map->get_tile_state(mapX, mapY + 1) == FENCE))))
	{
		v.push_back(MODE_DOWN);
	}
	
	return v;
}

bool Ghost::is_in_house()
{
	if ((mapX >= GHOST_HOUSE_STARTX) && (mapX <= GHOST_HOUSE_ENDX)
			&& (mapY >= GHOST_HOUSE_STARTY) && (mapY <= GHOST_HOUSE_ENDY))
	{
		return true;
	}
	else
	{
		return false;
	}
}
