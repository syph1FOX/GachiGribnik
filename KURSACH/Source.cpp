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
* Правила игры. В разных точках экрана на некоторое время появляются грибы, как съедобные, так и несъедобные. 
Игрок, управляя грибником, собирает грибы. 
За каждый вид гриба дается определенное количество очков: 
белый – 10, подосиновик, подберезовик – 8, лисичка – 5, сыроежка – 2, поганка, мухомор – -10. 
При попадании в корзину трех несъедобных грибов игра заканчивается, а набранные очки обнуляются. 
С течением времени продолжительность жизни грибов уменьшается. На всю игру отводится 1,5 минуты. 
По завершении игры на экран выводится набранное число очков. 
10 лучших результатов хранятся в файле и выводятся на экран по запросу пользователя.
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
