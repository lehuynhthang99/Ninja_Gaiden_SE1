#pragma once
class AttackState;
typedef class AttackState* LPAttackState;

#include "State.h"

class AttackState : public State
{
protected:
	//int _flyingTime;
	StateDefine _prevType, changeTo;
	Box _SwordBox;
	bool _endState;

public:
	AttackState();
	~AttackState();
	AttackState(int beginSprite, int EndSprite, StateDefine prevState, float vx = 0, float vy = 0);

	int HandleInput(StateInfo * info);
	void UpdateVelocity(LPSprite sprite);
	void UpdateStatus(LPSprite sprite);
	void UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu);
	Box ToBoxSword(LPSprite sprite);
	Box ToBox(LPSprite sprite);
};

