#ifndef PINKY_H__
#define PINKY_H__

#include "ghost.h"

class Pinky : public Ghost
{
public:
	Pinky(Texture*, Texture*, Texture*, Map*);
	~Pinky();

	void set_target();
};

#endif