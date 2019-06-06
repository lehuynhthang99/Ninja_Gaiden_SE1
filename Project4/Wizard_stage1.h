#pragma once

#include "Enemy.h"
#include "WizardBullet_stage1.h"

#define WIZARD_STAGE1_SPEED 0.2f

class Wizard_stage1 : public Enemy
{
protected: 
	bool _bulletAdd;
	string _Path, _fileName;
public:
	Wizard_stage1();
	Wizard_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
		float rangeXstart, float rangeXend);

	void UpdateVelocity(Ryu* ryu);
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu);

	Box ToBox();

	void Render(Camera camera);

	~Wizard_stage1();
};

