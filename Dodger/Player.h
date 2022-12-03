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
    explicit Player(Rectangle& rec, Color&& color);

    void draw() const;
    void moveLeft();
    void moveRight();

    [[nodiscard]] Color getColor() const;
    [[nodiscard]] Rectangle getRec() const;
};

#endif //DODGER_PLAYER_H
