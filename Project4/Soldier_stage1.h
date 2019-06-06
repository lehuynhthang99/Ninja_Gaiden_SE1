#pragma once

#include "Enemy.h"

#define SOLDIER_STAGE1_SPEED 0.3f

class Soldier_stage1 : public Enemy
{
public:
	Soldier_stage1();
	Soldier_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
		float rangeXstart, float rangeXend);

	void UpdateVelocity();
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu = NULL);

	Box ToBox();

	void Render(Camera camera);

	~Soldier_stage1();
};

