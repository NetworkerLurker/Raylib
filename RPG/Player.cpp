//
// Created by Justice Bole on 10/8/22.
//
#include "Player.h"


Player::Player(const Vector2& pos, const Vector2& size, const Color& color) :
        m_position{pos}, m_size{size}, m_color{color}
{

}

void Player::drawPlayer()
{
    DrawRectangleV(m_position, m_size, m_color);
}

void Player::moveUp()
{
    std::cout << "Moving UP\n";
    m_position.y -= 1;
}

void Player::moveDown()
{
    std::cout << "Moving DOWN\n";
    m_position.y += 1;
}

void Player::moveLeft()
{
    std::cout << "Moving LEFT\n";
    m_position.x -= 1;
}

void Player::moveRight()
{
    std::cout << "Moving RIGHT\n";
    m_position.x += 1;
}
