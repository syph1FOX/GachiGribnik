#include "ChooseNick.h"

char* ChooseNick(SDL_Renderer* ren)
{
	bool ChooseNicks = true;
	SDL_Event ev;

	char* nick = new char[11];
	char nickText[11];

	SDL_Color textColor = { 0,0,0 };
	TTF_Font* textFont = TTF_OpenFont("fonts/impact.ttf", 50);
	SDL_Surface* textSurface = NULL;
	SDL_Texture* textTexture = NULL;
	SDL_Rect textPosition = { 180, 370, 0, 0 };
	int lengthText = 0,i;
	char q[2];
	q[0] = ' ';
	q[1] = '\0';

	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("textures/background.png", &back_rect, ren);

	char str[50] = "Enter nickname";
	SDL_Rect StrRect;
	TTF_Font* StrFont = TTF_OpenFont("fonts/impact.ttf", 80);
	SDL_Surface* Str_surf = TTF_RenderText_Blended(StrFont, str, { 0,0,0,255 });
	StrRect = { 250,170,Str_surf->w, Str_surf->h };
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(ren, Str_surf);

	SDL_Rect a{ 150, 350, 700, 100 };

	while (ChooseNicks)
	{
		SDL_StartTextInput();
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				exit(1);
			else if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_RETURN:
					if (lengthText > 0)
					{
						*nick = '\0';
						SDL_DestroyTexture(textTexture);
						SDL_DestroyTexture(back_tex);
						SDL_DestroyTexture(Texture);
						SDL_FreeSurface(Str_surf);
						nick -= lengthText;
						return nick;
					}
					break;
				case SDLK_BACKSPACE:
					if (lengthText > 0)
					{
						*--nick = '\0';
						lengthText--;
						for (i = 0; i < lengthText; i++)
							nickText[i] = nick[i - lengthText];
						nickText[i] = '\0';
						if (lengthText)
						{
							textSurface = TTF_RenderText_Solid(textFont, nickText, textColor);
							textPosition.w = textSurface->w;
							textPosition.h = textSurface->h;
							textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
						}
						else
						{
							textSurface = TTF_RenderText_Solid(textFont, q, textColor);
							textPosition.w = textSurface->w;
							textPosition.h = textSurface->h;
							textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
						}
					}
					break;
				case SDLK_ESCAPE:
					exit(1);
					break;
				}
			}
			else if (ev.type == SDL_TEXTINPUT && lengthText < 10)
			{
				*nick++ = *ev.text.text;
				lengthText++;
				for (i = 0; i < lengthText; i++)
					nickText[i] = nick[i - lengthText];
				nickText[i] = '\0';
				if (lengthText)
				{
					textSurface = TTF_RenderText_Solid(textFont, nickText, textColor);
					textPosition.w = textSurface->w;
					textPosition.h = textSurface->h;
					textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
				}
			}
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
			SDL_RenderClear(ren);
			SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
			SDL_RenderCopy(ren, back_tex, NULL, &back_rect);
			SDL_RenderCopy(ren, Texture, NULL, &StrRect);
			SDL_RenderDrawRect(ren, &a);
			SDL_RenderCopy(ren, textTexture, NULL, &textPosition);
			SDL_RenderPresent(ren);
			SDL_Delay(10);
		}
	}
}
