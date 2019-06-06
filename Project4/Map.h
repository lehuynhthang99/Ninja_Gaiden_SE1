#pragma once

#include "Sprite.h"
#include <fstream>

class Map: public Sprite
{
protected:
	int **bitmap;
	int rows, cols;
	int numberBitmapPerRows;
public:
	Map();
	~Map();
	Map(string mapPath, string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay);

	void KillSprite();
	void Render(Camera camera);
};

