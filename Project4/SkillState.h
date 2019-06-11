#pragma once

class SkillState;
typedef class SkillState* LPSkillState;

#include "State.h"



class SkillState : public State
{
protected:
	StateDefine _prevType, changeTo;
	bool _endState;
public:
	SkillState();
	~SkillState();
	SkillState(int beginSprite, int EndSprite, StateDefine prevState, float vx = 0, float vy = 0);

	int HandleInput(StateInfo * info);
	void UpdateVelocity(LPSprite sprite);
	void UpdateStatus(LPSprite sprite);
	void UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu);
};

