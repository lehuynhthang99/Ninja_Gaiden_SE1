#pragma once
class DuckState;
typedef class DuckState* LPDuckState;

#include "State.h"
class DuckState : public State
{
public:
	DuckState();
	~DuckState();
	DuckState(int beginSprite, int EndSprite);

	int HandleInput(StateInfo * info);
	void UpdateVelocity(LPSprite sprite);
	void UpdateStatus(LPSprite sprite);
	void UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu);
	Box ToBox(LPSprite sprite);
};

