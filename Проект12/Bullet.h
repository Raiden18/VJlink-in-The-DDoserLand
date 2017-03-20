#include "Entity.h"
#ifndef BULLET_H
#define BULLET_H

class Bullet :public Entity{//����� ����
public:
	float distance;//����������� ����
	float tempx, tempy;
	float tempX, tempY;
	sf::Vector2i pixelPos; //�������� ����� �������
	sf::Vector2f pos; //��������� �� � ������� (������ �� ����� ����)

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, float TEMPX, float TEMPY, float tempXX, float tempYY) :Entity(image, Name, X, Y, W, H){//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
		obj = lvl.GetObjects("solid");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
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
		//���� ������������� � ������������
	}
 
	void update(float time)
	{
			distance =sqrt((tempx - x)*(tempx - x) + (tempy - y)*(tempy - y));//������� ��������� (����� �� ����� � �� ����� �). ������� ����� �������
			
		
 
					x += 0.1*time*(tempx - x) / 10;//���� �� ���� � ������� ������� �������
					y += 0.1*time*(tempy - y) / 10;//���� �� ������ ��� ��
 
			if (x <= 0) x = 1;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������
			if (y <= 0) y = 1;
		


			for (int i = 0; i < obj.size(); i++) {//������ �� �������� solid
				if (getRect().intersects(obj[i].rect)) //���� ���� ������ ���������� � �����,
				{
					Life = false;// �� ���� �������
				}
				if ((x == tempX) && (x == tempY))
				{
					Life = false;// �� ���� �������
				}
			}
 		    std::cout<<tempX<<" "<<tempY<<std::endl;
			sprite.setPosition(x, y);//�������� ������� ����
	}
};
#endif