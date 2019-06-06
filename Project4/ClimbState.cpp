#include "ClimbState.h"



ClimbState::ClimbState()
{
}


ClimbState::~ClimbState()
{
}

ClimbState::ClimbState(int beginSprite, int EndSprite, int rangeYStart, int rangeYEnd)
	:State(beginSprite, EndSprite)
{
	_Type = CLIMB_state;
	_vx = _vy = 0;
	_rangeYStart = rangeYStart;
	_rangeYEnd = rangeYEnd;
}

int ClimbState::HandleInput(StateInfo * info)
{
	if (_changeTo == JUMP_state)
	{
		info->frameToDraw.x = 16;
		info->frameToDraw.y = 19;
		_vx = 0;
		_vy = FLYING_TIME;
		return JUMP_state;
	}
	return 0;
}

void ClimbState::UpdateVelocity(LPSprite sprite)
{
	_vx = _vy = 0;
	if (Key_Down(DIK_UP))
	{
		_countDelay++;
		_vy = 0.5f;
	}
	if (Key_Down(DIK_DOWN))
	{
		_countDelay++;
		_vy = -0.5f;
	}
	if (_countDelay >= sprite->_animDelay)
	{
		_curSprite++;
		if (_curSprite > _endSprite)
			_curSprite = _beginSprite;
		_countDelay = 0;
	}
}

void ClimbState::UpdateStatus(LPSprite sprite)
{
	if (Key_Down(DIK_UP))
	{
		if (Key_Down(DIK_LEFT) && sprite->FlipY == 1 || Key_Down(DIK_RIGHT) && sprite->FlipY == -1)
			_changeTo = JUMP_state;
	}
	sprite->_X += _vx;
	sprite->_Y += _vy;
	if (sprite->_Y < _rangeYStart)
		sprite->_Y = _rangeYStart;
	if (sprite->_Y > _rangeYEnd)
		sprite->_Y = _rangeYEnd;
}

void ClimbState::UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu)
{

}
