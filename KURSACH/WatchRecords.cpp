#define _CRT_SECURE_NO_WARNINGS
#include "WatchRecords.h"
#include "SaveRecords.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "loadTextureFromFile.h"
#include "GiveFont.h"
#include <string.h>

void WatchRecords(SDL_Renderer * ren, int& win_width, int& win_height)
{
	TTF_Font* text_font = TTF_OpenFont("fonts/impact.ttf", 50);
	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("textures/background.png", &back_rect, ren);

	char filename[12] = "Records.bin";
	char stringrecord[30];

	bool on = true;

	SDL_Event ev;

	FILE* f = fopen(filename, "rb");
	if (!f)
	{
		std::cout << "No records" << std::endl;
		return;
	}
	int playercount,i;
	if (!fread(&playercount, sizeof(int), 1, f))
	{
		std::cout << "No records" << std::endl;
		return;
	}

	Record* recs = new Record[playercount];
	fread(recs, sizeof(Record), playercount, f);
	fclose(f);

	std::cout<< "WatchRecords\n" << playercount << " players" << std::endl;
	for (i = 0; i < playercount; i++)
		std::cout << i + 1 << " " << recs[i].nick << " : " << recs[i].score << std::endl;
	
	char top10[7] = "TOP 10";
	SDL_Surface* top10_surf = TTF_RenderText_Blended(text_font, top10, { 0, 0, 0, 0 });
	SDL_Texture* top10_text = SDL_CreateTextureFromSurface(ren, top10_surf);
	SDL_Rect top10_rect = { 400, 0, 200, 100 };

	SDL_Surface* player_surface = NULL;
	SDL_Texture* player_texture = NULL;
	SDL_Rect player_rect = { 100, 0, 0, 100 };


	while (on)
	{
		SDL_RenderClear(ren);

		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				exit(0);
			case SDL_KEYDOWN:
				if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					exit(0);
				else
					on = false;
				break;
			case SDL_WINDOWEVENT:
				if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					win_width = ev.window.data1;
					win_height = ev.window.data2;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if ((ev.button.button == SDL_BUTTON_LEFT) || (ev.button.button == SDL_BUTTON_RIGHT))
					on = false;
				break;
			}
		}

		SDL_RenderCopy(ren, back_tex, NULL, &back_rect);
		SDL_RenderCopy(ren, top10_text, NULL, &top10_rect);

		for (i = 0; i < playercount && i < 10; i++)
		{
			player_rect.y = 150 + i * 100;
			player_rect.w = 100 + (int)(strlen(recs[i].nick) / 2) * 70;
			sprintf(stringrecord, "%s  :  %d", recs[i].nick, recs[i].score);
			player_surface = TTF_RenderText_Blended(text_font, stringrecord, { 0, 0, 0, 0 });
			player_texture = SDL_CreateTextureFromSurface(ren, player_surface);
			SDL_RenderCopy(ren, player_texture, NULL, &player_rect);
		}
		
		SDL_RenderPresent(ren);
		SDL_Delay(20);
	}
	
	SDL_DestroyTexture(top10_text);
	SDL_DestroyTexture(player_texture);
	SDL_FreeSurface(player_surface);
	TTF_CloseFont(text_font);
	SDL_DestroyTexture(back_tex);
}