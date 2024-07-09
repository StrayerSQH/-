#include "MainStoryChapter.h"
#include "SFML/Graphics.hpp"
#include <iostream>

float MainStoryChapter::PIXEL_SIZE = 50;

MainStoryChapter::MainStoryChapter(int sex, int c, std::string s, sf::RenderWindow & window)
{
	Sex = sex;
	chapterNum = c;
	chapterImgPath = s;
	character_x = 1000;
	character_y = 1000;

	//�����½ڱ���
	sf::VideoMode deskTop = sf::VideoMode::getDesktopMode();
	if (!chapterBackgroundImg.loadFromFile(chapterImgPath))
	{
		cout << "��" << chapterNum << "�½ڱ���ͼƬ����ʧ��" << endl;
	}
	chapterSprite.setTexture(chapterBackgroundImg);
	chapterSprite.setScale(
		window.getSize().x / chapterSprite.getLocalBounds().width,
		window.getSize().y / chapterSprite.getLocalBounds().height
	);

	//������������
	character.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
	character.setFillColor(sf::Color::Red);
	if (Sex == 1)
	{
		if (!sexSetTexture.loadFromFile("Boy.jpg"))
		{
			std::cout << "Fail to open Boy.jpg" << std::endl;
		}

		sexSetSprite.setTexture(sexSetTexture);
		sexSetSprite.setPosition(character_x, character_y);
		sexSetSprite.setScale(
			PIXEL_SIZE / sexSetSprite.getLocalBounds().width,
			PIXEL_SIZE / sexSetSprite.getLocalBounds().height
		);
	}
	else
	{
		if (!sexSetTexture.loadFromFile("Girl.jpg"))
		{
			std::cout << "Fail to open Girl.jpg" << std::endl;
		}

		sexSetSprite.setTexture(sexSetTexture);
		sexSetSprite.setPosition(character_x, character_y);
		sexSetSprite.setScale(
			PIXEL_SIZE / sexSetSprite.getLocalBounds().width,
			PIXEL_SIZE / sexSetSprite.getLocalBounds().height
		);
	}
}

void MainStoryChapter::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (!checkBoundary(character_x, character_y))
		{
			character_y -= PIXEL_SIZE;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (!checkBoundary(character_x, character_y + PIXEL_SIZE))
		{
			character_y += PIXEL_SIZE;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!checkBoundary(character_x, character_y))
		{
			character_x -= PIXEL_SIZE;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!checkBoundary(character_x + PIXEL_SIZE, character_y))
		{
			character_x += PIXEL_SIZE;
		}
	}
}

void MainStoryChapter::Update()
{
	character.setPosition(character_x, character_y);
	sexSetSprite.setPosition(character_x, character_y);
}

void MainStoryChapter::CharacterDraw(sf::RenderWindow& window)
{
	window.draw(sexSetSprite);
}

ChapterOne::ChapterOne(int sex, int c, std::string s, sf::RenderWindow& window) : MainStoryChapter(sex, c, s, window) {};

int ChapterOne::Program(sf::RenderWindow& window)
{
	window.setFramerateLimit(60);

	window.clear();
	//ChapterOne chapterOne(MainStoryChapter::Sex, MainStoryChapter::chapterNum, MainStoryChapter::chapterImgPath, window);

	while (window.isOpen())
	{
		int end = 1;
		int returnHome = 1;

		sf::Event event;
		ReturnHomeButton returnHomeButton(ExitButton_x, ExitButton_y);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if ((event.type == sf::Event::MouseButtonPressed && end) && returnHome)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// ��������λ���Ƿ����˳���ť��Χ��
					if (returnHomeButton.CheckHover(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
					{
						// �˳���ť���������������,��������Ԫ�����ֲ���
						Arch archMusic("ArchClickMusic.mp3");
						if (archMusic.ArchLoadMusic())
						{
							archMusic.ArchPlay();
						}
						returnHome = returnHomeButton.ExitProgram(window);

						if (returnHome)
						{
							return 0;
						}
					}
				}
			}
		}
		// ����ɫ�ƶ�
		Move();

		// ��ȡ���λ��
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		window.clear();
		Update();

		window.draw(MainStoryChapter::chapterSprite);
		window.draw(MainStoryChapter::sexSetSprite);
		CharacterDraw(window);
		// �������Ƿ��ڰ�ť��Χ�ڣ������ð�ť״̬
		returnHomeButton.SetHovered(returnHomeButton.CheckHover(mousePosF));
		returnHomeButton.DrawButton(window);

		window.display();
	}
}