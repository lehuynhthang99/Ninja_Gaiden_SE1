#pragma once
class StandState;
typedef class StandState* LPStandState;

#include "State.h"

class StandState : public State
{
public:
	StandState();
	~StandState();
	StandState(int beginSprite, int EndSprite);

	int HandleInput(StateInfo* info);
	void UpdateVelocity(LPSprite sprite);
	void UpdateStatus(LPSprite sprite);
	void UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu);
};

