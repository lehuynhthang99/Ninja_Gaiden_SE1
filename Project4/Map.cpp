#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
}

Map::Map(string mapPath, string imagePath, int x, int y, int Width, int Height, int frameNumber, int animDelay):
	Sprite(imagePath, x, y, Width, Height, frameNumber, animDelay)
{
	ifstream map;
	map.open(mapPath);
	map >> rows >> cols;
	bitmap = new int*[rows];
	for (int i = 0; i < rows; i++)
		bitmap[i] = new int[cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			map >> bitmap[i][j];
	numberBitmapPerRows = SCREEN_WIDTH / (_Width*SCALEX) + 2;
	map.close();
}

void Map::KillSprite()
{
	Sprite::KillSprite();
	for (int i = 0; i < rows; i++)
		if (bitmap[i])
			delete[]bitmap[i];
	if (bitmap)
		delete[]bitmap;
}

void Map::Render(Camera camera)
{
	/*D3DXMatrixScaling(&_renderMatrix, SCALEX, SCALEY, 1);*/
	/*D3DXMatrixIdentity(&_renderMatrix);
	D3DXMATRIX tmp;*/
	int start = camera._X / _Width;
	for (int i = 0; i < rows; i++)
		for (int j = start; j < start + numberBitmapPerRows; j++)
		{
			int x = j * _Width;
			int y = _Height * (rows - i);

			D3DXMatrixIdentity(&_renderMatrix);
			D3DXMATRIX tmp;
			D3DXVECTOR3 position(x,y,0);
			position = camera.WorldToView(position);

			D3DXMatrixTranslation(&tmp, position.x, position.y, 0.0f);
			_renderMatrix *= tmp;
			D3DXMatrixScaling(&tmp, SCALEX, SCALEY, 1);
			_renderMatrix *= tmp;

			rect.top = 0;
			rect.left = _Width * bitmap[i][j];
			rect.right = rect.left + _Width;
			rect.bottom = rect.top + _Height;
			spritehandler->SetTransform(&_renderMatrix);
			spritehandler->Draw(
				_Image,
				&rect,
				NULL,
				&position,
				D3DCOLOR_XRGB(255, 255, 255)
			);
		}
}
