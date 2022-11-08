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
        DrawRectangleRec(getRec(), getColor());
    }

    void moveLeft() {
        m_rect.x -= m_rect.width;
    }

    void moveRight() {
        m_rect.x += m_rect.width;
    }

    void changeColor(Color c) { m_color = c; }

    [[nodiscard]] Rectangle getRec() const { return m_rect; }
    [[nodiscard]] Color getColor() const { return m_color; }

};

#endif //DODGER_PLAYER_H
