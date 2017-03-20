#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "level.h"
#include "Entity.h"
#include "Player.h"
#include "Menu.h"
#include "Arm.h"
#include "Cursor.h"
//#include "TinyXML/tinyxml.h"
#include "Bullet.h"
#include <list>
#include <vector>
 


 
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "VjLink B CTPAHE DDOSEPOB");
	

	sf::Music startAudio;//������� ������ ������
	startAudio.openFromFile("Audio/StartLevelAudio.ogg");//��������� ����
	startAudio.setVolume(100);
	startAudio.play();//������������� ������
	

	sf::Music music;//������� ������ ������
	music.openFromFile("Audio/MainMusic.ogg");//��������� ����	
	music.setVolume(30);
	music.play();//������������� ������

	menu(window);//����� ����

	view.reset(FloatRect(0, 0, 640, 480));
	
	//window.setMouseCursorVisible(false); //�������� ������

	Level lvl;//������� ��������� ������ �������
	lvl.LoadFromFile("map.tmx");//��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.
	
	sf::Image heroImage;
	heroImage.loadFromFile("images/Player.png");
	heroImage.createMaskFromColor(Color(255,255,255));
	Object player = lvl.GetObject("player");
	Player p(heroImage,"Player1", lvl,player.rect.left,player.rect.top, 33, 91);


	Arm hand("heroForRotate.png", 125, 616, 55, 30);
	
	Cursor Cur("Cursor.png", 125, 616, 20, 20);

	SoundBuffer LooseBuffer;//������ ����� ��� �����
	LooseBuffer.loadFromFile("Audio/WhenYouLoose.ogg");//��������� � ���� ����
	Sound loose(LooseBuffer);//������� ���� � ��������� � ���� ���� �� ������

	SoundBuffer shootBuffer;//������ ����� ��� �����
	shootBuffer.loadFromFile("Audio/Shooting.ogg");//��������� � ���� ����
	Sound shoot(shootBuffer);//������� ���� � ��������� � ���� ���� �� ������

	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������
	BulletImage.createMaskFromColor(Color(0, 0, 0));//����� ��� ���� �� ������� �����

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator it2;//������ ��������.��� �������������� ����� ��������� ������



	Clock clock;
	while (window.isOpen())
	{
		music.setLoop(true);// ����������� ������

		float time = clock.getElapsedTime().asMicroseconds();
	
		clock.restart();
		time = time/800;

		if (p.y>875) {p.x=200; p.y=0; loose.play();}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();	
			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
			//if (event.key.code == Mouse::Left)//� ������ ����� 
				{
					entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, Cur.x, Cur.y, Cur.pixelPos.x, Cur.pixelPos.y));
					shoot.play();
				}
		}		
		/////////�� ����������///////////////////////
		for (it = entities.begin(); it != entities.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->Life == false)	{ it = entities.erase(it); delete b; }// ���� ���� ������ �����, �� ������� ���
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}



		//�������
		hand.x = p.x + (p.width/2);
		hand.y = p.y + (p.height/4);

		
		p.update(time);
		hand.update(window);
		Cur.update(window);
		window.setView(view);
		window.clear(sf::Color(77,83,140));
		lvl.Draw(window);//������ ����� �����


		window.draw(hand.sprite);
		window.draw(p.sprite);
		window.draw(Cur.sprite);
		for (it = entities.begin(); it != entities.end(); it++){
			window.draw((*it)->sprite); 
		}
		window.display();
	}
	return 0;
}