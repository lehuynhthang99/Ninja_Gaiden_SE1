#pragma once

class Ryu;
typedef class Ryu* LPRyu;

#include "StandState.h"
#include "RunState.h"
#include "DuckState.h"
#include "JumpState.h"
#include "AttackState.h"
#include "Tiles.h"
#include "Wall.h"
#include "ClimbState.h"
#include "StunState.h"
#include "SkillState.h"
#include "DartA.h"
#include "DartB.h"
#include "dxsound.h"

class Ryu
{
protected:
	LPSkill skill;
	LPState state;
	Tiles tiles;
	Sprite sprite;
public:
	SkillDefine _skillType;
	int _lives;
	int _HP, _MP;
	bool _died;
	int _invisible;
	StateDefine _specialChange;

	Ryu();
	virtual ~Ryu();
	Ryu(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName);
	
	void ChangeState();

	void UpdateState();
	void UpdateCollision(Wall* wall);
	void Update();

	void Render(Camera camera);
	void ChangeStage(float x, float y);

	Box ToBox();

	float GetPosX();
	void Remove();
	StateDefine GetStateType();
	LPSprite GetSprite();
	Box ToBoxSword();
	Box ToSkillBox();
	LPSkill GetSkill();
	void KillSkill();
};

