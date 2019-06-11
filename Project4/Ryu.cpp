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
	_skillType = NO_skill;
	skill = NULL;
	sprite = Sprite(Path, x, y, Width, Height, frameNumber, animDelay);
	tiles = Tiles(fileName, frameNumber);
	state = new StandState(0, 0);
	_normalX = _normalY = 0;
	_died = false;
	_invisible = 0;
	_specialChange = NONE;
	_HP = 16;
	_MP = 0;
	_lives = 2;
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
	case STAND_State:
		delete state;
		state = new StandState(0, 0);
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
		vx = state->_vx;
		vy = state->_vy;
		delete state;
		state = new AttackState(info.frameToDraw.x, info.frameToDraw.y, tmpState, vx, vy);
		break;
	case CLIMB_state:
		delete state;
		state = new ClimbState(info.frameToDraw.x, info.frameToDraw.y, info.RangeY.x, info.RangeY.y);
		break;
	case SKILL_state:
		tmpState = state->_Type;
		vx = state->_vx;
		vy = state->_vy;
		delete state;
		state = new SkillState(info.frameToDraw.x, info.frameToDraw.y, tmpState, vx, vy);
		if (_MP > 0 && !skill)
		{
			switch (_skillType)
			{
			case DartA_skill:
				skill = new DartA("Resource/DartA/DartA.bmp", sprite._X, sprite._Y + 12, 10, 9, 2, 1, "Resource/DartA/DartA.xml", &sprite);
				break;
			case DartB_skill:
				skill = new DartB("Resource/DartB/DartB.bmp", sprite._X, sprite._Y + 12, 18, 18, 2, 6, "Resource/DartB/DartB.xml", &sprite);
				break;
			default:
				break;
			}
		}
		
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
	state->UpdateCollision(&sprite, wall, this->ToBox());
}

void Ryu::Update()
{
	state->UpdateStatus(&sprite);
	if (sprite._Y < -35) _died = true;
	if (_invisible > 0)
		_invisible--;
	if (skill)
	{
		if (skill->_lifeSpan <= 0)
		{
			skill->SkillDelete();
			delete skill;
			skill = NULL;
		}
		else skill->Update(&sprite);
	}
}




void Ryu::Render(Camera camera)
{
	if (_invisible != 0 && _invisible % 3 != 0)
		return;
	sprite.Render(camera, tiles.getRectLocation(state->_curSprite));
	if (skill)
		skill->Render(camera);
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
	if (skill)
	{
		skill->SkillDelete();
		delete skill;
	}
}

StateDefine Ryu::GetStateType()
{
	return state->_Type;
}

LPSprite Ryu::GetSprite()
{
	return &sprite;
}

Box Ryu::ToBoxSword()
{
	return state->ToBoxSword(&sprite);
}

Box Ryu::ToSkillBox()
{
	if (skill)
		return skill->ToBox();
	return Box();
}


