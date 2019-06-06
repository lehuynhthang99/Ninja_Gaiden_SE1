#include "AttackState.h"



AttackState::AttackState()
{
}


AttackState::~AttackState()
{
}

AttackState::AttackState(int beginSprite, int EndSprite, StateDefine prevState, float vx, float vy)
	:State(beginSprite, EndSprite)
{
	_Type = ATTACK_state;
	_vx = vx;
	_vy = vy;
	_prevType = prevState;
	if (_prevType == RUN_State)
		_prevType = STAND_State;
	_endState = false;
	changeTo = NONE;
	_SwordBox.width = 1;
	_SwordBox.height = 12;
	_SwordBox.vy = 0;
}

int AttackState::HandleInput(StateInfo* info)
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

		//Duck
		if (_prevType == DUCK_State)
		{
			info->frameToDraw.x = info->frameToDraw.y = 12;
			return DUCK_State;
		}
	}

	return 0;
}

void AttackState::UpdateVelocity(LPSprite sprite)
{
	if (_prevType == JUMP_state)
	{
		_vx = 0;
		//sprite->_Y += _vx;
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
		//sprite->_X += _vy;
	}
	
	_countDelay += 1.0f;
	//DebugOut((wchar_t*)L"%f %d\n",_countDelay, _curSprite);
	if (_countDelay >= sprite->_animDelay)
	{
		_curSprite++;
		//DebugOut((wchar_t*)L"inc %d\n", _curSprite);
		if (_curSprite > _endSprite)
		{
			_curSprite = _beginSprite;
			_endState = true;
		}
		_countDelay = 0;
		
	}
}

void AttackState::UpdateStatus(LPSprite sprite)
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
			if (_normalY == -1)
				_vy = 0;
		}
	}
	/*else if (_prevType == STAND_State)
	{
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
		sprite->_X += _vx * _collisionTime;
		sprite->_Y += _vy * _collisionTime;
	}*/
}

void AttackState::UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu)
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
			_collisionTime = collisionTime;
			_normalX = normalX;
			_normalY = normalY;
		}
	}
}

Box AttackState::ToBoxSword(LPSprite sprite)
{
	if (sprite->FlipX == 1)
		_SwordBox.x = (float)sprite->_X - 1;
	else 
		_SwordBox.x = (float)sprite->_X;
	_SwordBox.vx = sprite->FlipX* 22.0f;
	if (_prevType == DUCK_State)
		_SwordBox.y = (float)sprite->_Y + 30 - 12;
	else 
		_SwordBox.y = (float)sprite->_Y + 30 - 7;
	return _SwordBox;
}

Box AttackState::ToBox(LPSprite sprite)
{
	if (_prevType == DUCK_State)
	{
		Box tmp = State::ToBox(sprite);
		tmp.height = 20;
		tmp.y = (float)sprite->_Y + tmp.height;
		return tmp;
	}
	else
	{
		return State::ToBox(sprite);
	}
}

