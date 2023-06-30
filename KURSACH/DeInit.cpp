#include "DeInit.h"

void DeInit(int error, SDL_Renderer* ren, SDL_Window* win)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(error);
}
