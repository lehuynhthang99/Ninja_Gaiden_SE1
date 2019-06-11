#pragma once

class Sprite;
typedef class Sprite* LPSprite;

#include <d3d9.h>
#include <d3dx9.h>
#include "dxgraphics.h"
#include "dxinput.h"
#include "Collision.h"
#include "Camera.h"
#include "debug.h"


class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 _Image;
	int _Width, _Height;
	int _curFrame;
	D3DXMATRIX _renderMatrix;

public:
	int _frameNumber;
	RECT rect;
	float _X, _Y;
	float FlipX;
	float FlipY;
	int _animDelay, _countDelay;
	
	Sprite();
	~Sprite();
	Sprite(string Path, float x, float y, int Width, int Height, int frameNumber, int animDelay);

	void Render(Camera camera);
	void Render(Camera camera, RECT renderRect);
	void Render(Camera camera, RECT renderRect, D3DXVECTOR3 center);
	virtual void KillSprite();
	int GetWidth();
	int GetHeight();
	Box ToBox();
	virtual void RectUpdate();
};

