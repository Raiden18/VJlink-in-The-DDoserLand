#include <SFML/Graphics.hpp>
#include "level.h"
#ifndef ENTITY_H
#define ENTITY_H

											//����� ���� �������� ��� ������ �������//

class Entity
{
public: 
   std::vector<Object> obj; //������ ��������
   float      dx,	        //�������� �� ��� �
			  dy,	        //�������� �� ��� �
			   x,	        //���������� ������ �� �
			   y,	        //���������� ������ �� �
		   speed,	        //�������� ������
	   moveTimer;	        //???
   int     width,           //������ �������
	      height;	        //������ �������
   bool   isMove,           //��������
		onGround,           //�� ����� 
		    Life;			//�����
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
		
	   texture.loadFromImage(image);        //��������� �������� � ��������
	   sprite.setTexture(texture);			//��������� �������� � ������
	   sprite.setOrigin(width/2, height/2); //������������ ����� ���������� - ����� �������
   }

   sf::FloatRect getRect()//�-��� ��������� �������������. ��� ����������, �������.
   {                      //��� ����� ��� �������� ������������.
		return sf::FloatRect (x,y,width,height); 
   }		   
   
   virtual void update(float time) = 0;//��� ������� �������������� ��� �-���
};
#endif