#pragma once

#include "Wall.h"
//#include "Enemy.h"
#include <vector>
#include <algorithm>
#include "Sprite.h"

#define CELL_SIZE 44
class Wall;
//class Enemy;

using namespace std;

class Grid
{
protected:
	vector<Wall*> **Wall_Cells;
	//vector<Enemy*> **Enemy_Cells;
public:
	int _cellRows, _cellCols;

	Grid();
	virtual ~Grid();

	void GridClear();

	void Add(Wall* wall);
	//void Add(Enemy* enemy);

	void Output();

	vector<Wall*> WallOut(RECT rect);

};