#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include "funcs.h"
#include "globals.h"
#include "constants.h"
#include "pacman.h"
#include "text.h"
#include "map.h"
#include "ghost_manager.h"

int main( int argc, char* args[] )
{
	if (init() == false)
	{
		printf( "Could not initialize SDL!\n" );
	}
	else
	{
		bool quit = false;

		SDL_Event e;

		Map map;

		Pacman pacman(&map);

		GhostManager gm(&map);

		Text score(LAZY_FONT, SCORE_TEXT_SIZE, WHITE_COLOR, "Score = 0");

		while (!quit)
		{
			Uint32 startTicks = SDL_GetTicks();


			while ( SDL_PollEvent( &e ) != 0 )
			{
				if ( e.type == SDL_QUIT )
				{
					quit = true;
				}

				pacman.handle_event(e);
			}

			//clear screan
			SDL_SetRenderDrawColor( renderer, 0x0, 0x0, 0x0, 0x0 );
			SDL_RenderClear( renderer );

			pacman.move();
			gm.move();

			int pScore = pacman.get_score();

			std::stringstream text;
			text.str(" ");
			text << "Score: " << pScore;
			score.set_text(text.str().c_str());

			map.render();
			pacman.render();
			gm.render();
			score.render();
			//update screen
			SDL_RenderPresent( renderer );

			gm.update_targets();

			Uint32 frameTime = SDL_GetTicks() - startTicks;
			if (frameTime < SCREEN_TICKS_PER_FRAME)
			{
				// wait remaining time
				SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTime);
			}
		}
	}

	return 0;
}