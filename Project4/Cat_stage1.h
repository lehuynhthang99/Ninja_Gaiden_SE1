#pragma once

#include "Enemy.h"
#define CAT_STAGE1_SPEED 1.0f

class Cat_stage1 : public Enemy
{
public:
	Cat_stage1();
	Cat_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
		float rangeXstart, float rangeXend);


	void UpdateVelocity();
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu = NULL);

	Box ToBox();

	void Render(Camera camera);

	~Cat_stage1();
};

