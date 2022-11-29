//
// Created by Justice Bole on 10/20/22.
//

#ifndef DODGER_PLAYER_H
#define DODGER_PLAYER_H

#include <raylib.h>

class Player {
private:
    Rectangle m_rect{};
    Color m_color{};

public:
    explicit Player(Rectangle& rec, Color&& color = GREEN) :
        m_rect{rec}, m_color{color} { }

    explicit Player(Rectangle& rec, Color& color) :
            m_rect{rec}, m_color{color} { }

    void draw() const {
        DrawRectangleLinesEx(getRec(), 4, getColor());
    }

    void moveLeft() {
        m_rect.x -= m_rect.width * 1.5f;
    }

    void moveRight() {
        m_rect.x += m_rect.width * 1.5;
    }

    void changeColor(Color c) { m_color = c; }

    [[nodiscard]] Rectangle getRec() const { return m_rect; }
    [[nodiscard]] Color getColor() const { return m_color; }

};

#endif //DODGER_PLAYER_H
