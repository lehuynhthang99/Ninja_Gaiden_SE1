#pragma once
#include "State.h"
class ClimbState : public State
{
protected:
	int _rangeYStart, _rangeYEnd;
	StateDefine _changeTo;
public:
	ClimbState();
	~ClimbState();

	ClimbState(int beginSprite, int EndSprite, int rangeYStart, int rangeYEnd);

	int HandleInput(StateInfo * info);
	void UpdateVelocity(LPSprite sprite);
	void UpdateStatus(LPSprite sprite);
	void UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu);
};

