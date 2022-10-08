//
// Created by Justice Bole on 10/8/22.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H
#include <iostream>

#include <raylib.h>

class Player
{
private:
    Vector2 m_position{};
    Vector2 m_size{};
    Color m_color{};
    float m_speed{};

public:
    Player(const Vector2& pos, const Vector2& size, const Color& color, float speed);

    void drawPlayer();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void dontMove();

    Vector2 getPosition();
    float getSpeed();

};

#endif //RPG_PLAYER_H
