#include "Item.h"



Item::Item()
{
}

Item::Item(ItemDefine id, float x, float y, int CountDelay)
{
	string tmpPath = "Resource/Item/";
	int a = id;
	tmpPath += to_string(a);
	tmpPath += ".bmp";
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(tmpPath.c_str(), &info);
	sprite = Sprite(tmpPath, x, y, info.Width, info.Height, 1, 10);
	_countDelay = CountDelay;
	_id = id;
	_died = false;
	_activate = 10;
}

void Item::Update()
{
	if (_countDelay > 0)
	{
		sprite._Y -= 0.5f;
		_countDelay -= 0.5f;
		if (_activate > 0)
			_activate--;
	}
}

void Item::ItemDelete()
{
	sprite.KillSprite();
}

void Item::Render(Camera camera)
{
	sprite.Render(camera, sprite.rect);
}

Box Item::ToBox()
{
	Box tmp;
	tmp.vx = tmp.vy = 0;
	tmp.x = sprite._X - sprite.GetWidth() / 2.0f;
	tmp.y = sprite._Y + sprite.GetHeight();
	tmp.width = sprite.GetWidth();
	tmp.height = sprite.GetHeight();
	return tmp;
}

float Item::GetPosX()
{
	return sprite._X;
}

Item::~Item()
{
}
