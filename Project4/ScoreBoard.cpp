#include "ScoreBoard.h"



ScoreBoard::ScoreBoard()
{
}


ScoreBoard::~ScoreBoard()
{
}

ScoreBoard::ScoreBoard(string Path)
{
	_timer = 150;
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
	DartA = Sprite("Resource/ScoreBoard/DartA.bmp", 90, 135, 20, 20, 1, 0);
	DartB = Sprite("Resource/ScoreBoard/DartB.bmp", 90, 135, 20, 20, 1, 0);
}

void ScoreBoard::Update(int Stage, int lives, int RyuMP, bool TimeStop)
{
	_timer -= 0.01f;
	char scoreLine[30];
	sprintf_s(scoreLine, "SCORE-%06d STAGE-3-%d", _score, Stage);
	stringLine[0] = scoreLine;
	sprintf_s(scoreLine, "TIMER-%03d    NINJA-", (int)ceil(_timer));
	stringLine[1] = scoreLine;
	sprintf_s(scoreLine, "P-%02d  -%02d    ENEMY-", lives, RyuMP);
	stringLine[2] = scoreLine;
}

void ScoreBoard::Render(Camera camera, int RyuHP, SkillDefine skillType)
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
	if (skillType == DartA_skill)
	{
		DartA._X = camera._X + 90;
		DartA._Y = camera._Y - 35;
		DartA.Render(camera, DartA.rect);
	}
	if (skillType == DartB_skill)
	{
		DartB._X = camera._X + 90;
		DartB._Y = camera._Y - 35;
		DartB.Render(camera, DartB.rect);
	}
}


void ScoreBoard::ScoreBoardDelete()
{
	sprite.KillSprite();
	DartA.KillSprite();
	DartB.KillSprite();
}
