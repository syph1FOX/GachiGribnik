#pragma once
#include<iostream>
#include<SDL_image.h>
SDL_Texture* loadTextureFromFile(const char* filename, SDL_Rect* rect, SDL_Renderer* ren);