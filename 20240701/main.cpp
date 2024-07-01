#include <iostream>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include "GlobalVar.h"
#include "WindowsShow.h"
#include "Button.h"
#include "ChooseStateButton.h"
#include "ExitButton.h"
#include "MusicBGM.h"
#include "MusicClick.h"
#include "MusicClickDetail.h"

float numAdd(float n);

int main()
{
    //���ò��ű�������
    MusicBGM music("TestMusic.mp3");
    if (music.loadMusic()) 
    {
        music.play();
    }

    // �������ڶ�����ʾ
    WindowsShow windowsShow;
    windowsShow.ShowWindow();
    // ��ȡ���ڶ��������
    sf::RenderWindow& window = windowsShow.getWindow();

    // ����ģʽѡ��ť
    float Num = 0;
    ChooseStateButton MainStoryButton(
        window.getSize().x / 2 - ChooseStateButton::ChooseButtonWidth / 2,
        (7 - NumChooseButton + Num) * window.getSize().y / 7 - ChooseStateButton::ChooseButtonHeight / 2,
        "Main Story"
    );
    Num = numAdd(Num);
    ChooseStateButton ExploreButton(
        window.getSize().x / 2 - ChooseStateButton::ChooseButtonWidth / 2,
        (7 - NumChooseButton + Num) * window.getSize().y / 7 - ChooseStateButton::ChooseButtonHeight / 2,
        "Explore"
    );
    // �����˳���ť
    ExitButton ExitButton_(ExitButton_x, ExitButton_y);

    // ���ִ��ڿ���״̬
    while (window.isOpen())
    {
        int end = 1; 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && end) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // ��������λ���Ƿ����˳���ť��Χ��
                    if (ExitButton_.CheckHover(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) 
                    {
                        // �˳���ť���������������,��������Ԫ�����ֲ���
                        Arch archMusic("ArchClickMusic.mp3");
                        if (archMusic.ArchLoadMusic())
                        {
                            archMusic.ArchPlay();
                        }
                        end = ExitButton_.ExitProgram(window);
                    }
                }
            }
        }

        // ��ȡ���λ��
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // �������Ƿ��ڰ�ť��Χ�ڣ������ð�ť״̬
        MainStoryButton.SetHovered(MainStoryButton.CheckHover(mousePosF));
        ExploreButton.SetHovered(ExploreButton.CheckHover(mousePosF));
        ExitButton_.SetHovered(ExitButton_.CheckHover(mousePosF));

        // ���֮ǰ��ͼ��
        window.clear();

        // ���Ʊ���
        windowsShow.DrawBackground(window);

        // ���ư�ť
        ExitButton_.Button::DrawButton(window);
        MainStoryButton.Button::DrawButton(window);
        ExploreButton.Button::DrawButton(window);
        // ��ʾ���Ƶ�ͼ��
        window.display();
    }

    return 0;
}

float numAdd(float n)
{
    return n + 1.5;
}