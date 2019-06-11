#pragma once
#include "Skill.h"
class DartA : public Skill
{
public:
	DartA();
	DartA(string Path, float x, float y, int Width, int Height, int frameNumber, float LifeSpan, string fileName, LPSprite RyuSprite);
	~DartA();

	void UpdateVelocity(LPSprite RyuSprite);
	void Update(LPSprite RyuSprite);
};

