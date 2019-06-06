#pragma once
class JumpState;
typedef class JumpState* LPJumpState;

#include "State.h"
class JumpState: public State
{
protected:
	StateDefine changeTo;
	Wall* _climbWall;
public:
	JumpState();
	~JumpState();
	JumpState(int beginSprite, int EndSprite, float vx = 0, float vy = FLYING_TIME);

	int HandleInput(StateInfo *info);
	void UpdateVelocity(LPSprite sprite);
	void UpdateStatus(LPSprite sprite);
	void UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu);

};

