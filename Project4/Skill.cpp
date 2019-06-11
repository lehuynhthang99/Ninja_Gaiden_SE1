#include "Skill.h"



Skill::Skill()
{
}

Skill::Skill(string Path, float x, float y, int Width, int Height, int frameNumber, float LifeSpan, string fileName)
{
	sprite = Sprite(Path, x, y, Width, Height, frameNumber, 10);
	tiles = Tiles(fileName, frameNumber);
	_lifeSpan = LifeSpan;
	_vx = _vy = 0;
	_countDelay = 0;
	_curSprite = 0;
}


void Skill::SkillDelete()
{
	sprite.KillSprite();
}

void Skill::Render(Camera camera)
{
	sprite.Render(camera, tiles.getRectLocation(_curSprite));
}

Box Skill::ToBox()
{
	Box tmp;
	tmp.vx = _vx;
	tmp.vy = _vy;
	tmp.x = sprite._X - sprite.GetWidth() / 2.0f;
	tmp.y = sprite._Y + sprite.GetHeight();
	tmp.width = sprite.GetWidth();
	tmp.height = sprite.GetHeight();
	return tmp;
}

Skill::~Skill()
{
}
