#pragma once

class Skill;
typedef class Skill* LPSkill;

#include "Sprite.h"
#include "Item.h"
#include "Tiles.h"

enum SkillDefine
{
	NO_skill = 0,
	DartA_skill = 1,
	DartB_skill = 2,
};

class Skill
{
protected:
	Sprite sprite;
	float _vx, _vy;
	Tiles tiles;
	float _countDelay;
	int _curSprite;
public:
	SkillDefine _type;
	float _lifeSpan;
	Skill();
	Skill(string Path, float x, float y, int Width, int Height, int frameNumber, float LifeSpan, string fileName);

	virtual void UpdateVelocity(LPSprite RyuSprite) = 0;
	virtual void Update(LPSprite RyuSprite) = 0;
	virtual void SkillDelete();
	virtual void Render(Camera camera);

	virtual Box ToBox();
	virtual ~Skill();
};

