#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Gun.h"
#include "Bullet.h"
#include "Ball.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <fstream>

using namespace std;
using namespace sf;

int game(Font font);							//  функция, начинающая игру
void draw_game_over(Font font, int score);		//  функция, рисующая заставку конца игры
int draw_pause(Font font, int score);			//  функция, рисующая паузу


bool pause = false;		//  флаг паузы
bool f_boom = false;

RenderWindow window;
Image image, image_b, image_f, image_ball;
Texture texture, texture_b, texture_f, texture_ball;
Sprite sprite, sprite_b, sprite_f, sprite_ball;

int main()
{
	window.create(sf::VideoMode(700, 700), "Ball Blast");
	window.setFramerateLimit(60);

	//  загрузка стартового экрана
	Image start_image;
	start_image.loadFromFile("start.png");
	Texture start_texture;
	start_texture.loadFromImage(start_image);
	Sprite start_sprite;
	start_sprite.setTexture(start_texture);
	start_sprite.setPosition(0, 0);

	//  загрузка шрифта
	Font font;
	font.loadFromFile("cour.ttf");

	//  отрисовка стартового экрана
	window.clear();
	window.draw(start_sprite);
	//window.draw(start_text);
	window.display();


	int res;					//  результат игры
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			res = game(font);
		}
		
	}
}

int game(Font font)
{
	int score = 0;			//  очки игрока
	//  подготовка вывода счета игрока
	Text player_points("point: 0", font, 16);
	player_points.setStyle(Text::Bold);
	player_points.setPosition(10, 10);

	//  загрузка фона
	image_f.loadFromFile("background.png");
	texture_f.loadFromImage(image_f);
	sprite_f.setTexture(texture_f);
	sprite_f.setPosition(0, 0);

	//  создание пушки
	image.loadFromFile("gun.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(300, 600);
	Gun gun(300, 600, 10, sprite);

	//  создание пули
	image_b.loadFromFile("bullet.png");
	texture_b.loadFromImage(image_b);
	sprite_b.setTexture(texture_b);
	sprite_b.setPosition(gun.getx() + 30, 550);
	Bullet bullet(gun.getx() + 30, 550, 20, sprite_b);

	//  создание шарика
	image_ball.loadFromFile("ball.png");
	texture_ball.loadFromImage(image_ball);
	sprite_ball.setTexture(texture_ball);
	sprite_ball.setPosition(0, 50);
	Ball ball(0, 50, 5, 5, sprite_ball);

	//  подготовка вывода жизней шарика
	Text ball_hp;
	ball_hp.setFont(font);
	ball_hp.setStyle(Text::Bold);
	ball_hp.setString(to_string(ball.get_hp()));
	ball_hp.setCharacterSize(52);
	ball_hp.setPosition(ball.getx() + 40, ball.gety() + 20);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//  отслеживание нажатий клавиш для отрисовки перемещения пушки
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			//  движение влево
			gun.coordinate_recount(true);
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			//  движение вправо
			gun.coordinate_recount(false);
		}

		//  включение паузы
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			draw_pause(font, score);
		}

		//  проверка: ударил ли шарик пушку
		//if ((ball.getx() < gun.getx() && ball.getx() + 100 > gun.getx()) || (ball.getx() > gun.getx() && ball.getx() < gun.getx() + 100))
		if( ((gun.getx() >= ball.getx() && gun.getx() <= ball.getx() + 100) || (gun.getx() + 80 > ball.getx() && gun.getx() + 80 < ball.getx() + 100)) && (gun.gety() > ball.gety() + 10 && gun.gety() < ball.gety() + 100))
		{
			if (ball.gety() + 100 > gun.gety())
			{
				draw_game_over(font, score);
				gun.putlife(false);
				ifstream fin;
				fin.open("record.txt");
				if (!fin.is_open())
				{
					ofstream fout;
					fout.open("record.txt");
					fout << score;
					fout.close();
				}
				else
				{
					int record;
					fin >> record;
					fin.close();
					if (record < score)
					{
						ofstream fout;
						fout.open("record.txt");
						fout << score;
						fout.close();
					}
				}
				return 1;
			}
		}

		if (!pause)
		{
			//  проверка: попала ли пуля в шарик
			if (bullet.getx() >= ball.getx() && bullet.getx() <= ball.getx() + 100 && bullet.gety() >= ball.gety() + 80 && bullet.gety() <= ball.gety() + 100)
			{
				ball.set_hp();
				bullet.set_draw_bullet(false);
				score++;
				player_points.setString("point: " + to_string(score));		//  вывод очков
				if(ball.get_hp() <= 0)
				{
					Image image_boom;
					image_boom.loadFromFile("boom.png");
					Texture texture_boom;
					texture_boom.loadFromImage(image_boom);
					Sprite sprite_boom;
					sprite_boom.setTexture(texture_boom);
					for (int i = 0; i < 5; i++)
					{
						sprite_boom.setTextureRect(IntRect(i * 100, 0, 100, 100));
						sprite_boom.setPosition(ball.getx(), ball.gety());
						ball.coordinate_recount();
						window.clear();
						window.draw(sprite_f);
						window.draw(gun.getsprite());
						window.draw(player_points);
						window.draw(sprite_boom);
						window.display();
					}
					srand(time(NULL));
					bool direction;					//  направление полета нового шарика
					int hp = rand() % 10 + 1;		//  кол-во жизней нового шарика
					int napravl = rand() % 2 + 1;	
					int speed = rand() % 5 + 3;		//  скорость нового шарика
					int corx;
					if (napravl == 1)
					{
						direction = true;
						corx = -100;
					}
					else
					{
						direction = false;
						corx = 800;
					}
					ball.new_ball(corx, 50, hp, speed, false, direction);
					ball.draw();
				}
				ball_hp.setString(to_string(ball.get_hp()));				//  вывод жизней шарика
				window.draw(player_points);
			}
			
			//  отрисовка движения пули
			bullet.coordinate_recount(gun);
			bullet.draw();
			//  отрисовка движения шарика
			ball.coordinate_recount();
			ball.draw();
			ball_hp.setPosition(ball.getx() + 40, ball.gety() + 20);
			//  отрисовка текстур после изменениях их координат
			window.clear();
			gun.draw();
			window.draw(sprite_f);					//  фон
			window.draw(gun.getsprite());			//  пушка
			if (bullet.get_draw_bullet())
				window.draw(bullet.getsprite());	//  пуля
			window.draw(ball.getsprite());			//  шарик
			window.draw(ball_hp);
			window.draw(player_points);
			window.display();
		}
	}
}

int draw_pause(Font font, int score)
{
	int y = -700;
	bool draw = true;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (draw)
		{
			//  загрузка фона паузы
			Image image_pause;
			image_pause.loadFromFile("pause.png");
			Texture texture_pause;
			texture_pause.loadFromImage(image_pause);
			Sprite sprite_pause;
			sprite_pause.setTexture(texture_pause);
			sprite_pause.setPosition(0, y);

			//  загрузка кол-ва очков
			Text text_game_pause;
			text_game_pause.setFont(font);
			text_game_pause.setCharacterSize(32);
			text_game_pause.setFillColor(Color::Black);
			text_game_pause.setPosition(100, 400);
			text_game_pause.rotate(40);
			for (int i = 1; i < 71; i++)
			{
				sprite_pause.setPosition(0, y + i * 10);
				text_game_pause.setPosition(390, y + i * 10 + 60);
				text_game_pause.setString("your's point: " + to_string(score));
				window.clear();
				window.draw(sprite_pause);
				window.draw(text_game_pause);
				window.display();
			}
			draw = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			return 0;
		}
	}
}

void draw_game_over(Font font, int score)
{
	int y = 700;
	Image game_over;
	game_over.loadFromFile("gameover.png");
	Texture t_game_over;
	t_game_over.loadFromImage(game_over);
	Sprite s_game_over;
	s_game_over.setTexture(t_game_over);
	s_game_over.setPosition(0, y);

	Text text_game_over;
	text_game_over.setFont(font);
	text_game_over.setCharacterSize(32);
	text_game_over.setFillColor(Color::Black);
	text_game_over.setPosition(400, 200);
	for (int i = 1; i < 71; i++)
	{
		s_game_over.setPosition(0, y - i * 10);
		text_game_over.setPosition(350, y - i * 10 + 100);
		text_game_over.setString("your point: " + to_string(score));
		window.clear();
		window.draw(s_game_over);
		window.draw(text_game_over);
		window.display();
	}
}