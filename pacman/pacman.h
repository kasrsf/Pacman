#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include "texture.h"
#include "constants.h"
#include "map.h"

class Pacman
{
public: 
	static const int NUM_OF_FRAMES_PER_MODE = 3;

	static const int PAC_VEL = 2;

	static const int ANIMATION_SLOW = 4;

	static const int SMALL_DOT_POINT = 10;
	static const int LARGE_DOT_POINT = 50;
	static const int GHOST_POINT = 200;	

	static const int SMALL_DOT_HALT = 0;
	static const int LARGE_DOT_HALT = 0;

	Pacman(Map*);
	~Pacman();

	bool load();

	void handle_event(SDL_Event &e);
	
	void move();

	void render();

	int get_score();
private:
	int frame;
	int newMode, currMode;
	bool modeChanged;
	
	int posX, posY;

	int mapX, mapY;

	int score;

	bool inChaseMode;

	Texture texture;
	SDL_Rect clips[NUM_OF_MODES][NUM_OF_FRAMES_PER_MODE];

	int halt;

	bool dead;
	int deathTimer;

	Map* map;
};

#endif
