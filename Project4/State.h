#pragma once
class State;
typedef class State* LPState;


enum StateDefine
{
	NONE = 0,
	STAND_State = 1,
	RUN_State = 2,
	DUCK_State = 3,
	JUMP_state = 4,
	ATTACK_state = 5,
	CLIMB_state = 6,
	STUN_state = 7,
	SKILL_state = 8,
};



#define FLYING_TIME 3.2f

#include <d3d9.h>
#include <d3dx9.h>
#include "dxgraphics.h"
#include "dxinput.h"
#include "Collision.h"
#include "Sprite.h"
#include <string>
#include "debug.h"
#include "Wall.h"

using namespace std;

struct StateInfo
{
	POINT frameToDraw, RangeY;
};

class State
{
public:
	int _beginSprite, _endSprite, _curSprite;
	float _countDelay;
	StateDefine _Type;

	float _vx, _vy;

	float _collisionTime, _normalX, _normalY;

	State();
	virtual ~State();
	State(int beginSprite, int EndSprite);

	virtual int HandleInput(StateInfo* info) = 0;
	virtual void UpdateVelocity(LPSprite sprite);
	virtual void UpdateStatus(LPSprite sprite) = 0;
	virtual void UpdateCollision(LPSprite sprite, Wall* wall, Box Ryu) = 0;
	virtual Box ToBoxSword(LPSprite sprite);
	virtual Box ToBox(LPSprite sprite);
};

