#include "Init.h"
#include "DeInit.h"

void Init(SDL_Renderer* &ren, SDL_Window*& win, int win_width, int win_height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)//Начало, инициализируем говно
	{
		printf("couldn't init SDL! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, ren, win);
	}
	int res;
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) == 0)//Начало, инициализируем говно
	{
		printf("couldn't init IMG! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, ren, win);
	}
	if (res & IMG_INIT_PNG) printf("Initialised PNG library\n"); else printf("Couldn't initialised PNG library\n");
	if (res & IMG_INIT_PNG) printf("Initialised JPG library\n"); else printf("Couldn't initialised JPG library\n");

	win = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN );//Создаём окно параметры: 1,2 - точка верхнего угла(В нашем случае создаём по центру), 3,4 - ширина, длина, показываем окно и даём возможность изменять размер.

	if (win == NULL)
	{
		printf("couldn't create Window! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, ren, win);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);//Создаём рисовальщика(Привязан к окну), Последний параметр - ускоритель

	if (ren == NULL)
	{
		printf("couldn't create Renderer! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, ren, win);
	}
	if (TTF_Init())
	{
		printf("couldn't init SDL_TTF! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, ren, win);
	}
}
