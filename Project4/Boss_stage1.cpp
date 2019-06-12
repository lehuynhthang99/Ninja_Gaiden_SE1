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
		playSound(boss_jump_sound);
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
		_died = 400;
	}
	if (_died != -1)
	{
		DiedUpdate();
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

void Boss_stage1::DiedUpdate()
{
	if (_died < 400)
	{
		_countDelay++;
		if (_countDelay >= 5)
		{
			diedcurSprite++;
			_countDelay = 0;
		}
		if (diedcurSprite >= 2)
			diedcurSprite = 0;
		DebugOut((wchar_t*)L"diedcurSprite: %d\n", diedcurSprite);
		_died--;
	}
	else
	{
		stopSound(stageboss_bgm);
		playSound(boss_died_sound);
		diedSprite = Sprite("Resource/Enemies/Boss_died.bmp", sprite._X, sprite._Y, NULL, NULL, 2, 10);
		diedTiles = Tiles("Resource/Enemies/Boss_died.xml", 2);
		diedcurSprite = 0;
		_countDelay = 0;
		_died--;
	}
}

void Boss_stage1::EnemyDelete()
{
	diedSprite.KillSprite();
	diedTiles.TilesClear();
	Enemy::EnemyDelete();
}

void Boss_stage1::DiedRender(Camera camera)
{
	sprite.Render(camera, tiles.getRectLocation(_curSprite));
	RECT tmp = diedTiles.getRectLocation(diedcurSprite);
	D3DXVECTOR3 center = D3DXVECTOR3((tmp.right - tmp.left) / 2.0f, (tmp.bottom - tmp.top) / 2.0f, 0);
	diedSprite._X = sprite._X - 15;
	diedSprite._Y = sprite._Y + 30;
	diedSprite.Render(camera, diedTiles.getRectLocation(diedcurSprite), center);
	diedSprite._X = sprite._X + 10;
	diedSprite._Y = sprite._Y + 20;
	diedSprite.Render(camera, diedTiles.getRectLocation(diedcurSprite), center);
	diedSprite._X = sprite._X;
	diedSprite._Y = sprite._Y + 10;
	diedSprite.Render(camera, diedTiles.getRectLocation(diedcurSprite), center);
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
	else DiedRender(camera);
}

Boss_stage1::~Boss_stage1()
{
}
