#pragma once

#include "Enemy.h"

#define GUNNER_BULLET_SPEED 0.5f

class GunnerBullet_stage1 : public Enemy
{
public:
	GunnerBullet_stage1();
	GunnerBullet_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
		float FlipX);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu);

	Box ToBox();

	void Render(Camera camera);
	~GunnerBullet_stage1();
};

