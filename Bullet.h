#pragma once
#include "Object.h"
#include"Gun.h"
class Bullet : public Object
{
private:
	bool draw_bullet;	//  флаг для отрисовки пули
public:
	
	void set_draw_bullet(bool a);
	bool get_draw_bullet();
	void draw();
	void coordinate_recount(Gun gun);

	Bullet(int digx, int digy, int sp, Sprite a);
};

