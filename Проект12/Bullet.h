#include "Entity.h"
#ifndef BULLET_H
#define BULLET_H

class Bullet :public Entity{//класс пули
public:
	float distance;//направление пули
	float tempx, tempy;
	float tempX, tempY;
	sf::Vector2i pixelPos; //забираем коорд курсора
	sf::Vector2f pos; //переводим их в игровые (уходим от коорд окна)

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, float TEMPX, float TEMPY, float tempXX, float tempYY) :Entity(image, Name, X, Y, W, H){//всё так же, только взяли в конце состояние игрока (int dir)
		obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
		x = X;
		y = Y;
		tempx = TEMPX;
		tempy = TEMPY;
		tempX = tempXX;
		tempY = tempYY;
		speed = 0.8;
		width = height = 16;
		Life = true;
		sprite.setOrigin(width/2,height/2);
		//выше инициализация в конструкторе
	}
 
	void update(float time)
	{
			distance =sqrt((tempx - x)*(tempx - x) + (tempy - y)*(tempy - y));//считаем дистанцию (длину от точки А до точки Б). формула длины вектора
			
		
 
					x += 0.1*time*(tempx - x) / 10;//идем по иксу с помощью вектора нормали
					y += 0.1*time*(tempy - y) / 10;//идем по игреку так же
 
			if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
			if (y <= 0) y = 1;
		


			for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
				if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
				{
					Life = false;// то пуля умирает
				}
				if ((x == tempX) && (x == tempY))
				{
					Life = false;// то пуля умирает
				}
			}
 		    std::cout<<tempX<<" "<<tempY<<std::endl;
			sprite.setPosition(x, y);//задается позицию пуле
	}
};
#endif