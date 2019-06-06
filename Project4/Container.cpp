#include "Container.h"



Container::Container()
{
}

Container::Container(string Path, float x, float y, int Width, int Height, int frameNumber, int animDelay, string fileName, ItemDefine item, int itemCountDelay)
{
	sprite = Sprite(Path, x, y, Width, Height, frameNumber, animDelay);
	tiles = Tiles(fileName, frameNumber);
	_item = item;
	_countDelay = 0;
	_died = false;
	_curSprite = 0;
	_itemCountDelay = itemCountDelay;
}

LPItem Container::Update()
{
	if (_died)
	{
		LPItem tmp = new Item(_item, sprite._X, sprite._Y, _itemCountDelay);
		return tmp;
	}

	if (_countDelay >= 10)
	{
		_curSprite++;
		_countDelay = 0;
	}
	if (_curSprite >= 2)
		_curSprite = 0;
	_countDelay++;
	return NULL;
}

void Container::Render(Camera camera)
{
	sprite.Render(camera, tiles.getRectLocation(_curSprite));
}

void Container::ContainerDelete()
{
	sprite.KillSprite();
	tiles.TilesClear();
}

float Container::GetPosX()
{
	return sprite._X;
}

Box Container::ToBox()
{
	Box tmp;
	tmp.vx = tmp.vy = 0;
	RECT rect = tiles.getRectLocation(_curSprite);
	tmp.width = rect.right - rect.left;
	tmp.height = rect.bottom - rect.top;
	tmp.x = sprite._X - tmp.width / 2.0f;
	tmp.y = sprite._Y + tmp.height;
	
	return tmp;
}

Container::~Container()
{
}
