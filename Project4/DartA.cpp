#include "DartA.h"



DartA::DartA()
{
}

DartA::DartA(string Path, float x, float y, int Width, int Height, int frameNumber, float LifeSpan, string fileName, LPSprite RyuSprite)
	:Skill(Path, x, y, Width, Height, frameNumber, LifeSpan, fileName)
{
	_type = DartA_skill;
	_vx = 1.5f*RyuSprite->FlipX;
	_vy = 0;
}


DartA::~DartA()
{
}

void DartA::UpdateVelocity(LPSprite RyuSprite)
{
}

void DartA::Update(LPSprite RyuSprite)
{
	_lifeSpan -= 0.01f;
	sprite._X += _vx;
	sprite._Y += _vy;
	_countDelay++;
	if (_countDelay >= 10)
	{
		_countDelay = 0;
		_curSprite++;
		if (_curSprite >= sprite._frameNumber)
			_curSprite = 0;
	}
}
