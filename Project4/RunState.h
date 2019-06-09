#pragma once
class RunState;
typedef class RunState* LPRunState;

#define RYU_SPEED 0.8f

#include "State.h"
class RunState : public State
{
protected:
	StateDefine changeTo = NONE;
public:
	RunState();
	~RunState();
	RunState(int beginSprite, int EndSprite);

	int HandleInput(StateInfo *info);
	void UpdateVelocity(LPSprite sprite);
	void UpdateStatus(LPSprite sprite);
	void UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu);
};

