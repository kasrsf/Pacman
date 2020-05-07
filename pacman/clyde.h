#ifndef CLYDE_H__
#define CLYDE_H__

#include "ghost.h"

class Clyde : public Ghost
{
public:
	Clyde(Texture*, Texture*, Texture*, Map*);
	~Clyde();

	void set_target();
};

#endif