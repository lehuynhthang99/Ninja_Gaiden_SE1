#pragma once

#include "Enemy.h"
#include "BossBullet_stage1.h"

#define BOSS_FLYING_TIME 3.6f

class Boss_stage1 : public Enemy
{
protected:
	bool _bulletAdd, _jump, _shoot;
	int _countBullet, _startPos;
	string _Path, _fileName;
	Sprite diedSprite;
	Tiles diedTiles;
	int diedcurSprite;
public:
	Boss_stage1();
	Boss_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName);

	void UpdateVelocity(Ryu* ryu);
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu);
	void DiedUpdate();
	void EnemyDelete();
	void DiedRender(Camera camera);


	Box ToBox();

	void Render(Camera camera);
	~Boss_stage1();
};

