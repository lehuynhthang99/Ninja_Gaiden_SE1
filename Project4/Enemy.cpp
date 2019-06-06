#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName)
{
	sprite = Sprite(Path, x, y, Width, Height, frameNumber, animDelay);
	tiles = Tiles(fileName, frameNumber);
	_countDelay = 0;
	_curSprite = 0;
	_died = -1;
	_HP = 1;
	_isAttacked = false;
}

void Enemy::UpdateVelocity()
{
}

void Enemy::UpdatePosition()
{
}

void Enemy::UpdateFrame()
{
}


float Enemy::GetPosX()
{
	return sprite._X;
}

void Enemy::Render(Camera camera)
{
	sprite.Render(camera, tiles.getRectLocation(_curSprite));
}

Box Enemy::ToBox()
{
	Box tmp;
	tmp.vx = _vx;
	tmp.vy = _vy;
	RECT recttmp = tiles.getRectLocation(_curSprite);
	tmp.width = recttmp.right - recttmp.left;
	tmp.height = recttmp.bottom - recttmp.top;
	tmp.x = (float)sprite._X - tmp.width / 2.0f;
	tmp.y = (float)sprite._Y + tmp.height;
	return tmp;
}

Enemy::~Enemy()
{
}

void Enemy::EnemyDelete()
{
	sprite.KillSprite();
	tiles.TilesClear();
}

void Enemy::DiedRender(Camera camera)
{
	sprite.Render(camera, sprite.rect);
}

void Enemy::DiedUpdate()
{
	if (_died < 20)
	{
		_died--;
	}
	else
	{
		float a, b;
		a = sprite._X;
		b = sprite._Y;
		sprite = Sprite("Resource/Enemies/DiedAnimation.bmp", a, b, 30, 38, 1, 10);
		_beginSprite = _endSprite = _curSprite = 0;
		_died--;
	}
}
