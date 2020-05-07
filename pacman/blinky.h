#ifndef BLINKY_H__
#define BLINKY_H__

#include "ghost.h"

class Blinky : public Ghost
{
public:
	Blinky(Texture*, Texture*, Texture*, Map*);
	~Blinky();

	void set_target();

	int get_x();
	int get_y();
};

#endif