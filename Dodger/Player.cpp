//
// Created by Justice Bole on 11/30/22.
//
#include "Player.h"

Player::Player(Rectangle& rec, Color&& color = GREEN) :
        m_rect{rec}, m_color{color} { }

Player::Player(Rectangle& rec, Color& color) :
        m_rect{rec}, m_color{color} { }

void Player::draw() const {
    DrawRectangleLinesEx(getRec(), 4, getColor());
}

void Player::moveLeft() {
    m_rect.x -= m_rect.width * 1.5f;
}

void Player::moveRight() {
    m_rect.x += m_rect.width * 1.5;
}

void Player::changeColor(Color c) { m_color = c; }

[[nodiscard]] Rectangle Player::getRec() const { return m_rect; }
[[nodiscard]] Color Player::getColor() const { return m_color; }
