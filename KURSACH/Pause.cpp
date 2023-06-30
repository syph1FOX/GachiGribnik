#include "Pause.h"
#include "loadTextureFromFile.h"
#include "game.h"
#include "GiveFont.h"
#include <SDL.h>
#include <SDL_image.h>

int Pause(SDL_Renderer* ren)
{
	bool userMenu = true;
	bool flag = false;
	SDL_Event ev;
	int mouse_x = 0, mouse_y = 0;

	SDL_Rect pause_txt_rects[2];
	SDL_Texture* pause_txt[2];
	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
		case 0:
			pause_txt[i] = GiveFont("fonts/impact.ttf", 80, "Continue", pause_txt_rects[i], ren, 0, 0);
			pause_txt_rects[i].x = 360;
			break;
		case 1:
			pause_txt[i] = GiveFont("fonts/impact.ttf", 80, "Return to menu", pause_txt_rects[i], ren, 0, 0);
			pause_txt_rects[i].x = 250;
			break;
		}
		pause_txt_rects[i].y = 400 * i + 100 * (i + 1) + 10;
	}


	SDL_Rect a[2];
	for (int i = 0; i < 2; i++)
	{
		a[i].h = 100;
		a[i].w = 500;
		a[i].x = 250;
		a[i].y = 400 * i + 100 * (i + 1);
	}
	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("textures/pause.png", &back_rect, ren);
	back_rect.h = 800;
	back_rect.w = 1000;
	while (userMenu)
	{
		flag = false;
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				exit(1);
			case SDL_MOUSEBUTTONDOWN:
				if (ev.button.button = SDL_BUTTON_LEFT)
					flag = true;
				break;
			case SDL_KEYDOWN:
				if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					exit(1);
				else if (ev.key.keysym.scancode == SDL_SCANCODE_F9)
				{
					for (int i = 0; i < 2; i++)
						SDL_DestroyTexture(pause_txt[i]);
					SDL_DestroyTexture(back_tex);
					return 0;
				}
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
		for (int i = 0; i < 2; i++)
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
						SDL_DestroyTexture(back_tex);
						for (int i = 0; i < 2; i++)
							SDL_DestroyTexture(pause_txt[i]);
						SDL_DestroyTexture(back_tex);
						return 0;
					case 1:
						SDL_DestroyTexture(back_tex);
						for (int i = 0; i < 2; i++)
							SDL_DestroyTexture(pause_txt[i]);
						SDL_DestroyTexture(back_tex);
						return 1;

					}
				}
			}
			else
				SDL_RenderFillRect(ren, &a[i]);

			SDL_RenderCopy(ren, pause_txt[i], NULL, &pause_txt_rects[i]);
		}
		SDL_RenderPresent(ren);
	}
    return 0;
}
