#include "loadTextureFromFile.h"
#include "DeInit.h"

SDL_Texture* loadTextureFromFile(const char* filename, SDL_Rect* rect, SDL_Renderer* ren)
{
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == NULL)
	{
		printf("Didn't load image! %s", filename);
		system("pause");
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	if(surface!=NULL)
		*rect = { 0, 0, surface->w, surface->h };
	SDL_FreeSurface(surface);	
	return texture;
}
