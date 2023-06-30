#pragma once
class GameMatrix
{
	int cellsize = 50;
	bool flagx = 0, flagy = 0;
	int i, j, ik, jk;
public:
	bool matrix[20][16];
	GameMatrix();

	void set(int a, int b);

	void SetMushroom(int& mx, int& my, int& score, int mscore, int& looseCount, int type);

	void SetPlace(int x, int y);
};

