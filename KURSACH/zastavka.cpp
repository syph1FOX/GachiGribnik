#include "zastavka.h"
#include "loadTextureFromFile.h"
#include<SDL.h>
#include "Menu.h"
void zastavka(SDL_Renderer* ren, SDL_Window* win, int& win_width, int& win_height)
{
	bool zastavka = true;
	SDL_Event ev;

	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("textures/zastavkax.png", &back_rect, ren);

	while (zastavka)
	{
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
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					exit(1);
				default:
					SDL_DestroyTexture(back_tex);
					Menu(ren, win, win_width, win_height);
				}
			case SDL_MOUSEBUTTONDOWN:
				SDL_DestroyTexture(back_tex);
				Menu(ren, win, win_width, win_height);
			}
		}
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, back_tex, NULL, &back_rect);
		SDL_RenderPresent(ren);
	}
}
