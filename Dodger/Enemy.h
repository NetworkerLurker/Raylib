//
// Created by Justice Bole on 10/21/22.
//

#ifndef DODGER_ENEMY_H
#define DODGER_ENEMY_H

#include <raylib.h>
#include "Window.h"

class Enemy {
private:
    Rectangle m_rec{};
    float m_speed{};
    Color m_color{};

public:
    Enemy() = default;

    Enemy(Rectangle& rec, float speed, Color&& color = RED) :
            m_rec{rec}, m_speed{speed} , m_color{color} { }

    void draw() const {
        DrawRectangleRec(getRec(), getColor());
    }

    void move() {
        m_rec.y += m_speed * GetFrameTime();
    }

    void resetPosition(Window& win) {
        m_rec.y = 0;
        int position{GetRandomValue(1,4)};
        switch(position) {
            case 1: m_rec.x = 0; break;
            case 2: m_rec.x = m_rec.x =  win.getWidth() / 4; break;
            case 3: m_rec.x = win.getWidth() / 2; break;
            case 4: m_rec.x = win.getWidth() - m_rec.width; break;
            default: m_rec.x = 0;
        }
    }

    [[nodiscard]] Rectangle getRec() const { return m_rec; }
    [[nodiscard]] float getSpeed() const { return m_speed + GetTime() * 3; }
    [[nodiscard]] Color getColor() const { return m_color; }
};

#endif //DODGER_ENEMY_H
