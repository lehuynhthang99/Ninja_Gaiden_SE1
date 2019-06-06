#pragma once
#include <limits>

struct Box
{
	float x, y;
	float width, height;
	float vx, vy;
};

float SweptAABB(Box box1, Box box2, float &normal_x, float &normal_y);
bool OverlappedBox(Box box1, Box box2);

