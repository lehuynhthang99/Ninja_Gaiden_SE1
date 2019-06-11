#pragma once
#include "Skill.h"
class DartB : public Skill
{
protected:
	float _speed, _targetX, _targetY;
public:
	DartB();
	DartB(string Path, float x, float y, int Width, int Height, int frameNumber, float LifeSpan, string FileName, LPSprite RyuSprite);
	~DartB();

	void UpdateVelocity(LPSprite RyuSprite);
	void Update(LPSprite RyuSprite);
};