#include "Explore.h"
#include "SFML/Graphics.hpp"
#include "ReturnHomeButton.h"
#include "GlobalVar.h"
#include "MusicClickDetail.h"

float Explore::PIXEL_SIZE = 30;

Explore::Explore() : character_x(1000), character_y(1000) {};

Explore::Explore(int sex) : character_x(1000), character_y(1000)
{
    Sex = sex;
    character.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
    character.setFillColor(sf::Color::Red);
    if (Sex == 1)
    {
        if (!sexSetTexture.loadFromFile("Boy.jpg"))
        {
            std::cout << "Fail to open Boy.jpg" << endl;
        }

        sexSetSprite.setTexture(sexSetTexture);
        sexSetSprite.setPosition(character_x, character_y);
        // ���ü�ͷͼƬ�Ĵ�С
        sexSetSprite.setScale(
            PIXEL_SIZE / sexSetSprite.getLocalBounds().width,
            PIXEL_SIZE / sexSetSprite.getLocalBounds().height
        );
    }
    else
    {
        if (!sexSetTexture.loadFromFile("Girl.jpg"))
        {
            std::cout << "Fail to open Girl.jpg" << endl;
        }

        sexSetSprite.setTexture(sexSetTexture);
        sexSetSprite.setPosition(character_x, character_y);
        // ���ü�ͷͼƬ�Ĵ�С
        sexSetSprite.setScale(
            PIXEL_SIZE / sexSetSprite.getLocalBounds().width,
            PIXEL_SIZE / sexSetSprite.getLocalBounds().height
        );
    }
}


void Explore::MoveUp()
{
    std::cout << character_x << " " << character_y << endl;
    if (!checkCollision(character_x, character_y - PIXEL_SIZE))
        character_y -= PIXEL_SIZE;
}

void Explore::MoveDown()
{
    if (!checkCollision(character_x, character_y + PIXEL_SIZE))
        character_y += PIXEL_SIZE;
}

void Explore::MoveLeft() {
    if (!checkCollision(character_x - PIXEL_SIZE, character_y))
        character_x -= PIXEL_SIZE;
}

void Explore::MoveRight() {
    if (!checkCollision(character_x + PIXEL_SIZE, character_y))
        character_x += PIXEL_SIZE;
}

void Explore::Update() {
    character.setPosition(character_x, character_y);
    sexSetSprite.setPosition(character_x, character_y);
}

void Explore::Draw(sf::RenderWindow& window) {
    window.draw(sexSetSprite);
    //window.draw(character);
}


int Explore::Program(sf::RenderWindow& window)
{
    window.setFramerateLimit(60);

    ReturnHomeButton returnHomeButton(ExitButton_x, ExitButton_y);
    Explore characterControll(Sex);

    float ScreenWidth, ScreenHeight;
    ScreenWidth = window.getSize().x;
    ScreenHeight = window.getSize().y;

    while (window.isOpen())
    {
        int end = 1;
        int returnHome = 1;
        sf::Event event;
        
        while(window.pollEvent(event)) 
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            characterControll.MoveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            characterControll.MoveDown();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            characterControll.MoveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            characterControll.MoveRight();
        }
       
        // ��ȡ���λ��
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        window.clear();

        characterControll.Update();
        characterControll.Draw(window);

        // �������Ƿ��ڰ�ť��Χ�ڣ������ð�ť״̬
        returnHomeButton.SetHovered(returnHomeButton.CheckHover(mousePosF));
        returnHomeButton.DrawButton(window);
        window.display();
    }


    return 0;
}