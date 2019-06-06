#include "Ryu.h"



Ryu::Ryu()
{
	_died = true;
}


Ryu::~Ryu()
{
}

Ryu::Ryu(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName)
{
	sprite = Sprite(Path, x, y, Width, Height, frameNumber, animDelay);
	tiles = Tiles(fileName, frameNumber);
	state = new StandState(0, 0);
	_normalX = _normalY = 0;
	_died = false;
	_invisible = 0;
	_specialChange = NONE;
	_HP = 16;
}

void Ryu::ChangeState()
{
	switch (_specialChange)
	{
	case STUN_state:
		_HP--;
		if (_HP == 0)
			_died = true;
		delete state;
		state = new StunState(16, 16, sprite.FlipX);
		_specialChange = NONE;
		return;
	default:
		break;
	}
	StateInfo info;
	int check = state->HandleInput(&info);
	//int tmpFlyingTime;
	float vx, vy;
	StateDefine tmpState;
	switch (check)
	{
	case 0:
		return;
		break;
	case STAND_State:
		if (state->_Type == STUN_state)
			_invisible = 50;
		delete state;
		state = new StandState(info.frameToDraw.x, info.frameToDraw.y);
		break;
	case RUN_State:
		delete state;
		state = new RunState(info.frameToDraw.x, info.frameToDraw.y);
		break;
	case DUCK_State:
		delete state;
		state = new DuckState(info.frameToDraw.x, info.frameToDraw.y);
		break;
	case JUMP_state:
		//tmpFlyingTime = state->GetFlyingTime();
		vx = state->_vx;
		vy = state->_vy;
		delete state;
		state = new JumpState(info.frameToDraw.x, info.frameToDraw.y, vx, vy);
		break;
	case ATTACK_state:
		tmpState = state->_Type;
		//tmpFlyingTime = state->GetFlyingTime();
		vx = state->_vx;
		vy = state->_vy;
		delete state;
		state = new AttackState(info.frameToDraw.x, info.frameToDraw.y, tmpState, vx, vy);
		break;
	case CLIMB_state:
		delete state;
		state = new ClimbState(info.frameToDraw.x, info.frameToDraw.y, info.RangeY.x, info.RangeY.y);
		break;
	define:
		break;
	}

}

void Ryu::UpdateState()
{
	ChangeState();
	state->UpdateVelocity(&sprite);
	_collisionTime = 1;
}

void Ryu::UpdateCollision(Wall* wall)
{
	/*float tmpnormalX, tmpnormalY;
	float tmpCollisionTime = SweptAABB(this->ToBox(), wall, tmpnormalX, tmpnormalY);*/
	state->UpdateCollision(&sprite, wall, this->ToBox());
	/*if (tmpCollisionTime < 1)
	{
		if (_collisionTime == 1 || 
			_collisionTime <= 0.0f && tmpCollisionTime > 0.0f || 
			tmpCollisionTime > 0.0f && tmpCollisionTime < _collisionTime)
		{
			_collisionTime = tmpCollisionTime;
			_normalX = tmpnormalX;
			_normalY = tmpnormalY;
		}
	}*/
}

void Ryu::Update()
{
	state->UpdateStatus(&sprite);
	if (sprite._Y < -35) _died = true;
	if (_invisible > 0)
		_invisible--;
}




void Ryu::Render(Camera camera)
{
	if (_invisible != 0 && _invisible % 3 != 0)
		return;
	sprite.Render(camera, tiles.getRectLocation(state->_curSprite));
}

void Ryu::SetStartPos(float x, float y)
{
	sprite._X = x;
	sprite._Y = y;
	sprite.FlipX = 1;
}

Box Ryu::ToBox()
{
	/*Box tmp;
	
	tmp.vx = state->_vx;
	tmp.vy = state->_vy;
	RECT recttmp = tiles.getRectLocation(state->_curSprite);
	tmp.width = 17;
	tmp.height = 30;
	tmp.x = (float)sprite._X - 8;
	tmp.y = (float)sprite._Y + tmp.height;
	return tmp;*/
	return state->ToBox(&sprite);
}

float Ryu::GetPosX()
{
	return sprite._X;
}

void Ryu::Remove()
{
	sprite.KillSprite();
	if (state)
		delete state;
	tiles.TilesClear();

}

StateDefine Ryu::GetStateType()
{
	return state->_Type;
}

Box Ryu::ToBoxSword()
{
	/*Box tmp;

	tmp.vx = sprite.FlipX* 22.0f;
	tmp.vy = 0;
	tmp.width = 1;
	tmp.height = 12;
	if (sprite.FlipX == 1)
	{
		tmp.x = (float)sprite._X - 3;
		tmp.y = (float)sprite._Y + 30 - 7;
	}
	else
	{
		tmp.x = (float)sprite._X + 2;
		tmp.y = (float)sprite._Y + 30 - 7;
	}
	return tmp;*/
	return state->ToBoxSword(&sprite);
}


