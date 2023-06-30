#include "GameOver.h"
#include "loadTextureFromFile.h"
#include <SDL.h>
#include "GiveFont.h"
#include <iostream>
#include <cstring>

int GameOver(SDL_Renderer* ren, int score, char* end)
{
	bool gameOver = true;
	SDL_Event ev;

	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("textures/background.png", &back_rect, ren);

	SDL_Rect Over;
	SDL_Texture* over_tex = GiveFont("fonts/impact.ttf", 130, "Game over", Over, ren, 200, 200);

	char SCORE[50];
	sprintf_s(SCORE, "Score: %i", score);
	SDL_Rect Score;
	SDL_Texture* Score_tex = GiveFont("fonts/impact.ttf", 80, SCORE, Score, ren, 350, 370);

	SDL_Rect reason;
	SDL_Texture* Reason_tex;
	if(!strcmp(end, "Out of time!"))
		 Reason_tex = GiveFont("fonts/impact.ttf", 80, end, reason, ren, 300 , 480);
	else  Reason_tex = GiveFont("fonts/impact.ttf", 80, "You nazhralsya paganok!", reason, ren, 100, 480);

	while (gameOver)
	{
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				exit(1);
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					exit(1);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_DestroyTexture(back_tex);
				SDL_DestroyTexture(over_tex);
				SDL_DestroyTexture(Score_tex);
				SDL_DestroyTexture(Reason_tex);
				return 0;
			}
		}
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, back_tex, NULL, &back_rect);
		SDL_RenderCopy(ren, over_tex, NULL, &Over);
		SDL_RenderCopy(ren, Score_tex, NULL, &Score);
		SDL_RenderCopy(ren, Reason_tex, NULL, &reason);
		SDL_RenderPresent(ren);
	}
}
