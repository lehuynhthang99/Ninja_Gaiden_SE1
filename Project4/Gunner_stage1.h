#pragma once

#include "Enemy.h"
#include "GunnerBullet_stage1.h"

#define GUNNER_STAGE1_SPEED 0.2f

class Gunner_stage1 : public Enemy
{
protected:
	bool _bulletAdd;
	string _Path, _fileName;
public:
	Gunner_stage1();
	Gunner_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
		float rangeXstart, float rangeXend);

	void UpdateVelocity(Ryu* ryu);
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu);

	Box ToBox();

	void Render(Camera camera);
	~Gunner_stage1();
};

