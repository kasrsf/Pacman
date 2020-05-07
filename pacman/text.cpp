#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "text.h"
#include "constants.h"

Text::Text(int f, int size, int color, std::string t)
{
	switch (f)
	{
	case LAZY_FONT:
		font = TTF_OpenFont("./textures/lazy.ttf", size);
		if (font == NULL)
		{
			printf("Failed to Open Font!\n");
			return;
		}
		break;
	}

	set_color(color);

	text = t;

	if (!texture.load_from_rendered_text(text, font, textColor))
	{
		printf("Error Rendering Text!\n");
		return;
	}
}

void Text::set_color(int color)
{
	switch (color)
	{
	case WHITE_COLOR:
		textColor = {255, 255, 255};
		break;
	}
}

void Text::set_text(std::string t)
{
	if (!texture.load_from_rendered_text(t.c_str(), font, textColor))
	{
		printf("Error Rendering Text!\n");
		return;
	}
	text = t;
}

void Text::render()
{
	texture.render(SCORE_POS_X, SCORE_POS_Y);
}

Text::~Text()
{
	TTF_CloseFont(font);
	font = NULL;

	texture.free();
}