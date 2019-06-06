#include "Wizard_stage1.h"



Wizard_stage1::Wizard_stage1()
{
}

Wizard_stage1::Wizard_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
	float rangeXstart, float rangeXend)
	:Enemy(Path, x, y, Width, Height, frameNumber, animDelay, fileName)
{
	_type = WIZARD_stage1;
	_rangeXstart = rangeXstart;
	_rangeXend = rangeXend;
	_vy = 0;
	_vx = -WIZARD_STAGE1_SPEED;
	sprite.FlipX = -1;
	_bulletAdd = false;
	_Path = Path;
	_fileName = fileName;
}

void Wizard_stage1::UpdateVelocity(Ryu * ryu)
{
	if (sprite._X > _rangeXend || sprite._X < _rangeXstart)
		_vx *= -1;
	Box tmp = ryu->ToBox();
	if (tmp.x + 8 - sprite._X >= 0)
		sprite.FlipX = 1;
	else sprite.FlipX = -1;
}

void Wizard_stage1::UpdatePosition()
{
	sprite._X += _vx;
}

void Wizard_stage1::UpdateFrame()
{
	switch ((int)(_countDelay / (sprite._animDelay*1.75)))
	{
	case 0:
	case 2:
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	//case 14:
		_curSprite = 0;
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 9:
	case 11:
	//case 13:
		_curSprite = 1;
		break;
	case 13:
		_curSprite = 2;
		break;
	default:
		break;
	}
	_countDelay++;
	if ((int)(_countDelay / (sprite._animDelay*1.75)) >= 14)
	{
		_countDelay = 0;
		_bulletAdd = true;
	}
}

LPEnemy Wizard_stage1::Update(Ryu * ryu)
{
	if (ryu->GetStateType() != ATTACK_state)
		_isAttacked = false;
	if (_HP == 0)
	{
		_HP--;
		_died = 20;
	}
	if (_died != -1)
	{
		Enemy::DiedUpdate();
		return NULL;
	}
	UpdateVelocity(ryu);
	UpdatePosition();
	UpdateFrame();
	if (!_bulletAdd)
		return NULL;
	_bulletAdd = false;
	LPEnemy bullet = new WizardBullet_stage1(_Path, sprite._X + 10*sprite.FlipX, sprite._Y + 25, NULL, NULL, 4, 10,
		_fileName, sprite.FlipX);
	return bullet;
}

Box Wizard_stage1::ToBox()
{
	return Enemy::ToBox();
}

void Wizard_stage1::Render(Camera camera)
{
	if (_died == -1)
	{
		Enemy::Render(camera);
		return;
	}
	else Enemy::DiedRender(camera);
}


Wizard_stage1::~Wizard_stage1()
{
}
