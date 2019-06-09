#pragma once

enum EnemyDefine
{
	SOLDIER_stage1 = 1,
	BIRD_stage1 = 2,
	WIZARD_stage1 = 3,
	WIZARDBULLET_stage1 = -3,
	GUNNER_stage1 = 4,
	GUNNERBULLET_stage1 = -4,
	SNIPER_stage1 = 5,
	SNIPERBULLET_stage1 = -5,
	BOSS_stage1 = 6,
	BOSSBULLET_stage1 = -6,
	CAT_stage1 = 7,
	TROOPER_stage1 = 8,
};
class Enemy;
typedef class Enemy* LPEnemy;

class Ryu;
#include "Sprite.h"
#include "Tiles.h"
#include "Ryu.h"

class Enemy
{
protected:
	Tiles tiles;
	Sprite sprite;
	int _beginSprite, _endSprite, _curSprite;
	float _countDelay;
	float _vx, _vy;
	float _rangeXstart, _rangeXend;
	
public:
	int _score;
	bool _isAttacked;
	int _died;
	EnemyDefine _type;
	int _HP;

	friend class Grid;
	Enemy();
	Enemy(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName);

	virtual void UpdateVelocity();
	virtual void UpdatePosition();
	virtual void UpdateFrame();
	virtual LPEnemy Update(Ryu* ryu = NULL) = 0;

	virtual float GetPosX();

	virtual void Render(Camera camera);

	virtual Box ToBox();

	virtual ~Enemy();

	virtual void EnemyDelete();

	virtual void DiedUpdate();

	virtual void DiedRender(Camera camera);
};

