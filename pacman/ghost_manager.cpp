#include <SDL2/SDL.h>
#include "ghost_manager.h"
#include "blinky.h"
#include "clyde.h"
#include "pinky.h"
#include "inky.h"
#include "texture.h"

GhostManager::GhostManager(Map* m)
{
	map = m;

	if (!load_textures())
	{
		printf("Unable to load Ghost Textures!\n");
		return;
	}

	bl = new Blinky(&blinkyTexture, &scaredTexture, &deadTexture, map);
	cl = new Clyde(&clydeTexture, &scaredTexture, &deadTexture, map);
	pi = new Pinky(&pinkyTexture, &scaredTexture, &deadTexture, map);
	in = new Inky(&inkyTexture, &scaredTexture, &deadTexture , map, bl);
}

bool GhostManager::load_textures()
{
	if (!blinkyTexture.load_from_file("./textures/blinky.png"))
	{
		return false;
	}

	if (!clydeTexture.load_from_file("./textures/clyde.png"))
	{
		return false;
	}

	if (!pinkyTexture.load_from_file("./textures/pinky.png"))
	{
		return false;
	}

	if (!inkyTexture.load_from_file("./textures/inky.png"))
	{
		return false;
	}

	if (!scaredTexture.load_from_file("./textures/scatter.png"))
	{
		return false;
	}

	if (!deadTexture.load_from_file("./textures/dead.png"))
	{
		return false;
	}

	return true;
}

void GhostManager::move()
{
	bl->move();
	cl->move();
	pi->move();
	in->move();
}

void GhostManager::render()
{
	bl->render();	
	cl->render();
	pi->render();
	in->render();
}

void GhostManager::update_targets()
{
	if (SDL_GetTicks() - map->get_chase_start_time() >= CHASE_MODE_DURATION)
	{
		map->end_chase_mode();
	}

	bl->set_target();
	cl->set_target();
	pi->set_target();
	in->set_target();
}

GhostManager::~GhostManager()
{
	map = NULL;
	bl = NULL;
	cl = NULL;
	pi = NULL;
	in = NULL;

	blinkyTexture.free();
	clydeTexture.free();
	pinkyTexture.free();
	inkyTexture.free();
}