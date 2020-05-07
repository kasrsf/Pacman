#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
#include "globals.h"
#include "texture.h"

Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::load_from_file( std::string path )
{
	//deallocate prev texture
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	
	if (loadedSurface == NULL)
	{
		printf("Unable To Load Image. SDL Error: %s\n", IMG_GetError());
	}
	else
	{
		//SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable To Create Texture. SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
	return texture != NULL;
}

bool Texture::load_from_rendered_text(std::string text, TTF_Font *font, SDL_Color textColor)
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	if (textSurface == NULL)
	{
		printf("Unable to render text surface!\n");
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture == NULL)
	{
		printf("Unable to create texture!\n");
		return false;
	}

	width = textSurface->w;
	height = textSurface->h;

	SDL_FreeSurface(textSurface);

	return true;
}

void Texture::render( int x, int y, SDL_Rect* clip, SDL_Rect* scale)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (scale != NULL)
	{
		renderQuad.w = scale->w;
		renderQuad.h = scale->h;
	}
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

void Texture::free()
{
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		width = 0;
		height = 0;
	}
}

int Texture::get_width()
{
	return width;
}

int Texture::get_height()
{
	return height;
}