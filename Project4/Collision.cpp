#include "Collision.h"

float SweptAABB(Box box1, Box box2, float &normal_x, float &normal_y)
{
	box1.vx -= box2.vx;
	box1.vy -= box2.vy;
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	//distance
	if (box1.vx > 0)
	{
		xInvEntry = box2.x - (box1.x + box1.width);
		xInvExit = (box2.x + box2.width) - box1.x;
	}
	else
	{
		xInvEntry = (box2.x + box2.width) - box1.x;
		xInvExit = box2.x - (box1.x + box1.width);
	}

	if (box1.vy > 0)
	{	
		yInvEntry = box2.y - box2.height - box1.y;
		yInvExit = box2.y - (box1.y - box1.height);
	}
	else
	{
		yInvEntry = box2.y - (box1.y - box1.height);
		yInvExit = box2.y - box2.height - box1.y;
	}

	//time of collision and leaving
	float xEntry, yEntry;
	float xExit, yExit;

	if (box1.vx == 0)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / box1.vx;
		xExit = xInvExit / box1.vx;
	}

	if (box1.vy == 0)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / box1.vy;
		yExit = yInvExit / box1.vy;
	}

	//earliest and latest times of collision
	float entryTime = fmax(xEntry, yEntry);
	float exitTime = fmin(xExit, yExit);

	//no collision?
	if (entryTime > exitTime || (xEntry<0 && yEntry<0) || xEntry>1.0f || yEntry>1.0f || 
		(box1.vx == 0 && fabs(xInvEntry + xInvExit) > box1.width + box2.width) || 
		(box1.vy == 0 && fabs(yInvEntry + yInvExit) > box1.height + box2.height))
	{
		normal_x = 0;
		normal_y = 0;
		return 1.0f;
	}
	else
	{
		//which surface is collided
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0)
			{
				//right
				normal_x = 1.0f;
				normal_y = 0;
			}
			else if (xInvEntry > 0)
			{
				//left
				normal_x = -1.0f;
				normal_y = 0;
			}
			else
			{
				if (box1.vx > 0)
				{
					normal_x = -1.0f;
					normal_y = 0;
				}
				else
				{
					normal_x = 1.0f;
					normal_y = 0;
				}
			}
		}
		else
		{
			if (yInvEntry < 0)
			{
				//Top
				normal_x = 0;
				normal_y = 1.0f;
			}
			else if (yInvEntry > 0)
			{
				//Bottom
				normal_x = 0;
				normal_y = -1.0f;
			}
			else
			{
				if (box1.vy > 0)
				{
					normal_x = 0;
					normal_y = -1.0f;
				}
				else
				{
					normal_x = 0;
					normal_y = 1.0f;
				}
			}
		}
		return entryTime;
	}
}

bool OverlappedBox(Box box1, Box box2)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	//distance
	if (box1.vx > 0)
	{
		xInvEntry = box2.x - (box1.x + box1.width);
		xInvExit = (box2.x + box2.width) - box1.x;
	}
	else
	{
		xInvEntry = (box2.x + box2.width) - box1.x;
		xInvExit = box2.x - (box1.x + box1.width);
	}

	if (box1.vy > 0)
	{
		yInvEntry = box2.y - box2.height - box1.y;
		yInvExit = box2.y - (box1.y - box1.height);
	}
	else
	{
		yInvEntry = box2.y - (box1.y - box1.height);
		yInvExit = box2.y - box2.height - box1.y;
	}
	if ((fabs(xInvEntry + xInvExit) <= box1.width + box2.width) && (fabs(yInvEntry + yInvExit) <= box1.height + box2.height))
		return true;
	return false;
}
