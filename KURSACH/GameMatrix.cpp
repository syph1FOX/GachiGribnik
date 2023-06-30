#include "GameMatrix.h"

GameMatrix::GameMatrix()
	{
		i = j = ik = jk = 0;
		for (i = 0; i < 20; i++)
			for (j = 0; j < 16; j++)
				matrix[i][j] = false;
	}

void GameMatrix::set(int a, int b)
	{
		for (ik = i; ik < i + a; ik++)
			for (jk = j; jk < j + b; jk++)
				matrix[ik][jk] = true;
	}

void GameMatrix::SetMushroom(int& mx, int& my, int& score, int mscore, int& looseCount, int type)
{
	if (!matrix[mx][my])
		matrix[mx][my] = 2;
	else if (matrix[mx][my] == 1)
	{
		score += mscore;
		if (type == 1 || type == 6)
			looseCount++;
		mx = my = -1;
	}
}

void GameMatrix::SetPlace(int x, int y)
	{
		for (i = 0; i < 20; i++)
			for (j = 0; j < 16; j++)
				matrix[i][j] = false;
		flagx = flagy = 0;
		if (!(x % 50))
		{
			for (i = 0; i < 20; i++)
				if (i * cellsize == x)
				{
					flagx = 1;
					break;
				}
		}
		else
			for (i = 0; i < 20; i++)
				if ((i * cellsize < x) && ((i + 1) * cellsize > x))
					break;
		if (!(y % 50))
		{
			for (j = 0; j < 16; j++)
				if (j * cellsize == y)
				{
					flagy = 1;
					break;
				}
		}
		else
			for (j = 0; j < 16; j++)
				if ((j * cellsize < y) && ((j + 1) * cellsize > y))
					break;

		switch (flagx)
		{
		case 1:
			if (flagy)
				set(2, 2);
			else
				set(2, 3);
			break;
		case 0:
			if (flagy)
				set(3, 2);
			else
				set(3, 3);
		}

	}