#pragma once

#include "Enemy.h"
#include "SniperBullet_stage1.h"

class Sniper_stage1 : public Enemy
{
protected:
	bool _bulletAdd;
	string _Path, _fileName;
	D3DXVECTOR3 _center;
public:
	Sniper_stage1();
	Sniper_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName);

	void UpdateVelocity(Ryu* ryu);
	void UpdatePosition();
	void UpdateFrame();
	LPEnemy Update(Ryu* ryu);

	Box ToBox();

	void Render(Camera camera);
	~Sniper_stage1();
};

