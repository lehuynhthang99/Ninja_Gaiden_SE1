#pragma once

#include "Enemy.h"

#define BULLET_FLYING_TIME 2.0f

class WizardBullet_stage1 : public Enemy
{
protected:
	D3DXVECTOR3 _center;

public:
	WizardBullet_stage1();

	WizardBullet_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
		float FlipX);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu);

	Box ToBox();

	void Render(Camera camera);

	~WizardBullet_stage1();
};

