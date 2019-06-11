#include "SkillState.h"



SkillState::SkillState()
{
}


SkillState::~SkillState()
{
}

SkillState::SkillState(int beginSprite, int EndSprite, StateDefine prevState, float vx, float vy)
	:State(beginSprite, EndSprite)
{
	_Type = SKILL_state;
	_vx = vx;
	_vy = vy;
	_prevType = prevState;
	if (_prevType == RUN_State)
		_prevType = STAND_State;
	_endState = false;
	changeTo = NONE;
}

int SkillState::HandleInput(StateInfo * info)
{
	//Prev to Stand
	if (changeTo == STAND_State)
		_prevType = STAND_State;
	if (_endState)
	{
		//Stand
		if (_prevType == STAND_State)
		{
			info->frameToDraw.x = info->frameToDraw.y = 0;
			return STAND_State;
		}

		//Jump
		if (_prevType == JUMP_state)
		{
			info->frameToDraw.x = 16;
			info->frameToDraw.y = 19;
			return JUMP_state;
		}
	}
	return 0;
}

void SkillState::UpdateVelocity(LPSprite sprite)
{
	if (_prevType == JUMP_state)
	{
		_vx = 0;
		_vy -= 0.1f;

		if (Key_Down(DIK_LEFT))
		{
			if (sprite->FlipX == -1)
				_vx = -1.0f;
			else _vx = -0.5f;
		}
		else if (Key_Down(DIK_RIGHT))
		{
			if (sprite->FlipX == 1)
				_vx = 1.0f;
			else _vx = 0.5f;
		}
	}

	_countDelay += 1.0f;
	if (_countDelay >= sprite->_animDelay)
	{
		_curSprite++;
		if (_curSprite > _endSprite)
		{
			_curSprite = _beginSprite;
			_endState = true;
		}
		_countDelay = 0;

	}
}


void SkillState::UpdateStatus(LPSprite sprite)
{
	if (_prevType == JUMP_state)
	{
		sprite->_X += _vx * _collisionTime;
		sprite->_Y += _vy * _collisionTime;
		if (_collisionTime < 1.0f && _collisionTime >= 0.0f)
		{
			if (_normalY == 1)
			{
				changeTo = STAND_State;
				return;
			}
		}
	}
}

void SkillState::UpdateCollision(LPSprite sprite, Wall * wall, Box Ryu)
{
	if (_prevType != JUMP_state)
		return;
	float normalX, normalY;
	float collisionTime = SweptAABB(Ryu, wall->ToBox(), normalX, normalY);
	if (collisionTime < 1)
	{
		if (collisionTime <= 0.0f && fabs(normalX) > 0.0001f)
		{
			_vx = 0;
			return;
		}
		if (_collisionTime == 1 ||
			_collisionTime <= 0.0f && collisionTime > 0.0f ||
			collisionTime > 0.0f && collisionTime < _collisionTime)
		{
			if (normalY == -1)
			{
				_collisionTime = 1;
				return;
			}
			_collisionTime = collisionTime;
			_normalX = normalX;
			_normalY = normalY;
		}
	}
}