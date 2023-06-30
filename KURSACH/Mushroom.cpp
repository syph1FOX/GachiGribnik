#pragma once
#include "Mushroom.h"
#include <SDL.h>
#include "loadTextureFromFile.h"

Mushroom::Mushroom() {}

Mushroom::Mushroom(int type, SDL_Renderer* ren, GameMatrix& m)
{
	this->type = type;
	switch (type)
	{
	case 0:
		points = 2;
		texture = loadTextureFromFile("textures/mushroom2.png", &mushroom_rect, ren);
		break;
	case 1:
		points = -10;
		texture = loadTextureFromFile("textures/mushroom1.png", &mushroom_rect, ren);
		break;
	case 2:
		points = 10;
		texture = loadTextureFromFile("textures/god.png", &mushroom_rect, ren);
		break;
	case 3:
		points = 10;
		texture = loadTextureFromFile("textures/van.png", &mushroom_rect, ren);
		break;
	case 4:
		points = 8;
		texture = loadTextureFromFile("textures/svidetel.png", &mushroom_rect, ren);
		break;
	case 5:
		points = 5;
		texture = loadTextureFromFile("textures/jotaro.png", &mushroom_rect, ren);
		break;
	case 6:
		points = -10;
		texture = loadTextureFromFile("textures/toxic_shock.png", &mushroom_rect, ren);
		break;
	}
	Mushroom::CreateMushroom(m);
}
void Mushroom::DestroyMushroom(GameMatrix& m)
{
	m.matrix[c.x][c.y] = false;
	SDL_DestroyTexture(texture);
}
Mushroom ::~Mushroom()
{

}
Mushroom::Mushroom(Mushroom& another)
{
	this->type = another.type;
	this->points = another.points;
	texture = another.GetTexture();
	mushroom_rect = another.mushroom_rect;
	this->c.x = another.c.x;
	this->c.y = another.c.y;
}
SDL_Texture* Mushroom::GetTexture()
{
	return texture;
}
int Mushroom::GetPoints()
{
	return points;
}
void Mushroom::CreateMushroom(GameMatrix& m)
{
	do
	{
		c.x = rand() % 20;
		c.y = rand() % 16;
	} while (m.matrix[c.x][c.y]);
	m.matrix[c.x][c.y] = 1;
	mushroom_rect = { c.x * 50, c.y * 50, size, size };
}