#include "DartB.h"



DartB::DartB()
{
}

DartB::DartB(string Path, float x, float y, int Width, int Height, int frameNumber, float LifeSpan, string fileName, LPSprite RyuSprite)
	:Skill(Path, x, y, Width, Height, frameNumber, LifeSpan, fileName)
{
	_type = DartB_skill;
	_speed = RyuSprite->FlipX * 3.0f;
	_targetX = RyuSprite->FlipX;
	_targetY = 0;
}


DartB::~DartB()
{
}

void DartB::UpdateVelocity(LPSprite RyuSprite)
{
	float tmpfloat = _speed;
	if (RyuSprite->_X > sprite._X)
		_speed += 0.08f;
	else _speed -= 0.08f;
	if (_speed > 3.0f)
		_speed = 3.0f;
	if (_speed < -3.0f)
		_speed = -3.0f;
	if (tmpfloat != 0 && tmpfloat*_speed <= 0.0f)
	{
		_targetX = RyuSprite->_X - sprite._X;
		_targetY = RyuSprite->_Y - sprite._Y;
		tmpfloat = sqrt(_targetX*_targetX + _targetY * _targetY);
		_targetX /= tmpfloat;
		_targetY /= tmpfloat;
	}
	_vx = abs(_speed)*_targetX;
	_vy = abs(_speed)*_targetY;
}

void DartB::Update(LPSprite RyuSprite)
{
	UpdateVelocity(RyuSprite);
	_lifeSpan -= 0.01f;
	sprite._X += _vx;
	sprite._Y += _vy;
	_countDelay++;
	if (_countDelay >= 10)
	{
		_countDelay = 0;
		_curSprite++;
		if (_curSprite >= sprite._frameNumber)
			_curSprite = 0;
	}
}
