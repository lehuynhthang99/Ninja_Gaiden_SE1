#include "Boss_stage1.h"



Boss_stage1::Boss_stage1()
{
}

Boss_stage1::Boss_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName)
	:Enemy(Path, x, y, Width, Height, frameNumber, animDelay, fileName)
{
	_type = BOSS_stage1;
	_vy = BOSS_FLYING_TIME;
	_vx = -3.0f;
	sprite.FlipX = -1;
	_bulletAdd = false;
	_countBullet = 1;
	_Path = Path;
	_fileName = fileName;
	_jump = false;
	_shoot = false;
	_startPos = y;
	_HP = 16;
	_score = 10000;
}

void Boss_stage1::UpdateVelocity(Ryu * ryu)
{
	if (_jump)
	{
		_vy -= 0.1f;
		_vx = sprite.FlipX*2.0f;
	}
}

void Boss_stage1::UpdatePosition()
{
	if (_jump)
	{
		sprite._X += _vx;
		sprite._Y += _vy;
		if (sprite._Y <= _startPos)
			sprite._Y = _startPos;
	}
}

void Boss_stage1::UpdateFrame()
{
	if (!_jump && (int)(_countDelay / (sprite._animDelay*1.75)) >= 10)
	{
		_jump = true;
		_countDelay = 0;
		_curSprite = 1;
		_countBullet++;
		_vy = BOSS_FLYING_TIME;
		_vx = sprite.FlipX * 3.0f;
		if (_countBullet >= 3)
		{
			_shoot = true;
			_bulletAdd = true;
		}
	}
	else if (_jump)
	{
		if (_vy <= -BOSS_FLYING_TIME)
		{
			_jump = false;
			_curSprite = 0;
			sprite.FlipX *= -1;
			_vy = sprite.FlipX*BOSS_FLYING_TIME;
			_vx = -_vx;
			_countDelay = 0;
			return;
		}
		else if (_shoot)
		{
			if ((int)(_countDelay / (sprite._animDelay*0.4f)) >= 0.5f)
			{
				_countDelay = 0;
				_countBullet--;
				_bulletAdd = true;
				if (_countBullet == 1)
				{
					_shoot = false;
					_countBullet = 0;
				}
			}
		}
	}
	
	_countDelay++;
}

LPEnemy Boss_stage1::Update(Ryu * ryu)
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
	LPEnemy bullet = new BossBullet_stage1(_Path, sprite._X + 10 * sprite.FlipX, sprite._Y + 3, NULL, NULL, 3, 10,
		_fileName, sprite.FlipX);
	return bullet;
}

Box Boss_stage1::ToBox()
{
	return Enemy::ToBox();
}


void Boss_stage1::Render(Camera camera)
{
	if (_died == -1)
	{
		Enemy::Render(camera);
		return;
	}
	else Enemy::DiedRender(camera);
}

Boss_stage1::~Boss_stage1()
{
}
