//
// Created by Justice Bole on 10/8/22.
//
#include "Player.h"


Player::Player(const Vector2& pos, const Vector2& size, const Color& color, const float speed) :
        m_position{pos}, m_size{size}, m_color{color}, m_speed{speed}
{

}

void Player::drawPlayer()
{
    DrawRectangleV(m_position, m_size, m_color);
}

void Player::moveUp()
{
    std::cout << "Moving UP\n";
    m_position.y -= m_speed;
}

void Player::moveDown()
{
    std::cout << "Moving DOWN\n";
    m_position.y += m_speed;
}

void Player::moveLeft()
{
    std::cout << "Moving LEFT\n";
    m_position.x -= m_speed;
}

void Player::moveRight()
{
    std::cout << "Moving RIGHT\n";
    m_position.x += m_speed;
}
