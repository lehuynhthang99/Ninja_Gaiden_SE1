#pragma once

#include "Sprite.h"

using namespace std;

#define DISTANCE_BETWEEN_CHAR 8
#define DISTANCE_TO_MAIN_HEALTHBOARD D3DXVECTOR2(140, -8)

class ScoreBoard
{
protected:
	Sprite sprite;
	string stringLine[3];
	RECT chaRect[256];
public:
	int _score, _bossHP;
	ScoreBoard();
	~ScoreBoard();
	ScoreBoard(string Path);


	void Update(int Stage, float Timer, int lives, int RyuMP);
	void Render(Camera camera, int RyuHP);
	void ScoreBoardDelete();

};

