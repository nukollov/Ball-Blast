#include <SFML/Graphics.hpp>
#include "Ball.h"

using namespace sf;

void Ball::set_hp()
{
	healh_point--;
}

int Ball::get_hp()
{
	return healh_point;
}

void Ball::put_hp(int a)
{
	healh_point = a;
}

void Ball::new_ball(int nx, int ny, int hp, int s, bool u, bool r)
{
	x = nx,
	y = ny;
	healh_point = hp;
	speed = s;
	up = u;
	right = r;
}

void Ball::coordinate_recount()
{

	//  ���� ��� ��������� ������
	if (right)
	{
		if (x + speed > 600)
		{
			x = 600;
			right = false;
		}
		else
		{
			x += speed;
		}
	}
	//  ���� ��� ��������� �����
	else
	{
		if (x - speed < 0)
		{
			x = 0;
			right = true;
		}
		else
		{
			x -= speed;
		}
	}

	//  ���� ��� ��������� �����
	if (up)
	{
		if (y - speed < 50)
		{
			up = false;
		}
		else
		{
			y -= speed;
		}
	}
	//  ���� ��� ��������� ����
	else
	{
		if (y + speed > 600)
		{
			up = true;
			y = 600;
		}
		else
		{
			y += speed;
		}
	}
}

Ball::Ball(int digx, int digy, int sp, int hp, Sprite a) : Object(digx, digy, sp, a)
{
	healh_point = hp;
	up = false;
	right = true;
}
