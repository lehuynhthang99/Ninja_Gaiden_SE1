#include "RunState.h"



RunState::RunState()
{
}


RunState::~RunState()
{
}

RunState::RunState(int beginSprite, int EndSprite)
	:State(beginSprite, EndSprite)
{
	_Type = RUN_State;
	_vy = -0.1f;
	changeTo = NONE;
}

int RunState::HandleInput(StateInfo *info)
{
	//ChangeToJump
	if (changeTo == JUMP_state)
	{
		info->frameToDraw.x = 16;
		info->frameToDraw.y = 19;
		_vx = 0;
		_vy = 0;
		return JUMP_state;
	}

	//Stand
	if (!Key_Down(DIK_LEFT) && !Key_Down(DIK_RIGHT))
	{
		info->frameToDraw.x = info->frameToDraw.y = 0;
		return STAND_State;
	}

	//Duck
	if (Key_Down(DIK_DOWN))
	{
		info->frameToDraw.x = info->frameToDraw.y = 12;
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

void RunState::UpdateVelocity(LPSprite sprite)
{
	_vy = -0.1f;
	if (Key_Down(DIK_LEFT))
	{
		sprite->FlipX = -1;
		_vx = -RYU_SPEED;
	} 
	else if (Key_Down(DIK_RIGHT))
	{
		sprite->FlipX = 1;
		_vx = RYU_SPEED;
	}
	
	_countDelay += 1.0f;
	if (_countDelay >= sprite->_animDelay)
	{
		_curSprite++;
		if (_curSprite > _endSprite)
			_curSprite = _beginSprite;
		_countDelay = 0;
	}

	State::UpdateVelocity(sprite);

}

void RunState::UpdateStatus(LPSprite sprite)
{
	if (_collisionTime == 1)
	{
		changeTo = JUMP_state;
	}
	if (abs(_normalY) > 0.0001f)
	{
		_vy = 0;
		_collisionTime = 1;
	}
	if (abs(_normalX) > 0.0001f)
	{
		_vx = 0;
		_collisionTime = 0;
	}
	sprite->_X += _vx*_collisionTime;
	sprite->_Y += _vy*_collisionTime;
	
}

void RunState::UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu)
{
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
			_collisionTime = collisionTime;
			_normalX = normalX;
			_normalY = normalY;
		}
	}
}
