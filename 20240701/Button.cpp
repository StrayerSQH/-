#include "Button.h"
#include "ExitButton.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

// ���캯�����ڴ�����ʾ��xλ�ã��ڴ�����ʾ��yλ�ã���ť�߶ȣ���ť��ȣ���ť����ʾ�����֣���ť��Ĭ��͸����128��
Button::Button(float window_x, float window_y, float width, float height, const std::string& text, sf::Uint8 alpha)
    : isHovered(false)
{
    shape.setPosition(window_x, window_y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(128, 128, 128, alpha));

    if (!font.loadFromFile("��ͼĦ��С����(�������).ttf"))
    {
        cout << "�������Ĭ������ʧ�ܣ����������Ƿ���ڣ�����" << endl;
    }

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(characterSize);
    label.setFillColor(sf::Color::White);

    // �����ı���ԭ��λ��Ϊ���Ⱥ͸߶ȵ�һ��5
    sf::FloatRect labelBounds = label.getLocalBounds();
    label.setOrigin(labelBounds.left + labelBounds.width / 2, labelBounds.top + labelBounds.height / 2);

    // ���ı����ж���
    float centerX = window_x + width / 2;
    float centerY = window_y + height / 2;
    label.setPosition(centerX, centerY);
}

void Button::DrawButton(sf::RenderWindow& window)
{
    label.setFillColor(sf::Color::White);
    shape.setFillColor(sf::Color(128, 128, 128, 0));

    if (isHovered)
    {
        characterSize = 120;
    }
    else
    {
        characterSize = 80;
    }

    // ���ð�ť�ı��������С
    label.setCharacterSize(characterSize);

    // �����ı���ԭ��λ��Ϊ���Ⱥ͸߶ȵ�һ��
    sf::FloatRect labelBounds = label.getLocalBounds();
    label.setOrigin(labelBounds.left + labelBounds.width / 2, labelBounds.top + labelBounds.height / 2);

    // ���ı����ж���
    float centerX = shape.getPosition().x + shape.getSize().x / 2;
    float centerY = shape.getPosition().y + shape.getSize().y / 2;
    label.setPosition(centerX, centerY);

    window.draw(shape);
    window.draw(label);
}

bool Button::CheckHover(const sf::Vector2f& mousePos)
{
    return shape.getGlobalBounds().contains(mousePos);
}

void Button::SetHovered(bool hovered)
{
    isHovered = hovered;
}