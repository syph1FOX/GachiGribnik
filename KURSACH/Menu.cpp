#pragma once
#include <iostream>
#include <string>
#include "Menu.h"
#include "loadTextureFromFile.h"
#include "game.h"
#include "GiveFont.h"
#include "ChooseNick.h"
#include "Reference.h"
#include <fstream>
#include "WatchRecords.h"
#include <string.h>

void Menu(SDL_Renderer* ren, SDL_Window* win, int win_width, int win_height)
{
	char* str = new char [11];
	strcpy_s(str,11,ChooseNick(ren));

	bool userMenu = true;
	bool flag = false;
	SDL_Event ev;
	int mouse_x = 0, mouse_y = 0;

	SDL_Rect menu_txt_rects[5];
	SDL_Texture* menu_txt[5];
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			menu_txt[i] = GiveFont("fonts/impact.ttf", 80, "Start", menu_txt_rects[i], ren, 0, 0);
			menu_txt_rects[i].x = 420;
			break;
		case 1:
			menu_txt[i] = GiveFont("fonts/impact.ttf", 80, "Change player", menu_txt_rects[i], ren, 0, 0);
			menu_txt_rects[i].x = 265;
			break;
		case 2:
			menu_txt[i] = GiveFont("fonts/impact.ttf", 80, "Records", menu_txt_rects[i], ren, 0, 0);
			menu_txt_rects[i].x = 375;
			break;
		case 3:
			menu_txt[i] = GiveFont("fonts/impact.ttf", 80, "Reference", menu_txt_rects[i], ren, 0, 0);
			menu_txt_rects[i].x = 340;
			break;
		case 4:
			menu_txt[i] = GiveFont("fonts/impact.ttf", 80, "Exit", menu_txt_rects[i], ren, 0, 0);
			menu_txt_rects[i].x = 430;
			break;
		}
		menu_txt_rects[i].y = 100 * i + 50 * (i + 1) + 10;
	}


	SDL_Rect a[5];
	for (int i = 0; i < 5; i++)
	{
		a[i].h = 100;
		a[i].w = 500;
		a[i].x = 250;
		a[i].y = 100 * i + 50 * (i + 1);
	}
	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("textures/background.png", &back_rect, ren);
	while (userMenu)
	{
		flag = false;
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				exit(1);
			case SDL_WINDOWEVENT:
				if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					win_width = ev.window.data1;
					win_height = ev.window.data2;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (ev.button.button = SDL_BUTTON_LEFT)
					flag = true;
				break;
			case SDL_KEYDOWN:
				if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					exit(1);
			case SDL_MOUSEMOTION:
				mouse_x = ev.button.x;
				mouse_y = ev.button.y;
				break;
			}
		}

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, back_tex, NULL, &back_rect);
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		for (int i = 0; i < 5; i++)
		{
			if ((mouse_x<(a[i].x + 500) && mouse_x>a[i].x) && (mouse_y<(a[i].y + 100) && mouse_y>a[i].y))
			{
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
				SDL_RenderFillRect(ren, &a[i]);
				SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
				if (flag)
				{
					switch (i)
					{
					case 0:
						game(ren, win, win_width, win_height,str);
						break;
					case 1:
						strcpy_s(str, 11, ChooseNick(ren));
						break;
					case 2:
						WatchRecords(ren, win_width, win_height);
						break;
					case 3:
						Reference(ren,win_width,win_height);
						break;
					case 4:
						exit(0);

					}
				}
			}
			else
				SDL_RenderFillRect(ren, &a[i]);

			SDL_RenderCopy(ren, menu_txt[i], NULL, &menu_txt_rects[i]);
		}
		SDL_RenderPresent(ren);
	}
	SDL_DestroyTexture(back_tex);
	for (int i = 0; i < 5; i++)
		SDL_DestroyTexture(menu_txt[i]);
}