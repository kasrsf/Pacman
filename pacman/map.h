#ifndef MAP__H__
#define MAP__H__

#include "texture.h"
#include "constants.h"

class Map
{
public:
	Map();
	~Map();

	bool load();
	bool set_tiles();

	bool is_moveable_tile(int, int);
	int get_tile_state(int, int);

	void set_pacman_x(int);
	void set_pacman_y(int);

	int get_pacman_x();
	int get_pacman_y();

	void set_pacman_dir(int);
	int get_pacman_dir();

	void render();

	int get_start_time();

	void init_chase_mode();
	bool in_chase_mode();
	void end_chase_mode();
	Uint32 get_chase_start_time();

	void set_ghost_loc(int, int, int);
private:
	Texture wallTexture, dotsTexture, fenceTexture;
	SDL_Rect dotClips[2];

	int pacLocX, pacLocY, pacDir;

	int ghostLoc[4][2];

	int mapArray[TILES_PER_ROW][TILES_PER_COL];

	Uint32 startTime, chaseStartTime;
	bool inChaseMode;
};

#endif