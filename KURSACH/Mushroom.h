#pragma once
#include <SDL.h>
#include "GameMatrix.h"
class Mushroom
{ 
	int size = 50;
	SDL_Texture* texture;
	int points;
public:
	SDL_Rect mushroom_rect;
	int time = 6000;
	int type;
	struct coords
	{
		int x;
		int y;
	} c;
	Mushroom();
	Mushroom(int type, SDL_Renderer* ren, GameMatrix& m);
	Mushroom(Mushroom& another);
	void DestroyMushroom(GameMatrix& m);
	~Mushroom();
	SDL_Texture* GetTexture();
	int GetPoints();
	void CreateMushroom(GameMatrix& m);
};

