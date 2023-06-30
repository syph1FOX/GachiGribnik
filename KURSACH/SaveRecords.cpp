#define _CRT_SECURE_NO_WARNINGS
#include "SaveRecords.h"
#include <string.h>
#include <iostream>
#include <vector>
#include <iterator>




void SaveRecords(Record r)
{
	char filename[12] = "Records.bin";

	if (*r.nick == '\0')
	{
		std::cout << "No nickname" << std::endl;
		return;
	}

	FILE* f = fopen(filename, "rb");
	int playercount, i = 0;

	if (!f)
	{
		std::cout << "file touble" << std::endl;
		playercount = 1;
		f = fopen(filename, "wb");
		fwrite(&playercount, sizeof(int), 1, f);
		fwrite(&r, sizeof(Record), 1, f);
		fclose(f);
		return;
	}
	if (!fread(&playercount, sizeof(int), 1, f))
	{
		std::cout << "file touble" << std::endl;
		playercount = 1;
		fclose(f);
		f = fopen(filename, "wb");
		fwrite(&playercount, sizeof(int), 1, f);
		fwrite(&r, sizeof(Record), 1, f);
		fclose(f);
		return;
	}

	std::vector<Record> recs;
	Record temp;
	int n = playercount;
	bool flag = false;
	while (n--)
	{
		fread(&temp, sizeof(Record), 1, f);
		if (r.score > temp.score)
		{
			recs.push_back(r);
			playercount++;
			i++;
			flag = true;
			break;
		}
		else
		{
			recs.push_back(temp);
			i++;
		}
	}
	if (flag)
	{
		recs.push_back(temp);
		while (++i < playercount)
		{
			fread(&temp, sizeof(Record), 1, f);
			recs.push_back(temp);
		}
	}
	else
	{
		recs.push_back(r);
		i++;
	}
	

	std::cout<< "SaveRecords\n" << playercount << " players" << std::endl;
	for (i = 0; i < playercount; i++)
		std::cout << i + 1 << " " << recs[i].nick << " : " << recs[i].score << std::endl;

	fclose(f);
	FILE* f1 = fopen(filename, "wb");
	if (!f1)
	{
		std::cout << "Oh shit! No saves today" << std::endl;
		return;
	}
	fwrite(&playercount, sizeof(int), 1, f1);
	auto it = recs.begin();
	while (it != recs.end())
	{
		temp = *it++;
		fwrite(&temp, sizeof(Record), 1, f1);
	}
	fclose(f1);
}