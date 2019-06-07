#include "Sprite.h"



Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

Sprite::Sprite(string Path, float x, float y, int Width, int Height, int frameNumber, int animDelay)
{
	_Image = LoadTexture(Path, D3DCOLOR_XRGB(255, 0, 255));
	_X = x;
	_Y = y;
	_Width = Width;
	_Height = Height;
	_frameNumber = frameNumber;
	_curFrame = 0;
	_animDelay = animDelay;
	_countDelay = 0;
	rect.top = rect.left = 0;
	rect.right = rect.left + Width;
	rect.bottom = rect.top + Height;
	FlipX = FlipY = 1;
}

void Sprite::Render(Camera camera)
{
	D3DXMatrixIdentity(&_renderMatrix);
	D3DXMATRIX tmp;
	D3DXVECTOR3 position((float)_X, (float)_Y, 0);
	position = camera.WorldToView(position);

	//Flip
	D3DXMatrixScaling(&tmp, FlipX, 1, 1);
	_renderMatrix *= tmp;

	//ZOOM for View
	//Translate the sprite
	D3DXMatrixTranslation(&tmp, position.x, position.y, 0.0f);
	_renderMatrix *= tmp;

	// Scale the sprite.
	D3DXMatrixScaling(&tmp, SCALE, SCALE, SCALE);
	_renderMatrix *= tmp;

	
	
	spritehandler->SetTransform(&_renderMatrix);
	D3DXVECTOR3 center = D3DXVECTOR3((rect.right-rect.left)/2.0f, (rect.top - rect.bottom) / 2.0f, 0);
	spritehandler->Draw(
		_Image,
		&rect,
		&center,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void Sprite::Render(Camera camera, RECT renderRect)
{
	D3DXMatrixIdentity(&_renderMatrix);
	D3DXMATRIX tmp;
	D3DXVECTOR3 position((float)_X, (float)_Y, 0);
	position = camera.WorldToView(position);
	//Flip
	D3DXMatrixScaling(&tmp, FlipX, FlipY, 1);
	_renderMatrix *= tmp;

	//ZOOM for View
	//Translate the sprite
	D3DXMatrixTranslation(&tmp, position.x, position.y, 0.0f);
	_renderMatrix *= tmp;

	// Scale the sprite.
	D3DXMatrixScaling(&tmp, SCALE, SCALE, SCALE);
	_renderMatrix *= tmp;

	D3DXVECTOR3 center = D3DXVECTOR3((renderRect.right - renderRect.left) / 2.0f, (renderRect.bottom - renderRect.top), 0);
	spritehandler->SetTransform(&_renderMatrix);
	spritehandler->Draw(
		_Image,
		&renderRect,
		&center,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void Sprite::Render(Camera camera, RECT renderRect, D3DXVECTOR3 center)
{
	D3DXMatrixIdentity(&_renderMatrix);
	D3DXMATRIX tmp;
	D3DXVECTOR3 position((float)_X, (float)_Y, 0);
	position = camera.WorldToView(position);
	//Flip
	D3DXMatrixScaling(&tmp, FlipX, FlipY, 1);
	_renderMatrix *= tmp;

	//ZOOM for View
	//Translate the sprite
	D3DXMatrixTranslation(&tmp, position.x, position.y, 0.0f);
	_renderMatrix *= tmp;

	// Scale the sprite.
	D3DXMatrixScaling(&tmp, SCALE, SCALE, SCALE);
	_renderMatrix *= tmp;

	spritehandler->SetTransform(&_renderMatrix);
	spritehandler->Draw(
		_Image,
		&renderRect,
		&center,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void Sprite::KillSprite()
{
	if (_Image != NULL)
		_Image->Release();
}

int Sprite::GetWidth()
{
	return _Width;
}

int Sprite::GetHeight()
{
	return _Height;
}

Box Sprite::ToBox()
{
	Box tmp;
	tmp.x = (float)_X;
	tmp.y = (float)_Y;
	tmp.vx = tmp.vy = 0;
	tmp.width = (float)_Width;
	tmp.height = (float)_Height;
	return tmp;
}

void Sprite::RectUpdate()
{
	D3DXVECTOR2 pos;
	pos.x = (float)_curFrame * _Width;
	pos.y = (float)_curFrame * _Height;
	rect.top = (long)pos.y;
	rect.left = (long)pos.x;
	rect.bottom = rect.top + _Height;
	rect.right = rect.left + _Width;
	_countDelay++;
	if (_countDelay == _animDelay)
	{
		_countDelay = 0;
		_curFrame++;
		if (_curFrame == _frameNumber)
			_curFrame = 0;
	}
}
