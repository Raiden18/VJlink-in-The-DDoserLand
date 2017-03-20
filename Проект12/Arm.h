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
	sf::Vector2i pixelPos; //забираем коорд курсора
	sf::Vector2f pos; //переводим их в игровые (уходим от коорд окна)
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
		pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
		pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		dX = pos.x - x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
		dY = pos.y - y;//он же, координата y
		rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
		//std::cout<<rotation<<std::endl;
		sprite.setRotation(rotation);//поворачиваем спрайт на эти градусы

		sprite.setPosition(x, y); 
	}
	
};


#endif 