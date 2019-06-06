#pragma once
#include <fstream>
#include "Grid.h"
#include "Collision.h"
#include "Sprite.h"
class Grid;

class Wall
{
protected:
	RECT wall;
public:
	bool _left, _right;
	friend class Grid;
	Wall();
	Wall(RECT rect, bool left, bool right);
	virtual ~Wall();

	Box ToBox();
};

