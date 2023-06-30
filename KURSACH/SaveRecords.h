#pragma once
#include <cstdio>
#include <string.h>

struct Record
{
	char nick[11];
	int score = 0;
};

void SaveRecords(Record r);