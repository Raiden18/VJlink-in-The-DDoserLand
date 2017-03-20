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
	

	sf::Music startAudio;//создаем объект музыки
	startAudio.openFromFile("Audio/StartLevelAudio.ogg");//загружаем файл
	startAudio.setVolume(100);
	startAudio.play();//воспроизводим музыку
	

	sf::Music music;//создаем объект музыки
	music.openFromFile("Audio/MainMusic.ogg");//загружаем файл	
	music.setVolume(30);
	music.play();//воспроизводим музыку

	menu(window);//вызов меню

	view.reset(FloatRect(0, 0, 640, 480));
	
	//window.setMouseCursorVisible(false); //Скрываем курсор

	Level lvl;//создали экземпляр класса уровень
	lvl.LoadFromFile("map.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.
	
	sf::Image heroImage;
	heroImage.loadFromFile("images/Player.png");
	heroImage.createMaskFromColor(Color(255,255,255));
	Object player = lvl.GetObject("player");
	Player p(heroImage,"Player1", lvl,player.rect.left,player.rect.top, 33, 91);


	Arm hand("heroForRotate.png", 125, 616, 55, 30);
	
	Cursor Cur("Cursor.png", 125, 616, 20, 20);

	SoundBuffer LooseBuffer;//создаём буфер для звука
	LooseBuffer.loadFromFile("Audio/WhenYouLoose.ogg");//загружаем в него звук
	Sound loose(LooseBuffer);//создаем звук и загружаем в него звук из буфера

	SoundBuffer shootBuffer;//создаём буфер для звука
	shootBuffer.loadFromFile("Audio/Shooting.ogg");//загружаем в него звук
	Sound shoot(shootBuffer);//создаем звук и загружаем в него звук из буфера

	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения
	BulletImage.createMaskFromColor(Color(0, 0, 0));//маска для пули по черному цвету

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator it2;//второй итератор.для взаимодействия между объектами списка



	Clock clock;
	while (window.isOpen())
	{
		music.setLoop(true);// зацикливаем музыку

		float time = clock.getElapsedTime().asMicroseconds();
	
		clock.restart();
		time = time/800;

		if (p.y>875) {p.x=200; p.y=0; loose.play();}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();	
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
			//if (event.key.code == Mouse::Left)//а именно левая 
				{
					entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, Cur.x, Cur.y, Cur.pixelPos.x, Cur.pixelPos.y));
					shoot.play();
				}
		}		
		/////////НЕ РАЗБИРАЛСЯ///////////////////////
		for (it = entities.begin(); it != entities.end();)//говорим что проходимся от начала до конца
		{
			Entity *b = *it;//для удобства, чтобы не писать (*it)->
			b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (b->Life == false)	{ it = entities.erase(it); delete b; }// если этот объект мертв, то удаляем его
			else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}



		//Костыли
		hand.x = p.x + (p.width/2);
		hand.y = p.y + (p.height/4);

		
		p.update(time);
		hand.update(window);
		Cur.update(window);
		window.setView(view);
		window.clear(sf::Color(77,83,140));
		lvl.Draw(window);//рисуем новую карту


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