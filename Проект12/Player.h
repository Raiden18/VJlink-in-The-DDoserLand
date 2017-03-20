#include "Entity.h"
#include "view.h"
#ifndef PLAYER_H
#define PLAYER_H
class Player : public Entity
{
public: 
	enum {left, right, up, down, jump, stay} state;
	float currentFrame;
	bool isShoot;
	Player (sf::Image &image, sf::String string, Level &lev, float X, float Y, int Width, int Height) :Entity(image, string, X, Y, Width, Height)
	{
		currentFrame = 0;
		state = stay;
		obj = lev.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
		if (name == "Player1")
			{
				sprite.setTextureRect(sf::IntRect (0, 2, width, height));
			}
	}

	void control ()
	{
		if (sf::Keyboard::isKeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))               {state = left; speed = 0.15;}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))			  {state = right; speed = 0.15;}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround)) 
			{
				state = jump;
				dy = -0.6; 
				onGround = false;

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))				  {state = down;}

		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	   {
		   for (int i = 0; i<obj.size(); i++)//проходимся по объектам
			   if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			   {
				   if (obj[i].name == "solid")//если встретили препятствие
				   {
					   if (Dy>0)	{ y = obj[i].rect.top - height;  dy = 0; onGround = true; }
					   if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0;}
					   if (Dx>0)	{ x = obj[i].rect.left - width;}
					   if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; }
				   }
				}
		       else 
		       if (dy > 0) { onGround = false; }
	   }


	void update(float time)
	   {
		   control();

		   if (!onGround){speed = 0.15;}

		   switch (state)
		   {
		   case right: 
						dx = speed; 
						currentFrame +=(speed*0.07)*time;       //Движениe по кадрам
						if (currentFrame > 5) {currentFrame -=4;}
						sprite.setScale(1,1);					//Отражение по горизонтали
						sprite.setTextureRect(sf::IntRect(37*int(currentFrame), 2, width, height));
				break;
		   case left:  
				   dx = -speed; 
				   currentFrame +=(speed*0.07)*time;		 //Движение по кадрам
				   if (currentFrame > 5) {currentFrame -=4;} 
				   sprite.setScale(-1,1);					 //Отражение по горизонтали
				   sprite.setTextureRect(sf::IntRect(37*int(currentFrame), 2, width, height));
			   break;
		   case up:                 break;
		   case down: dx = 0;  sprite.setTextureRect(sf::IntRect (0, 2, width, height));  break;
		   }
		   if (onGround &&  (speed == 0) ) {sprite.setTextureRect(sf::IntRect (0, 2, width, height));}
		   x += dx*time;
		   checkCollisionWithMap(dx, 0);
		   y += dy*time;
		   checkCollisionWithMap(0, dy);
		   sprite.setPosition(x + width / 2, y + height / 2);
		   if (!isMove){ speed = 0;}
		   //if (y>875) {Life = false;}
		   setPlayerCoordinateForView(x, y);
		   dy = dy + 0.0015*time;
	
	   } 
};


#endif