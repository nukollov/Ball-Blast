#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;

int Object::getx()
{
	return x;
}

int Object::gety()
{
	return y;
}

bool Object::getlife()
{
	return life;
}

Sprite Object::getsprite()
{
	return sprite;
}

void Object::putx(int digit)
{
	x = digit;
}

void Object::puty(int digit)
{
	y = digit;
}

void Object::putlife(bool a)
{
	life = a;
}


Object::Object(int digx, int digy, int sp, Sprite a)
{
	x = digx;
	y = digy;
	sprite = a;
	speed = sp;
	life = true;
}
