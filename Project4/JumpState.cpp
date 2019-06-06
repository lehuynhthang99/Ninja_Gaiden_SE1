#include "JumpState.h"



JumpState::JumpState()
{
}


JumpState::~JumpState()
{
}

JumpState::JumpState(int beginSprite, int EndSprite, float vx, float vy)
	:State(beginSprite, EndSprite)
{
	_Type = JUMP_state;
	_vx = vx;
	_vy = vy;
	changeTo = NONE;

}

int JumpState::HandleInput(StateInfo *info)
{
	//Stand
	if (changeTo == STAND_State)
	{
		info->frameToDraw.x = info->frameToDraw.y = 0;
		return STAND_State;
	}

	//Climb
	if (changeTo == CLIMB_state)
	{
		info->frameToDraw.x = 7;
		info->frameToDraw.y = 8;
		Box tmpWall = _climbWall->ToBox();
		info->RangeY.x = tmpWall.y - tmpWall.height;
		info->RangeY.y = tmpWall.y;
		return CLIMB_state;
	}

	//Attack
	if (Key_Down(DIK_SPACE))
	{
		info->frameToDraw.x = 1;
		info->frameToDraw.y = 3;
		return ATTACK_state;
	}

	return 0;
}

void JumpState::UpdateVelocity(LPSprite sprite)
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
	
	_countDelay+=2;
	if (_countDelay >= sprite->_animDelay)
	{
		_curSprite++;
		if (_curSprite > _endSprite)
			_curSprite = _beginSprite;
		_countDelay = 0;
	}

	State::UpdateVelocity(sprite);
}

void JumpState::UpdateStatus(LPSprite sprite)
{
	sprite->_X += _vx * _collisionTime;
	sprite->_Y += _vy * _collisionTime;
	if (_collisionTime < 1.0f && fabs(_collisionTime) >= 0.0)
	{
		if (_normalY == 1)
		{
			changeTo = STAND_State;
			return;
		}
		/*if (_normalY == -1)
			_vy = 0;*/
	}
}

void JumpState::UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu)
{
	if (changeTo == CLIMB_state)
		return;
	float normalX, normalY;
	float collisionTime = SweptAABB(Ryu, wall->ToBox(), normalX, normalY);
	if (collisionTime < 1)
	{
		if (collisionTime <= 0.0f && fabs(normalX) > 0.0001f)
		{
			if (normalX == -1 && wall->_left || normalX == 1 && wall->_right)
			{
				_collisionTime = 0;
				changeTo = CLIMB_state;
				_climbWall = wall;
				return;
			}

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

