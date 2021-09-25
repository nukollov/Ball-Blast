#pragma once
#include "Object.h"

using namespace sf;

class Gun : public Object
{
public:

	void draw();
	void coordinate_recount(bool right);

	Gun(int digx, int digy, int sp, Sprite a);
};

