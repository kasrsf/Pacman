#include "map.h"
#include "constants.h"
#include <fstream>
#include <SDL2/SDL.h>

Map::Map()
{
	if (!load())
	{
		printf("Unable to load Map texture!\n");
		return;
	}

	if (!set_tiles())
	{
		printf("Unable to set tiles!\n");
		return;
	}

	pacLocX = 1;
	pacLocY = 1;
	pacDir = MODE_RIGHT;

	startTime = SDL_GetTicks();
}

bool Map::load()
{
	if (!wallTexture.load_from_file("./textures/brick.png"))
	{
		return false;
	}

	if (!dotsTexture.load_from_file("./textures/dot.png"))
	{
		return false;
	}

	if (!fenceTexture.load_from_file("./textures/fence.png"))
	{
		return false;
	}

	// clip large dot
	dotClips[0].x = 0;
	dotClips[0].y = 0;
	dotClips[0].w = CLIP_WIDTH;
	dotClips[0].h = CLIP_HEIGHT;

	// clip small dot
	dotClips[1].x = 30;
	dotClips[1].y = 0;
	dotClips[1].w = CLIP_WIDTH;
	dotClips[1].h = CLIP_HEIGHT;

	return true;
}

bool Map::set_tiles()
{
	int x = 0;
	int y = 0;

	std::fstream map("./textures/default.map");

	if (map == NULL)
	{
		return false;
	}

	for (int i = 0; i < NUM_OF_TILES; i++)
	{
		int tile_type = 0;

		map >> tile_type;

		if (map.fail())
		{
			printf("Error: Unexpected end of file!\n");
			return false;
		}
		if ((tile_type >= 0) && (tile_type < TILE_TYPES))
		{
			mapArray[x][y] = tile_type;
		}
		else
		{
			printf("Invalid Tile Type!\n");
			return false;
		}

		x++;
		if (x >= TILES_PER_ROW)
		{
			x = 0;
			y++;
		}
	}

	map.close();

	return true;
}

bool Map::is_moveable_tile(int x, int y)
{
	if (((x == PORTAL_LEFT_X) && (y == PORTAL_LEFT_Y))
		|| ((x == PORTAL_RIGHT_X) && (y == PORTAL_RIGHT_Y)))
		return true;
	
	return mapArray[x][y] < WALL; 
}

int Map::get_tile_state(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		if ((x == ghostLoc[i][0]) && (y == ghostLoc[i][1]))
		{
			return GHOST;
		}
	}

	int tile = mapArray[x][y];

	if ((tile == SMALL_DOT) || (tile == LARGE_DOT))
	{
		mapArray[x][y] = NOTHING;
	}

	return tile;
}

void Map::set_pacman_x(int x)
{
	pacLocX = x;
}

void Map::set_pacman_y(int y)
{
	pacLocY = y;
}

int Map::get_pacman_x()
{
	return pacLocX;
}

int Map::get_pacman_y()
{
	return pacLocY;
}

void Map::set_pacman_dir(int d)
{
	pacDir = d;
}

int Map::get_pacman_dir()
{
	return pacDir;
}

void Map::render()
{
	SDL_Rect scaleRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};

	for (int i = 0; i < TILES_PER_ROW; i++)
	{
		for (int j = 0; j < TILES_PER_COL; j++)
		{
			if (mapArray[i][j] == WALL)
			{
				wallTexture.render(i * TILE_WIDTH, j * TILE_HEIGHT, NULL, &scaleRect);
			}
			else if (mapArray[i][j] == SMALL_DOT)
			{
				dotsTexture.render(i * TILE_WIDTH, j * TILE_HEIGHT, &dotClips[1], &scaleRect);
			}
			else if (mapArray[i][j] == LARGE_DOT)
			{
				dotsTexture.render(i * TILE_WIDTH, j * TILE_HEIGHT, &dotClips[0], &scaleRect);
			}
			else if (mapArray[i][j] == FENCE)
			{
				fenceTexture.render(i * TILE_WIDTH, j * TILE_HEIGHT, NULL, &scaleRect);
			}
		}
	}
}

int Map::get_start_time()
{
	return startTime;
}

void Map::init_chase_mode()
{
	chaseStartTime = SDL_GetTicks();
	inChaseMode = true;
}

bool Map::in_chase_mode()
{
	return inChaseMode;
}

void Map::end_chase_mode()
{
	inChaseMode = false;
}

Uint32 Map::get_chase_start_time()
{
	return chaseStartTime;
}

void Map::set_ghost_loc(int ghostId, int x, int y)
{
	ghostLoc[ghostId][0] = x;
	ghostLoc[ghostId][1] = y;
}

Map::~Map()
{
	wallTexture.free();
	dotsTexture.free();
}