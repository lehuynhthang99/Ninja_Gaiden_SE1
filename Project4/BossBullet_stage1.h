#pragma once

#include "Enemy.h"

#define BOSS_BULLET_SPEED 0.5f

class BossBullet_stage1 : public Enemy
{
public:
	BossBullet_stage1();
	BossBullet_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
		float FlipX);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu);

	Box ToBox();

	void Render(Camera camera);
	~BossBullet_stage1();
};

