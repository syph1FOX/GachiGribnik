#include "Reference.h"

void Reference(SDL_Renderer* ren, int& win_width, int& win_height)
{
	bool on = true;

	SDL_Event ev;

	int mouseX, mouseY;

	TTF_Font* RefFont = TTF_OpenFont("fonts/impact.ttf", 50);

	char strRef[80] = "You need to pick up mushrooms";
	SDL_Surface* RefSurf = TTF_RenderText_Blended(RefFont, strRef, { 0, 0, 0, 0 });
	SDL_Texture* RefTex = SDL_CreateTextureFromSurface(ren, RefSurf);
	SDL_Rect RefRect = { 50, 50, 900, 80 };

	char strRef2[80] = "and reach the highest score!";
	SDL_Surface* Ref2Surf = TTF_RenderText_Blended(RefFont, strRef2, { 0, 0, 0, 0 });
	SDL_Texture* Ref2Tex = SDL_CreateTextureFromSurface(ren, Ref2Surf);
	SDL_Rect Ref2Rect = { 50, 150, 900, 80 };

	char strRef3[80] = "Red and green are bad mushrooms, other are good";
	SDL_Surface* Ref3Surf = TTF_RenderText_Blended(RefFont, strRef3, { 0, 0, 0, 0 });
	SDL_Texture* Ref3Tex = SDL_CreateTextureFromSurface(ren, Ref3Surf);
	SDL_Rect Ref3Rect = { 50, 350, 900, 80 };

	char strRef4[80] = "If you pick up 3 bad mushrooms, you will lose";
	SDL_Surface* Ref4Surf = TTF_RenderText_Blended(RefFont, strRef4, { 0, 0, 0, 0 });
	SDL_Texture* Ref4Tex = SDL_CreateTextureFromSurface(ren, Ref4Surf);
	SDL_Rect Ref4Rect = { 50, 500, 900, 80 };

	char strRef5[80] = "Use your arrow keys to move your gribnik";
	SDL_Surface* Ref5Surf = TTF_RenderText_Blended(RefFont, strRef5, { 0, 0, 0, 0 });
	SDL_Texture* Ref5Tex = SDL_CreateTextureFromSurface(ren, Ref5Surf);
	SDL_Rect Ref5Rect = { 50, 650, 900, 80 };


	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("textures/background.png", &back_rect, ren);
	

	while (on)
	{
		SDL_RenderClear(ren);

		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				exit(1);
			case SDL_KEYDOWN:
				if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					exit(1);
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
				if ((ev.button.button == SDL_BUTTON_LEFT)|| (ev.button.button == SDL_BUTTON_RIGHT))
				{
					on = false;
				}
				break;
			}
		}

		SDL_RenderCopy(ren, back_tex, NULL, &back_rect);
		SDL_RenderCopy(ren, RefTex, nullptr, &RefRect);
		SDL_RenderCopy(ren, Ref2Tex, nullptr, &Ref2Rect);
		SDL_RenderCopy(ren, Ref3Tex, nullptr, &Ref3Rect);
		SDL_RenderCopy(ren, Ref4Tex, nullptr, &Ref4Rect);
		SDL_RenderCopy(ren, Ref5Tex, nullptr, &Ref5Rect);

		SDL_RenderPresent(ren);
		SDL_Delay(20);
	}

	SDL_FreeSurface(RefSurf);
	SDL_FreeSurface(Ref2Surf);
	SDL_FreeSurface(Ref3Surf);
	SDL_FreeSurface(Ref4Surf);
	SDL_FreeSurface(Ref5Surf);

	SDL_DestroyTexture(RefTex);
	SDL_DestroyTexture(Ref2Tex);
	SDL_DestroyTexture(Ref3Tex);
	SDL_DestroyTexture(Ref4Tex);
	SDL_DestroyTexture(Ref5Tex);

	SDL_DestroyTexture(back_tex);

	TTF_CloseFont(RefFont);
}
