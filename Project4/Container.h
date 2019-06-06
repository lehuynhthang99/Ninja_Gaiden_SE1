#pragma once

#include "Item.h"
#include "Tiles.h"

class Container;
typedef Container* LPContainer;

class Container
{
protected:
	Sprite sprite;
	ItemDefine _item;
	Tiles tiles;
	int _countDelay, _itemCountDelay;
	int _beginSprite, _endSprite, _curSprite;
public:
	bool _died;
	Container();
	Container(string Path, float x, float y, int Width, int Height, int frameNumber, int animDelay, string fileName, ItemDefine item, int itemCountDelay);

	LPItem Update();
	void Render(Camera camera);
	void ContainerDelete();
	float GetPosX();
	Box ToBox();

	virtual ~Container();
};

