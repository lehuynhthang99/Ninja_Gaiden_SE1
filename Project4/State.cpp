#include "State.h"



State::State()
{
}


State::~State()
{
}

State::State(int beginSprite, int EndSprite)
{
	_beginSprite = beginSprite;
	_endSprite = EndSprite;
	_curSprite = beginSprite;
	_countDelay = 0;
	_vx = _vy = 0;
	_collisionTime = 1;
	_normalX = _normalY = 0;
}

void State::UpdateVelocity(LPSprite sprite)
{
	_collisionTime = 1;
	_normalX = _normalY = 0;
}

Box State::ToBoxSword(LPSprite sprite)
{
	return Box();
}

Box State::ToBox(LPSprite sprite)
{
	Box tmp;

	tmp.vx = _vx;
	tmp.vy = _vy;
	//RECT recttmp = tiles.getRectLocation(state->_curSprite);
	tmp.width = 17;
	tmp.height = 30;
	tmp.x = (float)sprite->_X - 8;
	tmp.y = (float)sprite->_Y + tmp.height;
	return tmp;
}

//int State::GetFlyingTime()
//{
//	return FLYING_TIME;
//}
