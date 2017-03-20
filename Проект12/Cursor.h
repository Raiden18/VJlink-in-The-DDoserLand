#include <SFML/Graphics.hpp>
#ifndef CURSOR_H
#define CURSOR_H

class Cursor { 
 
public:
	float w, h,x,y;\
	sf::String File;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i pixelPos; //забираем коорд курсора
	sf::Vector2f pos; //переводим их в игровые (уходим от коорд окна)
	float dX, dY;
	
	Cursor (sf::String F, float X, float Y, float W, float H)
	{
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(sf::Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(sf::IntRect(0, 0, w, h));
        sprite.setOrigin(w / 2, h / 2); 
	}
	void update(sf::RenderWindow & window) 
	{    
		window.setMouseCursorVisible(false);
		//if (!mirror) {x = pos.x-160; y = pos.y+160;} else
		{
		pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
		pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		x = pos.x;
		y = pos.y;
		}
		sprite.setPosition(x, y);
	}
};


#endif