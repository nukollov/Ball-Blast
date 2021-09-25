#pragma once
#include "Object.h"
class Ball : public Object
{
private:
	int healh_point;		//  кол-во жизней шарика
	bool up, right;			//  флажки перемещения шарика

public:

	void set_hp();
	int get_hp();
	void put_hp(int a);

	void new_ball(int nx, int ny, int hp, int s, bool u, bool r);

	void draw()
	{
		sprite.setPosition(x, y);
	}

	void coordinate_recount();
	
	Ball(int digx, int digy, int sp, int hp, sf::Sprite a);

};

