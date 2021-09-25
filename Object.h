#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Object
{
protected:
	int x;
	int y;
	int speed;
	bool life;
	Sprite sprite;
public:

	virtual void draw() = 0;

	//  �������
	int getx();
	int gety();
	bool getlife();
	Sprite getsprite();

	//  �������
	void putx(int digit);
	void puty(int digit);
	void putlife(bool a);

	//  ������������
	Object(int digx, int digy, int sp, Sprite a);
};

