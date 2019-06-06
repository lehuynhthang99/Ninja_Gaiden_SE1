#pragma once

#include "Ryu.h"
#include "Map.h"
#include "Wall.h"
#include "Enemy.h"

class Stage
{
public:
	int _stage;
	string _mapImg[3], _mapTxt[3], _enemyTxt[3], _wallsTxt[3], _containerTxt[3];
	int _gameWidth[3];
	POINT _ryuPos[3];

	Stage();
	Stage(string path);

	virtual ~Stage();
};

