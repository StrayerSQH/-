#include "Explore.h"
#include "SFML/Graphics.hpp"
#include "conio.h"
#include "ReturnHomeButton.h"
#include "GlobalVar.h"
#include "MusicClickDetail.h"

int Explore::TILE_SIZE = 20;

void Explore::MapSet()
{
    img[0].loadFromFile("E:\\ͼƬ\\Screenshots\\road.png");
    img[1].loadFromFile("E:\\ͼƬ\\Screenshots\\dormitory.png");
    img[2].loadFromFile("E:\\ͼƬ\\Screenshots\\ABCD.png");
    img[3].loadFromFile("E:\\ͼƬ\\Screenshots\\dining_hall.png");
    img[4].loadFromFile("E:\\ͼƬ\\Screenshots\\school_gate.png");
    img[5].loadFromFile("E:\\ͼƬ\\Screenshots\\river.png");
    img[6].loadFromFile("E:\\ͼƬ\\Screenshots\\pool.png");
    img[7].loadFromFile("E:\\ͼƬ\\Screenshots\\changqiao.png");
    img[8].loadFromFile("E:\\ͼƬ\\Screenshots\\guangchang.png");
    img[9].loadFromFile("E:\\ͼƬ\\Screenshots\\erjilou.png");
    img[10].loadFromFile("E:\\ͼƬ\\Screenshots\\zonghelou.png");
    img[11].loadFromFile("E:\\ͼƬ\\Screenshots\\library.png");
    img[12].loadFromFile("E:\\ͼƬ\\Screenshots\\man_s.png");
    img[13].loadFromFile("E:\\ͼƬ\\Screenshots\\man_w.png");
    img[14].loadFromFile("E:\\ͼƬ\\Screenshots\\man_l.png");
    img[15].loadFromFile("E:\\ͼƬ\\Screenshots\\man_r.png");
}

void Explore::DrawMap(sf::RenderWindow& window)
{
    for (int i = 0; i < 48; i++) // ��
    {
        for (int j = 0; j < 57; j++) // ��
        {
            sf::Sprite sprite;
            sprite.setTexture(img[Map[i][j]]);
            sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
            window.draw(sprite);
        }
    }
}

void Explore::MoveCharacter(sf::RenderWindow& window)
{
    if (moving)
    {
        return;
    }

    moving = true;

    if (key == 'w' || key == 'W')
    {
        if (y > 0 && (Map[y - 1][x] == 0 || Map[y - 1][x] == 7))
        {
            DrawMap(window);
            y--;
            sf::Sprite sprite;
            sprite.setTexture(img[13]);
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(sprite);
        }
    }
    else if (key == 's' || key == 'S')
    {
        if (y < 47 && (Map[y + 1][x] == 0 || Map[y + 1][x] == 7))
        {
            DrawMap(window);
            y++;
            sf::Sprite sprite;
            sprite.setTexture(img[12]);
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(sprite);
        }
    }
    else if (key == 'a' || key == 'A')
    { // �����ƶ�
        if (x > 0 && (Map[y][x - 1] == 0 || Map[y][x - 1] == 7))
        {
            DrawMap(window);
            x--;
            sf::Sprite sprite;
            sprite.setTexture(img[14]);
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(sprite);
        }
    }
    else if (key == 'd')
    { // �����ƶ�
        if (x < 56 && (Map[y][x + 1] == 0 || Map[y][x + 1] == 7))
        {
            DrawMap(window);
            x++;
            sf::Sprite sprite;
            sprite.setTexture(img[15]);
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(sprite);
        }
    }

    moving = false;
}

int Explore::Program(sf::RenderWindow& window)
{
    float ScreenWidth, ScreenHeight;
    ScreenWidth = window.getSize().x;
    ScreenHeight = window.getSize().y;

    ReturnHomeButton returnHomeButton(ExitButton_x, ExitButton_y);

    // ��ʼ����ͼ
    MapSet();

    while (window.isOpen())
    {
        int end = 1;
        int returnHome = 1;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if ((event.type == sf::Event::MouseButtonPressed && end) && returnHome) {
                if (event.mouseButton.button == sf::Mouse::Left) {
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            key = 'w';
            MoveCharacter(window);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            key = 's';
            MoveCharacter(window);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            key = 'a';
            MoveCharacter(window);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            key = 'd';
            MoveCharacter(window);
        }
        // ��ȡ���λ��
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        window.clear();
        DrawMap(window);

        // �������Ƿ��ڰ�ť��Χ�ڣ������ð�ť״̬
        returnHomeButton.SetHovered(returnHomeButton.CheckHover(mousePosF));
        returnHomeButton.DrawButton(window);
        window.display();
    }


    return 0;
}