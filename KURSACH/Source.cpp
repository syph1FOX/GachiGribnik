#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "loadTextureFromFile.h"
#include "DeInit.h"
#include "Init.h"
#include "game.h"
#include "zastavka.h"
#include <SDL_ttf.h>
#include "GiveFont.h"

/*
* ������� ����. � ������ ������ ������ �� ��������� ����� ���������� �����, ��� ���������, ��� � �����������. 
�����, �������� ���������, �������� �����. 
�� ������ ��� ����� ������ ������������ ���������� �����: 
����� � 10, �����������, ������������ � 8, ������� � 5, �������� � 2, �������, ������� � -10. 
��� ��������� � ������� ���� ����������� ������ ���� �������������, � ��������� ���� ����������. 
� �������� ������� ����������������� ����� ������ �����������. �� ��� ���� ��������� 1,5 ������. 
�� ���������� ���� �� ����� ��������� ��������� ����� �����. 
10 ������ ����������� �������� � ����� � ��������� �� ����� �� ������� ������������.
*/


SDL_Renderer* ren = NULL;
SDL_Window* win = NULL;
int win_width = 1000, win_height = 800;



int main(int argc, char* argv[])
{ 
	Init(ren, win, win_width, win_height);
	zastavka(ren, win, win_width, win_height);

	DeInit(0, ren, win);
	return 0;
}
