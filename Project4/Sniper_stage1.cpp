#include "Sniper_stage1.h"



Sniper_stage1::Sniper_stage1()
{
}

Sniper_stage1::Sniper_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName)
	:Enemy(Path, x, y, Width, Height, frameNumber, animDelay, fileName)
{
	_type = SNIPER_stage1;
	_vy = _vx = 0;
	sprite.FlipX = -1;
	_bulletAdd = false;
	_Path = Path;
	_fileName = fileName;
	RECT recttmp = tiles.getRectLocation(_curSprite);
	_center = D3DXVECTOR3((recttmp.right - recttmp.left) / 2.0f, (recttmp.bottom - recttmp.top), 0);
}

void Sniper_stage1::UpdateVelocity(Ryu * ryu)
{
	Box tmp = ryu->ToBox();
	if (tmp.x + 8 - sprite._X >= 0)
		sprite.FlipX = 1;
	else sprite.FlipX = -1;
}

void Sniper_stage1::UpdatePosition()
{
}

void Sniper_stage1::UpdateFrame()
{
	if ((int)(_countDelay / (sprite._animDelay*1.75)) <= 10)
		_curSprite = 0;
	else if ((int)(_countDelay / (sprite._animDelay*1.75)) <= 11)
		_curSprite = 1;
	_countDelay++;
	if ((int)(_countDelay / (sprite._animDelay*1.75)) >= 12)
	{
		_countDelay = 0;
		_bulletAdd = true;
	}
	RECT recttmp = tiles.getRectLocation(_curSprite);
	_center.y = recttmp.bottom - recttmp.top;
	recttmp = tiles.getRectLocation(0);
	if (_curSprite == 0)
		_center.x = (recttmp.right - recttmp.left) / 2.0f;
	else _center.x = (recttmp.right - recttmp.left) / 2.0f + 2;

}

LPEnemy Sniper_stage1::Update(Ryu * ryu)
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
	LPEnemy bullet = new SniperBullet_stage1(_Path, sprite._X + 10 * sprite.FlipX, sprite._Y + 19, NULL, NULL, 3, 10,
		_fileName, sprite.FlipX);
	return bullet;
}

Box Sniper_stage1::ToBox()
{
	Box tmp;
	tmp.vx = _vx;
	tmp.vy = _vy;
	RECT recttmp = tiles.getRectLocation(0);
	tmp.width = recttmp.right - recttmp.left;
	tmp.height = recttmp.bottom - recttmp.top;
	tmp.x = (float)sprite._X - tmp.width / 2;
	tmp.y = (float)sprite._Y + tmp.height;
	return tmp;
}


void Sniper_stage1::Render(Camera camera)
{
	if (_died == -1)
	{
		sprite.Render(camera, tiles.getRectLocation(_curSprite), _center);
		return;
	}
	else Enemy::DiedRender(camera);
}

Sniper_stage1::~Sniper_stage1()
{
}
