#include "StandState.h"



StandState::StandState()
{
}


StandState::~StandState()
{
}

StandState::StandState(int beginSprite, int EndSprite)
	:State(beginSprite, EndSprite)
{
	_Type = STAND_State;
	_vx = _vy = 0;
}

int StandState::HandleInput(StateInfo *info)
{
	//Run
	if (Key_Down(DIK_LEFT) || Key_Down(DIK_RIGHT))
	{
		info->frameToDraw.x = 9;
		info->frameToDraw.y = 11;
		return RUN_State;
	}

	//Duck
	if (Key_Down(DIK_DOWN))
	{
		info->frameToDraw.x = info->frameToDraw.y =12;
		return DUCK_State;
	}

	//Jump
	if (Key_Down(DIK_UP))
	{
		info->frameToDraw.x = 16;
		info->frameToDraw.y = 19;
		_vx = 0;
		_vy = FLYING_TIME;
		return JUMP_state;
	}

	//Attack
	if (Key_Down(DIK_SPACE))
	{
		info->frameToDraw.x = 1;
		info->frameToDraw.y = 3;
		_vx = _vy = 0;
		return ATTACK_state;
	}

	return 0;
}

void StandState::UpdateVelocity(LPSprite sprite)
{
	_vy = -1;
	_curSprite = 0;
}

void StandState::UpdateStatus(LPSprite sprite)
{
}

void StandState::UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu)
{
}

