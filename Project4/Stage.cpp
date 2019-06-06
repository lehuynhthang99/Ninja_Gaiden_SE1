#include "Stage.h"



Stage::Stage()
{
}

Stage::Stage(string path)
{
	_stage = 0;
	ifstream txt;
	txt.open(path);
	int num;
	txt >> num;
	for (int i = 0; i < 3; i++)
	{
		txt >> _mapImg[i] >> _mapTxt[i] >> _ryuPos[i].x >> _ryuPos[i].y >> _wallsTxt[i] >> _enemyTxt[i] >> _containerTxt[i] >>_gameWidth[i];
	}
}

Stage::~Stage()
{
}
