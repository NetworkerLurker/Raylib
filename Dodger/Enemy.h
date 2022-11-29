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
        DrawRectangleLinesEx(getRec(), 2, getColor());
    }

    void moveDown(int maxHeight) {
        m_rec.y += maxHeight;
    }

    void grow(int minHeight, int minWidth) {
        m_rec.height *= 1.5;
        m_rec.width *= 1.5;
    }

    void resetPosition(Window& win) {
        m_rec.y = win.getHeight() / 2;

        int randNum{GetRandomValue(1,3)};
        switch(randNum) {
            case 1 : m_rec.x = win.getWidth() / 2; break;
            case 2 : m_rec.x = win.getWidth() / 2.3;break;
            case 3 : m_rec.x = win.getWidth() / 1.9;break;
            default: std::cout << "error finding reset location for enemy";
        }
    }

    void resetSize(int minWidth, int minHeight) {
        m_rec.width = minWidth;
        m_rec.height = minHeight;
    }

    [[nodiscard]] Rectangle getRec() const { return m_rec; }
    [[nodiscard]] float getSpeed() const { return m_speed + GetTime() * 3; }
    [[nodiscard]] Color getColor() const { return m_color; }
};

#endif //DODGER_ENEMY_H
