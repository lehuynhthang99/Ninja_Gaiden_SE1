#include "Bird_stage1.h"



Bird_stage1::Bird_stage1()
{
}

Bird_stage1::Bird_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName)
	:Enemy(Path, x, y, Width, Height, frameNumber, animDelay, fileName)
{
	_type = BIRD_stage1;
	sprite.FlipX = 1;
	_vx = _vy = 0;
	_speedX = -0.025;
	_directionX = -1;
}

void Bird_stage1::UpdateVelocity(Ryu* ryu)
{
	float tmpX, tmpY;
	Box tmpBox = ryu->ToBox();
	tmpX = tmpBox.x + 8 - sprite._X;
	tmpY = tmpBox.y - tmpBox.height - sprite._Y;
	float tmpfloat = sqrt(tmpX*tmpX + tmpY*tmpY);
	tmpX /= tmpfloat;
	tmpY /= tmpfloat;

	if (fabs(tmpX*tmpfloat) >= 25)
		_vy = tmpY;

	tmpfloat = _speedX;
	_vx = _speedX;
	if (tmpX <= 0)
	{
		/*if (_speedX <= 0)
			_speedX -= 0.01;
		else _speedX -= 0.01;*/
		_speedX -= 0.01;
	}
	else 
	{
		/*if (_speedX >= 0)
			_speedX += 0.01;
		else _speedX += 0.01;*/
		_speedX += 0.01;
	}
		//_speedX += 0.02;
	if (_speedX > BIRD_STAGE1_MAXSPEED)
		_speedX = BIRD_STAGE1_MAXSPEED;
	if (_speedX < -BIRD_STAGE1_MAXSPEED)
		_speedX = -BIRD_STAGE1_MAXSPEED;
	
	if (_speedX <= 0)
		sprite.FlipX = -1;
	else sprite.FlipX = 1;
	/*if (tmpX > 0)
		_speed += 0.025;
	else if (tmpX < 0)
		_speed -= 0.025;
	
	if (_speed < 0)
	{
		if (tmpX < 0)
		{
			if (fabs(_speed) >= BIRD_STAGE1_MAXSPEED)

			_vx = fabs(_speed) * tmpX;
			_vy = fabs(_speed) * tmpY;
		} 
		else
		{
			_speed += 0.05;
			_vx -= 0.015;
			_vy += 0.015;
		}
	}
	else if (_speed > 0)
	{
		if (tmpX > 0)
		{
			_vx = fabs(_speed) * tmpX;
			_vy = fabs(_speed) * tmpY;
		}
		else
		{
			_speed -= 0.05;
			_vx += 0.015;
			_vy += 0.015;
		}
	}*/

	/*tmpfloat = _speed;
	if (tmpX > 0)
		_speed += 0.025;
	else if (tmpX < 0)
		_speed -= 0.025;

	if (_speed > BIRD_STAGE1_MAXSPEED)
		_speed = BIRD_STAGE1_MAXSPEED;
	else if (_speed < -BIRD_STAGE1_MAXSPEED)
		_speed = -BIRD_STAGE1_MAXSPEED;
	if (fabs(_speed) != BIRD_STAGE1_MAXSPEED)
	{
		_vx = fabs(_speed) * tmpX;
		_vy = fabs(_speed) * tmpY;
	} 
	else
	{
		if (_speed < 0 && _vx >= 0)
			_speed += 0.025;
		else if (_speed > 0 && _vx <= 0)
			_speed -= 0.025;
	}
		
	if (tmpfloat*_speed <= 0)
		sprite.FlipX *= -1;*/
}

void Bird_stage1::UpdatePosition()
{
	sprite._X += _vx;
	sprite._Y += _vy;
}

void Bird_stage1::UpdateFrame()
{
	_curSprite = (int)(_countDelay / (sprite._animDelay*1.75));
	_countDelay++;
	if ((int)(_countDelay / (sprite._animDelay*1.75)) >= 2)
		_countDelay = 0;
}

LPEnemy Bird_stage1::Update(Ryu* ryu)
{
	if (ryu->GetStateType() != ATTACK_state)
		_isAttacked = false;
	if (_HP == 0)
	{
		_HP--;
		_died = 20;
	}
	if (_died != -1)
	{
		Enemy::DiedUpdate();
		return NULL;
	}
	UpdateVelocity(ryu);
	UpdatePosition();
	UpdateFrame();
	return NULL;
}

Box Bird_stage1::ToBox()
{
	return Enemy::ToBox();
}


void Bird_stage1::Render(Camera camera)
{
	if (_died == -1)
	{
		Enemy::Render(camera);
		return;
	}
	else Enemy::DiedRender(camera);
}

Bird_stage1::~Bird_stage1()
{
}
