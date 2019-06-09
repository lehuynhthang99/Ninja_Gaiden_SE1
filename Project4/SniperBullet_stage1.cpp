#include "SniperBullet_stage1.h"



SniperBullet_stage1::SniperBullet_stage1()
{
}

SniperBullet_stage1::SniperBullet_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, 
	string fileName, float FlipX)
	:Enemy(Path, x, y, Width, Height, frameNumber, animDelay, fileName)
{
	_type = SNIPERBULLET_stage1;
	_vx = FlipX * SNIPER_BULLET_SPEED;
	sprite.FlipX = FlipX;
	_curSprite = 2;
	_score = 100;
}

void SniperBullet_stage1::UpdateVelocity()
{
}

void SniperBullet_stage1::UpdatePosition()
{
	sprite._X += _vx;
}

void SniperBullet_stage1::UpdateFrame()
{
}

LPEnemy SniperBullet_stage1::Update(Ryu * ryu)
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

Box SniperBullet_stage1::ToBox()
{
	return Enemy::ToBox();
}


void SniperBullet_stage1::Render(Camera camera)
{
	if (_died == -1)
	{
		Enemy::Render(camera);
		return;
	}
	else Enemy::DiedRender(camera);
}

SniperBullet_stage1::~SniperBullet_stage1()
{
}
