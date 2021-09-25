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

	//  геттеры
	int getx();
	int gety();
	bool getlife();
	Sprite getsprite();

	//  сеттеры
	void putx(int digit);
	void puty(int digit);
	void putlife(bool a);

	//  конструкторы
	Object(int digx, int digy, int sp, Sprite a);
};

