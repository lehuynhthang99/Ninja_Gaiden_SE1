#pragma once

#include "Enemy.h"

#define BIRD_STAGE1_MAXSPEED 1.25f

class Bird_stage1 : public Enemy
{
protected:
	
	float _speedX, _directionX;
public:
	Bird_stage1();
	Bird_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName);
	void UpdateVelocity(Ryu* ryu);
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu);

	Box ToBox();

	void Render(Camera camera);
	~Bird_stage1();
};

