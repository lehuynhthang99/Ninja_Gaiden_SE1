#pragma once

#include "Sprite.h"
#include "Skill.h"
#include "dxsound.h"

using namespace std;

#define DISTANCE_BETWEEN_CHAR 8
#define DISTANCE_TO_MAIN_HEALTHBOARD D3DXVECTOR2(140, -8)

class ScoreBoard
{
protected:
	Sprite sprite, DartA, DartB;
	string stringLine[3];
	RECT chaRect[256];
public:
	float _timer;
	int _score, _bossHP;
	ScoreBoard();
	~ScoreBoard();
	ScoreBoard(string Path);


	void Update(int Stage, int lives, int RyuMP, bool TimeStop);
	void Render(Camera camera, int RyuHP, SkillDefine skillType);
	void ScoreBoardDelete();

};

