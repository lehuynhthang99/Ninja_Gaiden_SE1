#include "ScoreBoard.h"



ScoreBoard::ScoreBoard()
{
}


ScoreBoard::~ScoreBoard()
{
}

ScoreBoard::ScoreBoard(string Path)
{
	_score = 0;
	sprite = Sprite(Path, 0, 0, 8, 8, 256, 0);
	for (int i = 0; i < 256; i++)
	{
		chaRect[i].left = i % 16 * 8;
		chaRect[i].top = i / 16 * 8;
		chaRect[i].right = chaRect[i].left + 8;
		chaRect[i].bottom = chaRect[i].top + 8;
	}
	_bossHP = 16;
}

void ScoreBoard::Update(int Stage, float Timer, int lives, int RyuMP)
{
	char scoreLine[30];
	sprintf_s(scoreLine, "SCORE-%06d STAGE-3-%d", _score, Stage);
	stringLine[0] = scoreLine;
	sprintf_s(scoreLine, "TIMER-%03d    NINJA-", (int)Timer);
	stringLine[1] = scoreLine;
	sprintf_s(scoreLine, "P-%02d  -%02d    ENEMY-", lives, RyuMP);
	stringLine[2] = scoreLine;
}

void ScoreBoard::Render(Camera camera, int RyuHP)
{
	D3DXVECTOR2 origin = D3DXVECTOR2(camera._X + 10, camera._Y - 15);
	D3DXVECTOR2 tmpPos = origin;
	for (int i = 0; i < 3; i++)
	{
		int j = 0;
		while (stringLine[i][j] != '\0')
		{
			sprite._X = tmpPos.x;
			sprite._Y = tmpPos.y;
			sprite.Render(camera, chaRect[(int)stringLine[i][j]]);
			tmpPos.x += DISTANCE_BETWEEN_CHAR;
			j++;
		}
		tmpPos.x = origin.x;
		tmpPos.y -= DISTANCE_BETWEEN_CHAR;
	}

	tmpPos = origin + DISTANCE_TO_MAIN_HEALTHBOARD;
	tmpPos.y += DISTANCE_BETWEEN_CHAR;
	sprite._Y = tmpPos.y;
	for (int i = 0; i < 16; i++)
	{
		tmpPos.x += 5;
		sprite._X = tmpPos.x;
		if (i < RyuHP)
		{
			sprite.Render(camera, chaRect[254], D3DXVECTOR3(0, 0, 0));
		}
		else
			sprite.Render(camera, chaRect[22], D3DXVECTOR3(0, 0, 0));
	}

	tmpPos = origin + DISTANCE_TO_MAIN_HEALTHBOARD;
	sprite._Y = tmpPos.y;
	for (int i = 0; i < 16; i++)
	{
		tmpPos.x += 5;
		sprite._X = tmpPos.x;
		if (i < _bossHP)
		{
			sprite.Render(camera, chaRect[254], D3DXVECTOR3(0, 0, 0));
		}
		else
			sprite.Render(camera, chaRect[22], D3DXVECTOR3(0, 0, 0));
	}
}


void ScoreBoard::ScoreBoardDelete()
{
	sprite.KillSprite();
}
