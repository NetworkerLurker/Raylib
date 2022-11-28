#include <iostream>

#include <raylib.h>
#include <array>

#include "Window.h"
#include "Player.h"
#include "Enemy.h"

void checkMove(Player& player, int columns);
void emove(Enemy& enemy, Window& win, int rows, int cols, int maxHeight, int minWidth, int minHeight);

int main() {

    //Window settings
    constexpr int winWidth{640};
    constexpr int winHeight{static_cast<int>(winWidth * .75f)}; //we can change the winWidth and keep the same aspect ratio
    Window window{winWidth, winHeight, "Dodger"};
    Window::setDefaultFps();

    constexpr int columns = 3;
    constexpr int rows = 5;

    //SHAPE SETTINGS
    constexpr int rectWidth{winWidth / columns}; //window will always be 4 squares wide
    constexpr int rectHeight{winHeight / rows};

    //player
    constexpr int startRow{2};
    Rectangle playerRect{0, winHeight - (rectHeight * startRow), rectWidth, rectHeight};
    Player player{playerRect, RED};


    //enemy
    constexpr int minWidth{rectWidth / columns};
    constexpr int minHeight{rectHeight / rows};
    Rectangle enemyRect{0,0,minWidth, minHeight};
    const int enemyCount{10};
    float speed{300.0f};
    std::array<Enemy, enemyCount> enemies{};
    for(int i{0}; i < enemyCount; ++i) {
        enemies[i] = Enemy{enemyRect, speed};
    }


    int t{0};
    int tt{0};
    int at{0};
    bool turning = true;
    bool set1 = true;

    Vector2 leftTurnRoadStart{winWidth/2.0, 0};
    Vector2 leftTurnRoadEnd{0, winHeight};
    Vector2 leftControlPoint{(leftTurnRoadStart.x + leftTurnRoadEnd.x) / 4, (leftTurnRoadStart.y + leftTurnRoadEnd.y) / 2};

    Vector2 rightTurnRoadStart{winWidth, 0};
    Vector2 rightTurnRoadEnd{winWidth / 1, winHeight};
    Vector2 rightControlPoint{(rightTurnRoadStart.x + rightTurnRoadEnd.x) / 3, (rightTurnRoadStart.y + rightTurnRoadEnd.y) / 2};

    while(!WindowShouldClose()) {

        //draw grid
        //horizontal lines
//        for(int i{0}; i < (winHeight/rectHeight); ++i) {
//            DrawLine(0, rectHeight * i, winWidth, rectHeight * i, RED);
//        }
//        //vertical lines
//        for(int i{0}; i < (winWidth/rectWidth); ++i) {
//            DrawLine(rectWidth * i, 0, rectWidth * i, winHeight, RED);
//        }

        //road
        if(!turning) {
            DrawLine(winWidth / 2.5, 0, 0, winHeight, RED); //left road edge

            DrawLine(winWidth * .6, 0, winWidth, winHeight, RED); //right road edge

            //road lines - alternate between road line sets to give appearance of movement
            if(set1) {
                DrawLine(winWidth/2, 1 * rectHeight, winWidth/2, rectHeight * 2, RED);
                DrawLine(winWidth/2, 3 * rectHeight, winWidth/2, rectHeight * 4, RED);
            }
            else {
                DrawLine(winWidth/2, 0 * rectHeight, winWidth/2, rectHeight * 1, RED);
                DrawLine(winWidth/2, 2 * rectHeight, winWidth/2, rectHeight * 3, RED);
                DrawLine(winWidth/2, 4 * rectHeight, winWidth/2, rectHeight * 5, RED);
            }


        }
        else {
            DrawLineBezierQuad(leftTurnRoadStart, leftTurnRoadEnd, leftControlPoint, 1.0f, RED);
            DrawLineBezierQuad(rightTurnRoadStart, rightTurnRoadEnd, rightControlPoint, 1.0f, RED);

            if(set1) {
                DrawLine(winWidth/1.65, 1 * rectHeight, winWidth/1.90, rectHeight * 1.85, RED);
                DrawLine(winWidth/2.0, 3 * rectHeight, winWidth/2, rectHeight * 4, RED);
            }
            else {
                DrawLine(winWidth/1.40, 0 * rectHeight, winWidth/1.60, rectHeight * .80, RED);
                DrawLine(winWidth/1.90, 2 * rectHeight, winWidth/2, rectHeight * 3, RED);
                DrawLine(winWidth/2, 4 * rectHeight, winWidth/2, rectHeight * 5, RED);
            }
        }


        if(CheckCollisionRecs(player.getRec(), enemies[0].getRec())) {
            exit(0);
        }

        BeginDrawing();

        ClearBackground(BLACK);
        player.draw();
        enemies[0].draw();

        checkMove(player, columns);

        //Move enemy once every 100 frames
        if(t >= 50) {
            emove(enemies[0], window, rows, columns, rectHeight, minHeight, minWidth);
            t = 0;


        }

        if(at >= 10) {
            if(set1) {
                set1 = false;
            }
            else {
                set1 = true;
            }
            at = 0;
        }

        if(tt >= 600 && !turning) {
            turning = true;
            tt = 0;
        }
        if (tt >= 300 && turning) {
            turning = false;
            tt = 0;
        }

        EndDrawing();

        ++t;
        ++tt;
        ++at;

    }

    return 0;
}

void checkMove(Player& player, int columns) {
    if(IsKeyPressed(KEY_A) && player.getRec().x > 0) {
        player.moveLeft();
    } else if (IsKeyPressed(KEY_D) && player.getRec().x < player.getRec().width * (columns - 1)) {
        player.moveRight();
    }
}

void emove(Enemy& enemy, Window& win, int rows, int cols, int maxHeight, int minHeight, int minWidth) {
    enemy.moveDown(maxHeight);
    enemy.grow(rows, cols);
    if(enemy.getRec().y >= win.getHeight()) {
        enemy.resetPosition(cols);
        enemy.resetSize(minWidth, minHeight);
    }
}
