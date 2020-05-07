#ifndef INKY_H__
#define INKY_H__

#include "ghost.h"
#include "blinky.h"

class Inky : public Ghost
{
public:
	Inky(Texture*, Texture*, Texture*, Map*, Blinky*);
	~Inky();

	void set_target();
private:
	Blinky* blinky;
};

#endif