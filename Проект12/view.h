#include <SFML/Graphics.hpp>
using namespace sf;
 
sf::View view;
 
void setPlayerCoordinateForView(float x, float y) { 
	float tempX = x; float tempY = y;
 
	if (x < 355)  tempX = 355;
	if (x > 2500) tempX = 2500;
	if (y < 240)  tempY = 240;//������� �������
	if (y > 624)  tempY = 624;//������ �������.��� ����� �����
 
	view.setCenter(tempX, tempY); 
}