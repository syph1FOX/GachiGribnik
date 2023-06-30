#include "GiveFont.h"

SDL_Texture* GiveFont(const char* filename, int size, const char* text, SDL_Rect& rect, SDL_Renderer* ren, int x, int y)
{
	TTF_Font* font = TTF_OpenFont(filename, size);

	SDL_Surface* str_surf = TTF_RenderText_Blended(font, text, { 0,0,0,255 });
	rect = { x,y,str_surf->w, str_surf->h };

	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, str_surf);
	SDL_FreeSurface(str_surf);
	return texture;
}