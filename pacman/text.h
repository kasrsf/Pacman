#ifndef TEXT__H
#define TEXT__H

#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text
{
public:
	Text(int, int, int, std::string);
	~Text();

	void set_color(int);
	void set_text(std::string);

	void render();
private:
	Texture texture;
	TTF_Font *font;

	std::string text;
	SDL_Color textColor;
};

#endif