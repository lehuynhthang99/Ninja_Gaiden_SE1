#include "DuckState.h"



DuckState::DuckState()
{
}


DuckState::~DuckState()
{
}

DuckState::DuckState(int beginSprite, int EndSprite)
	:State(beginSprite, EndSprite)
{
	_Type = DUCK_State;
	_vx = _vy = 0;
}

int DuckState::HandleInput(StateInfo* info)
{
	//Stand
	if (!Key_Down(DIK_DOWN))
	{
		info->frameToDraw.x = info->frameToDraw.y = 0;
		return STAND_State;
	}

	//Attack
	if (Key_Down(DIK_SPACE))
	{
		info->frameToDraw.x = 13;
		info->frameToDraw.y = 15;
		_vx = _vy = 0;
		return ATTACK_state;
	}

	return 0;
}

void DuckState::UpdateVelocity(LPSprite sprite)
{
	_vx = 0;
	_vy = -1;
}

void DuckState::UpdateStatus(LPSprite sprite)
{

}

void DuckState::UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu)
{
}

Box DuckState::ToBox(LPSprite sprite)
{
	Box tmp = State::ToBox(sprite);
	tmp.height = 20;
	tmp.y = (float)sprite->_Y + tmp.height;
	return tmp;
}
