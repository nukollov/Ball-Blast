#include <SFML/Graphics.hpp>
#include "Gun.h"


using namespace sf;

void Gun::draw()
{
	this->sprite.setPosition(x, y);
}

void Gun::coordinate_recount(bool right)
{
	if (right)
	{
		if (x + speed > 620)
		{
			x = 620;
		}
		else
		{
			x += speed;
		}
	}
	else
	{
		if (x - speed < 0)
		{
			x = 0;
		}
		else
		{
			x -= speed;
		}
	}
}

Gun::Gun(int digx, int digy, int sp, Sprite a) : Object(digx, digy, sp, a)
{
}