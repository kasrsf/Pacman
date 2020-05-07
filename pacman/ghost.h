#ifndef GHOST_H__
#define GHOST_H__

#include "texture.h"
#include "map.h"
#include <vector>

class Ghost
{
public:
	static const int NUM_OF_FRAMES_PER_MODE = 4;

	static const int NUM_OF_DIRECTIONS = 4;

	static const int ANIMATION_SLOW = 5;

	static const int GHOST_VEL = 2;

	Ghost(Texture*, Texture*, Texture*, Map*);
	virtual ~Ghost() {};

	void move();
	void die();
	virtual void set_target() = 0;

	double get_squared_distance(int x, int y);

	void render();

	std::vector<int> available_directions();

	bool is_in_house();
protected:
	int posX, posY;
	int mapX, mapY;
	int targetX, targetY;
	int direction;

	int ghostId;

	int frame;

	bool canPassFence;

	bool dead;
	Uint32 deathTime;

	Texture *normalTexture, *scaredTexture, *deadTexture;
	SDL_Rect clips[NUM_OF_DIRECTIONS][NUM_OF_FRAMES_PER_MODE];
	SDL_Rect deadClips[NUM_OF_DIRECTIONS];

	Map* map;
};

#endif