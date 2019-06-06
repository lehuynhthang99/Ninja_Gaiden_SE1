#include "StunState.h"



StunState::StunState()
{
}


StunState::~StunState()
{
}

StunState::StunState(int beginSprite, int EndSprite, int FlipX)
	:State(beginSprite, EndSprite)
{
	_Type = STUN_state;
	_vx = -FlipX * 0.5f;
	_vy = FLYING_TIME;
	changeTo = NONE;
}

int StunState::HandleInput(StateInfo * info)
{
	//Stand
	if (changeTo == STAND_State)
	{
		info->frameToDraw.x = info->frameToDraw.y = 0;
		return STAND_State;
	}
	return 0;
}

void StunState::UpdateVelocity(LPSprite sprite)
{
	_vy -= 0.1f;
	State::UpdateVelocity(sprite);
}

void StunState::UpdateStatus(LPSprite sprite)
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

void StunState::UpdateCollision(LPSprite sprite, Wall * wall, Box Ryu)
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
