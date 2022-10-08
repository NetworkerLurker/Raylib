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

public:
    Player(const Vector2& pos, const Vector2& size, const Color& color);

    void drawPlayer();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

};

#endif //RPG_PLAYER_H
