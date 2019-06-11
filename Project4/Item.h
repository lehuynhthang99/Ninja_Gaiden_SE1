#pragma once

#include "Sprite.h"
#include "Collision.h"

using namespace std;

enum ItemDefine
{
	NullSkill = 0,
	LiveUp = 1,
	PtsBonus_A = 2,
	PtsBonus_B = 3,
	HPRecover = 4,
	MPRecover_A = 5,
	MPRecover_B = 6,
	Dart_A = 7,
	Dart_B = 8,
	TimeStop = 9,
};

class Item;
typedef Item* LPItem;

class Item
{
protected:
	Sprite sprite;
	float _countDelay;
public:
	int _activate;
	ItemDefine _id;
	bool _died;
	Item();
	Item(ItemDefine id, float x, float y, int CountDelay);

	void Update();
	void ItemDelete();
	void Render(Camera camera);
	Box ToBox();

	float GetPosX();

	virtual ~Item();
};