#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
SDL_Texture* GiveFont(const char* filename, int size, const char* text, SDL_Rect& rect, SDL_Renderer* ren, int x, int y);