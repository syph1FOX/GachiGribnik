#include "game.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>
#include "loadTextureFromFile.h"
#include "DeInit.h"
#include "Init.h"
#include "isAnythingPressed.h"
#include "GiveFont.h"
#include "Menu.h"
#include "GameOver.h"
#include "Pause.h"
#include "GameMatrix.h"
#include "Mushroom.h"
#include "SaveRecords.h"


using namespace std;

struct node
{
	Mushroom mush;
	struct node* next = NULL;
	struct node* prev = NULL;
};

class Mlist
{
	node* Begin = NULL;
	node* cur = NULL;
public:
	~Mlist()
	{
		cur = Begin;
		node* temp;
		while (cur)
		{
			temp = cur;
			cur = cur->next;
			delete temp;
		}
	}
	void newNode(SDL_Renderer* ren, GameMatrix& m)
	{
		Mushroom M(rand() % 7, ren, m);
		node* temp = new node;
		cur = Begin;
		temp->mush = M;
		if (!Begin)
		{
			Begin = temp;
			Begin->next = NULL;
			Begin->prev = NULL;
		}
		else
		{
			while (cur->next != NULL)
				cur = cur->next;
			cur->next = temp;
			temp->prev = cur;
		}
		cout << temp->mush.c.x << " " << temp->mush.c.y << endl;
	}
	void DeleteNode()
	{
		if (cur->prev)
			cur->prev->next = cur->next;
		if (cur->next)
			cur->next->prev = cur->prev;
		if (cur == Begin)
			Begin = cur->next;
		node* cur1 = cur;
		cur = cur->next;
		delete cur1;
	}

	void CheckList(int dt, SDL_Renderer*& ren, GameMatrix& m, int& score, int& looseCount)
	{
		cur = Begin;
		while (cur != NULL)
		{
			m.SetMushroom(cur->mush.c.x, cur->mush.c.y, score, cur->mush.GetPoints(), looseCount, cur->mush.type);
			if (cur->mush.c.x == -1 || cur->mush.time < 0)
			{
				cur->mush.DestroyMushroom(m);
				cout << "deleted" << endl;
				DeleteNode();
			}
			else
			{
				cur->mush.time -= dt;
				SDL_RenderCopy(ren, cur->mush.GetTexture(), NULL, &cur->mush.mushroom_rect);
				cur = cur->next;
			}
		}
	}
	node* GetBegin()
	{
		return Begin;
	}
};

int game(SDL_Renderer* ren, SDL_Window* win, int& win_width, int& win_height, char *nickname)
{
	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("textures/background.png", &back_rect, ren);

	SDL_Rect player_rect, chillingPlayer_rect; //Хитбокс
	SDL_Texture* player_tex = loadTextureFromFile("textures/Boy.png", &player_rect, ren);// Распаковываем текстуры
	player_rect.w = 205;
	player_rect.h = 277;
	chillingPlayer_rect = player_rect;
	chillingPlayer_rect.x = 205;
	chillingPlayer_rect.y = 0;
	bool isRunning = true;
	SDL_Rect dst_rect = { 0, 0, 0, 0 };
	int frame = 0;
	int frame_count = 4;
	int cur_frametime = 0;
	int max_frametime = 200;

	int gametime = 90000;
	int newtime;
	int lasttime = SDL_GetTicks();
	int dt = 0;

	int MushroomTimer = 3000;
	int NowMushroomTimer = 0;


	char str[50] = "Time 0:90";
	SDL_Rect TimeRect;

	TTF_Font* font = TTF_OpenFont("fonts/impact.ttf", 50);
	SDL_Surface* str_surf = TTF_RenderText_Blended(font, str, { 0,0,0,255 });
	TimeRect = { 10,10,str_surf->w, str_surf->h };
	SDL_Texture* TimeTexture = SDL_CreateTextureFromSurface(ren, str_surf);
	SDL_FreeSurface(str_surf);

	char ScoreStr[50] = "Score: 0";
	SDL_Rect ScoreRect;
	TTF_Font* ScoreFont = TTF_OpenFont("fonts/impact.ttf", 50);
	SDL_Surface* Score_surf = TTF_RenderText_Blended(ScoreFont, ScoreStr, { 0,0,0,255 });
	ScoreRect = { 600,10,Score_surf->w, Score_surf->h };
	SDL_Texture* ScoreTexture = SDL_CreateTextureFromSurface(ren, Score_surf);
	SDL_FreeSurface(Score_surf);

	int score = 0;

	int looseCount = 0;
	char end[100];

	int pausereturn = -1;

	bool flag = false;

	SDL_Event ev;
	double x = 450, y = 350;
	double delta = 400;

	GameMatrix m;

	srand(time(NULL));

	Mlist mList;
	node* cur = NULL, * cur1 = NULL;

	bool pauseflag = 0;
	bool isUpPressed = false;
	bool isDownPressed = false;
	bool isLeftPressed = false;
	bool isRightPressed = false;

	while (isRunning && gametime > 0 && looseCount < 3)
	{
#pragma region motion

		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				exit(0);
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
					exit(0);
				case SDL_SCANCODE_UP:
					isUpPressed = true;
					break;
				case SDL_SCANCODE_DOWN:
					isDownPressed = true;
					break;
				case SDL_SCANCODE_LEFT:
					isLeftPressed = true;
					break;
				case SDL_SCANCODE_RIGHT:
					isRightPressed = true;
					break;
				case SDL_SCANCODE_F9:
					if ((pausereturn = Pause(ren)) == 0)
					{
						isRightPressed = false;
						isDownPressed = false;
						isLeftPressed = false;
						isUpPressed = false;
						break;
					}
					else
					{
						SDL_DestroyTexture(back_tex);
						SDL_DestroyTexture(player_tex);
						return 0;
					}
				}
				break;
			case SDL_KEYUP:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
					isUpPressed = false;
					break;
				case SDL_SCANCODE_DOWN:
					isDownPressed = false;
					break;
				case SDL_SCANCODE_LEFT:
					isLeftPressed = false;
					break;
				case SDL_SCANCODE_RIGHT:
					isRightPressed = false;
					break;
				}
				break;
			}
		}
		if (isUpPressed && !isDownPressed)
		{
			y -= delta * dt / 1000;
			player_rect.y = player_rect.h * 3;
		}
		if (!isUpPressed && isDownPressed)
		{
			y += delta * dt / 1000;
			player_rect.y = 0;
		}

		if (isLeftPressed && !isRightPressed)
		{
			x -= delta * dt / 1000;
			player_rect.y = player_rect.h * 2 + 2;
		}
		if (isRightPressed && !isLeftPressed)
		{
			x += delta * dt / 1000;
			player_rect.y = player_rect.h + 8;

		}

		flag = isAnythingPressed(isUpPressed, isDownPressed, isLeftPressed, isRightPressed);

		newtime = SDL_GetTicks();
		if (!pausereturn)
		{
			lasttime = SDL_GetTicks();
			pausereturn = -1;
		}
		dt = newtime - lasttime;
		lasttime = newtime;

		gametime -= dt;
		sprintf_s(str, "Time %02i:%02i", gametime / 1000 / 60, gametime / 1000 % 60);

		sprintf_s(ScoreStr, "Score: %i", score);

		NowMushroomTimer += dt;
		if (NowMushroomTimer >= MushroomTimer)
		{
			NowMushroomTimer = 0;
			mList.newNode(ren, m);
			if (MushroomTimer > 1500)
				MushroomTimer -= 100;
		}

		str_surf = TTF_RenderText_Blended(font, str, { 0,0,0,255 });
		TimeRect = { 10,10,str_surf->w, str_surf->h };
		TimeTexture = SDL_CreateTextureFromSurface(ren, str_surf);

		Score_surf = TTF_RenderText_Blended(ScoreFont, ScoreStr, { 0,0,0,255 });
		ScoreRect = { 600,10,Score_surf->w, Score_surf->h };
		ScoreTexture = SDL_CreateTextureFromSurface(ren, Score_surf);

		SDL_FreeSurface(str_surf);
		SDL_FreeSurface(Score_surf);



		dst_rect = { (int)x, (int)y, 100, 100 };


		if (x > 900)
			x -= 1;
		else if (x <= 0)
			x += 1;
		if (y < 0)
			y += 1;
		else if (y > 700)
			y -= 1;

		m.SetPlace((int)x, (int)y);

		mList.CheckList(dt, ren, m, score, looseCount);
#pragma endregion 
#pragma region Drawing
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);//Придаём цвет, параметры - Рисовальщик, RGB параметры, Параметр прозрачности 0 - прозрачно, 255 - нет.
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, back_tex, NULL, &back_rect);


		if (flag)
		{
			cur_frametime += dt;
			if (cur_frametime >= max_frametime)
			{
				cur_frametime -= max_frametime;
				frame = (frame + 1) % frame_count;
				player_rect.x = player_rect.w * frame;
			}
			SDL_RenderCopy(ren, player_tex, &player_rect, &dst_rect);
		}
		else
			SDL_RenderCopy(ren, player_tex, &chillingPlayer_rect, &dst_rect);
		cur = mList.GetBegin();
		if (cur)
		{
			SDL_RenderCopy(ren, cur->mush.GetTexture(), NULL, &cur->mush.mushroom_rect);
			while (cur->next)
			{
				cur1 = cur->next;
				SDL_RenderCopy(ren, cur1->mush.GetTexture(), NULL, &cur->next->mush.mushroom_rect);
				cur = cur1;
			}
		}
		SDL_RenderCopy(ren, TimeTexture, NULL, &TimeRect);
		SDL_RenderCopy(ren, ScoreTexture, NULL, &ScoreRect);
		SDL_RenderPresent(ren);
#pragma endregion 
		SDL_DestroyTexture(TimeTexture);
		SDL_DestroyTexture(ScoreTexture);
	}

	SDL_DestroyTexture(back_tex);
	SDL_DestroyTexture(player_tex);
	if (gametime <= 0)
		sprintf_s(end, "Out of time!");
	Record r;
	strcpy_s(r.nick, 11, nickname);
	r.score = score;
	SaveRecords(r);
	GameOver(ren, score, end);
	return 0;
}