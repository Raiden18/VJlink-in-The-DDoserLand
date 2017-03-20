#include <SFML/Graphics.hpp>
#ifndef ARM_H
#define ARM_H

class Arm { 
 
public:
	float w, h,x,y;
	sf::String File;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i pixelPos; //�������� ����� �������
	sf::Vector2f pos; //��������� �� � ������� (������ �� ����� ����)
	float dX, dY;
	float rotation;
	bool mirror;
	enum {left, right} state;
	Arm (sf::String F, float X, float Y, float W, float H)
	{
		state = right;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(sf::Color(0, 0, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		
		x = X; y = Y;

		sprite.setTextureRect(sf::IntRect(0, 0, w, h));
        sprite.setOrigin(w / w, h / 2); 
	}
	void update(sf::RenderWindow & window) 
	{    
		pixelPos = sf::Mouse::getPosition(window);//�������� ����� �������
		pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		dX = pos.x - x;//������ , ����������� ������, ������� ���������� ������ � ������
		dY = pos.y - y;//�� ��, ���������� y
		rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
		//std::cout<<rotation<<std::endl;
		sprite.setRotation(rotation);//������������ ������ �� ��� �������

		sprite.setPosition(x, y); 
	}
	
};


#endif 