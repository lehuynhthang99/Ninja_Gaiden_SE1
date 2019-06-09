#include "BossBullet_stage1.h"



BossBullet_stage1::BossBullet_stage1()
{
}

BossBullet_stage1::BossBullet_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, 
	string fileName, float FlipX)
	:Enemy(Path, x, y, Width, Height, frameNumber, animDelay, fileName)
{
	_type = GUNNERBULLET_stage1;
	_vx = FlipX * BOSS_BULLET_SPEED;
	sprite.FlipX = FlipX;
	_curSprite = 2;
	_score = 100;
}

void BossBullet_stage1::UpdateVelocity()
{
}

void BossBullet_stage1::UpdatePosition()
{
	sprite._X += _vx;
}

void BossBullet_stage1::UpdateFrame()
{
}

LPEnemy BossBullet_stage1::Update(Ryu * ryu)
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

Box BossBullet_stage1::ToBox()
{
	return Enemy::ToBox();
}


void BossBullet_stage1::Render(Camera camera)
{
	if (_died == -1)
	{
		Enemy::Render(camera);
		return;
	}
	else Enemy::DiedRender(camera);
}

BossBullet_stage1::~BossBullet_stage1()
{
}
