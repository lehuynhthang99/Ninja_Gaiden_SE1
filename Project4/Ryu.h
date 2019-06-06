#pragma once

#include "StandState.h"
#include "RunState.h"
#include "DuckState.h"
#include "JumpState.h"
#include "AttackState.h"
#include "Tiles.h"
#include "Wall.h"
#include "ClimbState.h"
#include "StunState.h"

class Ryu
{
protected:
	LPState state;
	Tiles tiles;
	Sprite sprite;
	float _collisionTime, _normalX, _normalY;
public:
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
	void SetStartPos(float x, float y);

	Box ToBox();

	float GetPosX();
	void Remove();
	StateDefine GetStateType();
	Box ToBoxSword();
};

