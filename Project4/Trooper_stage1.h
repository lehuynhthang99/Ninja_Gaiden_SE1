#pragma once

#include "Enemy.h"

#define TROOPER_STAGE1_SPEED 1.0f

class Trooper_stage1 : public Enemy
{
public:
	Trooper_stage1();
	Trooper_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
		float rangeXstart, float rangeXend);


	void UpdateVelocity();
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu = NULL);

	Box ToBox();

	void Render(Camera camera);

	~Trooper_stage1();
};

