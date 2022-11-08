#include <iostream>

#include <raylib.h>
#include <array>

#include "Window.h"
#include "Player.h"
#include "Enemy.h"

void checkMove(Player& player);
void emove(Enemy& enemy, Window& win);

int main() {

    //Window settings
    constexpr int winWidth{500};
    constexpr int winHeight{static_cast<int>(winWidth * 1.5f)}; //we can change the winWidth and keep the same aspect ratio
    Window window{winWidth, winHeight, "Dodger"};
    Window::setFps();

    //colors
    std::array<Color, 6> colors = {YELLOW, ORANGE, RED, GREEN, BLUE, VIOLET};
    int ci{0};

    //SHAPE SETTINGS
    //player
    constexpr int rectSize{winWidth / 4}; //window will always be 4 squares wide
    Rectangle playerRect{0, winHeight - rectSize, rectSize, rectSize};
    Player player{playerRect, colors[ci]};

    //enemy
    Rectangle enemyRect{0,-rectSize,rectSize, rectSize};
    const int enemyCount{10};
    float speed{300.0f};
    std::array<Enemy, enemyCount> enemies{};
    for(int i{0}; i < enemyCount; ++i) {
        enemies[i] = Enemy{enemyRect, speed};
    }
    int j{0};

    while(!WindowShouldClose()) {

        if(j == enemyCount - 1) { j = 0; }

        //make sure rectangles spawn evenly spaced relative to existing rectangles
        int evenPoint = window.getHeight() % static_cast<int>(enemies[0].getRec().y);

        if(CheckCollisionRecs(player.getRec(), enemies[j].getRec())) {
            break;
        }

        if(CheckCollisionRecs(enemies[j].getRec(),enemies[j+1].getRec())) {
            enemies[j].resetPosition(window);
            enemies[j+1].resetPosition(window);
        }

        BeginDrawing();

        ClearBackground(BLACK);
        player.draw();
        enemies[j].draw();

        checkMove(player);
        emove(enemies[j], window);

        EndDrawing();

        ++j;

    }

    return 0;
}

void checkMove(Player& player) {
    if(IsKeyPressed(KEY_A) && player.getRec().x > 0) {
        player.moveLeft();
    } else if (IsKeyPressed(KEY_D) && player.getRec().x < (static_cast<float>(player.getRec().width) * 3)) {
        player.moveRight();
    }
}

void emove(Enemy& enemy, Window& win) {
    enemy.move();
    if(enemy.getRec().y > win.getHeight() + enemy.getRec().height) {
        enemy.resetPosition(win);
    }
}
