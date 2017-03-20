#include <SFML/Graphics.hpp>
#include "level.h"
#ifndef ENTITY_H
#define ENTITY_H

											//Общий клас родитель для других классов//

class Entity
{
public: 
   std::vector<Object> obj; //Список объектов
   float      dx,	        //Смещение по оси х
			  dy,	        //Смещение по оси у
			   x,	        //Координата игрока по х
			   y,	        //Координата игрока по у
		   speed,	        //Скорость игрока
	   moveTimer;	        //???
   int     width,           //Ширина спрайта
	      height;	        //Высота спрайта
   bool   isMove,           //Движется
		onGround,           //На земле 
		    Life;			//Живой
   sf::Texture texture;
   sf::Sprite  sprite;
   sf::String  name;
  
   Entity(sf::Image &image, sf::String Name, float X, float Y, int Width, int Height)
   {
	   x	  = X;
	   y	  = Y;
	   width  = Width;
	   height = Height;
	   name   = Name;
	  
	   moveTimer = 0;
	   speed     = 0;
	   dx        = 0;
	   dy        = 0;
	   
	   onGround   = false;
	   isMove     = false;
	   Life       = true;
		
	   texture.loadFromImage(image);        //Загружаем картинку в текстуру
	   sprite.setTexture(texture);			//Загружаем текстуру в спрайт
	   sprite.setOrigin(width/2, height/2); //Устанавлиаем новые координаты - центр спрайта
   }

   sf::FloatRect getRect()//ф-ция получения прямоугоьника. Его координаты, размеры.
   {                      //Она нужна для проверки столкновений.
		return sf::FloatRect (x,y,width,height); 
   }		   
   
   virtual void update(float time) = 0;//все потомки переопределяют эту ф-цию
};
#endif