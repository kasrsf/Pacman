#ifndef GHOST_MAN__H
#define GHOST_MAN__H

#include "ghost.h"
#include "blinky.h"
#include "clyde.h"
#include "pinky.h"
#include "inky.h"
#include "texture.h"

class GhostManager
{
public:
	GhostManager(Map*);
	~GhostManager();

	bool load_textures();

	void move();
	void render();

	void update_targets();
private:
	Map* map;

	Blinky* bl;
	Clyde* cl;
	Pinky* pi;
	Inky* in;

	Texture blinkyTexture, clydeTexture, pinkyTexture, inkyTexture, scaredTexture, deadTexture;
};

#endif