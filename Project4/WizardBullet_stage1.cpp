#include "WizardBullet_stage1.h"



WizardBullet_stage1::WizardBullet_stage1()
{
}

WizardBullet_stage1::WizardBullet_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay,
	string fileName, float FlipX)
	:Enemy(Path, x, y, Width, Height, frameNumber, animDelay, fileName)
{
	_type = WIZARDBULLET_stage1;
	_vx = FlipX;
	_vy = BULLET_FLYING_TIME;
	_curSprite = 3;
	RECT recttmp = tiles.getRectLocation(_curSprite);
	_center = D3DXVECTOR3((recttmp.right - recttmp.left) / 2.0f, (recttmp.bottom - recttmp.top) / 2.0f, 0);
	_score = 100;
}

void WizardBullet_stage1::UpdateVelocity()
{
	if (sprite._Y >= -30)
		_vy -= 0.05f;
	else _vy = _vx = 0;
}

void WizardBullet_stage1::UpdatePosition()
{
	sprite._X += _vx;
	sprite._Y += _vy;
}

void WizardBullet_stage1::UpdateFrame()
{
	_countDelay += 2;
	switch ((int)(_countDelay / sprite._animDelay))
	{
	case 0:
		sprite.FlipX = 1;
		sprite.FlipY = 1;
		break;
	case 1:
		sprite.FlipX = -1;
		sprite.FlipY = 1;
		break;
	case 2:
		sprite.FlipX = -1;
		sprite.FlipY = -1;
		break;
	case 3:
		sprite.FlipX = 1;
		sprite.FlipY = -1;
		break;
	default:
		break;
	}
	if ((int)(_countDelay / sprite._animDelay) >= 4)
		_countDelay = 0;
}

LPEnemy WizardBullet_stage1::Update(Ryu * ryu)
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
	UpdateVelocity();
	UpdatePosition();
	UpdateFrame();
	return NULL;
}

Box WizardBullet_stage1::ToBox()
{
	Box tmp;
	tmp.vx = _vx;
	tmp.vy = _vy;
	RECT recttmp = tiles.getRectLocation(_curSprite);
	tmp.width = recttmp.right - recttmp.left;
	tmp.height = recttmp.bottom - recttmp.top;
	tmp.x = (float)sprite._X - tmp.width / 2;
	tmp.y = (float)sprite._Y + tmp.height/ 2;
	return tmp;
}

void WizardBullet_stage1::Render(Camera camera)
{
	if (_died == -1)
	{
		sprite.Render(camera, tiles.getRectLocation(_curSprite), _center);
		return;
	}
	else Enemy::DiedRender(camera);
}


WizardBullet_stage1::~WizardBullet_stage1()
{
}
