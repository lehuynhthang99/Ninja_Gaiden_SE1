#pragma once
class StunState;
typedef class StunState* LPStunState;

#include "State.h"
class StunState : public State
{
protected:
	StateDefine changeTo;
public:
	StunState();
	~StunState();
	StunState(int beginSprite, int EndSprite, int FlipX);

	int HandleInput(StateInfo *info);
	void UpdateVelocity(LPSprite sprite);
	void UpdateStatus(LPSprite sprite);
	void UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu);
};

