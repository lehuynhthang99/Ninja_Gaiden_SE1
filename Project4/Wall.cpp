#include "Wall.h"



Wall::Wall()
{
}

Wall::Wall(RECT rect, bool left, bool right)
{
	wall = rect;
	_left = left;
	_right = right;
}


Wall::~Wall()
{
}

Box Wall::ToBox()
{
	Box result;
	result.x = wall.left;
	result.y = wall.top;
	result.width = wall.right - wall.left;
	result.height = wall.top - wall.bottom;
	result.vx = result.vy = 0;
	return result;
}
