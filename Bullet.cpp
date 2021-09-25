#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Gun.h"

using namespace sf;

void Bullet::draw()
{
	sprite.setPosition(x, y);
}

void Bullet::set_draw_bullet(bool a)
{
	draw_bullet = a;
}

bool Bullet::get_draw_bullet()
{
	return draw_bullet;
}

void Bullet::coordinate_recount(Gun gun)
{
	if (y - speed < 0)
	{
		x = gun.getx() + 30;
		y = 610;
		draw_bullet = true;
	}
	else
	{
		y -= speed;
	}
}

Bullet::Bullet(int digx, int digy, int sp, Sprite a) : Object(digx, digy, sp, a)
{
}