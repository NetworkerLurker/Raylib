#include <iostream>

#include <raylib.h>
#include <array>

#include "Window.h"
#include "Player.h"
#include "Enemy.h"

void checkMove(Player& player, int columns);
void drawRoad(int winHeight, int winWidth, int halfHeight, int halfWidth , Color&& color);

enum class Racers {
    leftRacer,
    midRacer,
    rightRacer,
    maxRacers,
};

int main() {

    //Window settings
    constexpr int winWidth{960};
    constexpr int winHeight{static_cast<int>(winWidth * .75f)}; //we can change the winWidth and keep the same aspect ratio
    Window window{winWidth, winHeight, "Dodger"};
    Window::setDefaultFps();

    constexpr int halfWidth{static_cast<int>(winWidth * 0.5f)};
    constexpr int halfHeight{static_cast<int>(winHeight * 0.5f)};

    constexpr int columns = 5;
    constexpr int rows = 5;

    //SHAPE SETTINGS
    constexpr int rectWidth{winWidth / columns}; //window will always be 4 squares wide
    constexpr int rectHeight{halfHeight / rows};

    //player
    constexpr int startRow{1};
    constexpr int startColumn{2};
    Rectangle playerRect{rectWidth * startColumn, winHeight - (rectHeight * startRow), rectWidth, rectHeight};
    Player player{playerRect, RED};

    //racers
    
    float row2Width{rectWidth * .75f};
    float row3Width{rectWidth *.50f};
    float row4Width{rectWidth *.25f};
    float row5Width{rectWidth *.12};
    
    float row2Height{rectHeight *.75f};
    float row3Height{rectHeight *.50f};
    float row4Height{rectHeight *.25f};
    float row5Height{rectHeight *.12f};
    
    //closest to furthest
    Rectangle leftRacer1{rectWidth * .5f, winHeight - (rectHeight * 1), rectWidth, rectHeight};
    Rectangle middleRacer1{rectWidth * 2, winHeight - (rectHeight * 1), rectWidth, rectHeight};
    Rectangle rightRacer1{rectWidth * 3.5f, winHeight - (rectHeight * 1), rectWidth, rectHeight};

    Rectangle leftRacer2{rectWidth * 1, winHeight - (rectHeight * 2), row2Width, row2Height};
    Rectangle middleRacer2{rectWidth * 2.12, winHeight - (rectHeight * 2), row2Width, row2Height};
    Rectangle rightRacer2{rectWidth * 3.25, winHeight - (rectHeight * 2), row2Width, row2Height};

    Rectangle leftRacer3{rectWidth * 1.5, winHeight - (rectHeight * 3), row3Width, row3Height};
    Rectangle middleRacer3{rectWidth * 2.25, winHeight - (rectHeight * 3), row3Width, row3Height};
    Rectangle rightRacer3{rectWidth * 3.0, winHeight - (rectHeight * 3), row3Width, row3Height};

    Rectangle leftRacer4{rectWidth * 2, winHeight - (rectHeight * 4), row4Width, row4Height};
    Rectangle middleRacer4{rectWidth * 2.37, winHeight - (rectHeight * 4), row4Width, row4Height};
    Rectangle rightRacer4{rectWidth * 2.75, winHeight - (rectHeight * 4), row4Width, row4Height};

    Rectangle leftRacer5{rectWidth * 2.25f, winHeight - (rectHeight * 4.5), row5Width, row5Height};
    Rectangle middleRacer5{rectWidth * 2.44f, winHeight - (rectHeight * 4.5), row5Width, row5Height};
    Rectangle rightRacer5{rectWidth * 2.63f, winHeight - (rectHeight * 4.5), row5Width, row5Height};

    std::array<Rectangle, 5> leftRacerRecs{leftRacer5, leftRacer4, leftRacer3, leftRacer2, leftRacer1};
    std::array<Rectangle, 5> middleRacerRecs{middleRacer5, middleRacer4, middleRacer3, middleRacer2, middleRacer1};
    std::array<Rectangle, 5> rightRacerRecs{rightRacer5, rightRacer4, rightRacer3, rightRacer2, rightRacer1};

    std::array<std::array<Rectangle , 5>, 3> allRacerRecs{leftRacerRecs, middleRacerRecs, rightRacerRecs};

    int leftPosition{0};
    int midPosition{0};
    int rightPosition{0};

    int lt{0};
    int mt{0};
    int rt{0};

    int timeToSpawn{80};
    int spawnTime{timeToSpawn};


    bool leftSpawn = false;
    bool midSpawn = false;
    bool rightSpawn = false;

    while(!WindowShouldClose()) {

        BeginDrawing();

        drawRoad(winHeight, winWidth, halfHeight, halfWidth , RED);



        if(spawnTime > timeToSpawn) {
            switch(GetRandomValue(1, 3)) {
                case 1: leftSpawn = true; break;
                case 2: midSpawn = true; break;
                case 3: rightSpawn = true; break;
            }
            spawnTime = 0;
        }


        if(leftSpawn) {
            DrawRectangleLinesEx(allRacerRecs[static_cast<int>(Racers::leftRacer)][leftPosition], leftPosition + 1, GREEN);
            ++lt;
            if(CheckCollisionRecs(allRacerRecs[static_cast<int>(Racers::leftRacer)][leftPosition], player.getRec())) {
                player.changeColor(PURPLE);
            }
            if(lt > 60) {
                ++leftPosition;
                lt = 0;
                if (leftPosition > leftRacerRecs.size() - 1) {

                    leftPosition = 0;
                    lt = 0;
                    leftSpawn = false;
                }
            }
        }


        if(midSpawn) {
            DrawRectangleLinesEx(allRacerRecs[static_cast<int>(Racers::midRacer)][midPosition], midPosition + 1, GREEN);
            ++mt;
            if(CheckCollisionRecs(allRacerRecs[static_cast<int>(Racers::midRacer)][midPosition], player.getRec())) {
                player.changeColor(PURPLE);
            }
            if(mt > 60) {
                ++midPosition;
                mt = 0;
                if (midPosition > middleRacerRecs.size() - 1) {
                    midPosition = 0;
                    mt = 0;
                    midSpawn = false;
                }
            }
        }

        if(rightSpawn) {
            DrawRectangleLinesEx(allRacerRecs[static_cast<int>(Racers::rightRacer)][rightPosition], rightPosition + 1, GREEN);
            ++rt;
            if(CheckCollisionRecs(allRacerRecs[static_cast<int>(Racers::rightRacer)][rightPosition], player.getRec())) {
                player.changeColor(PURPLE);
            }
            if(rt > 60) {
                ++rightPosition;
                rt = 0;
                if (rightPosition > rightRacerRecs.size() - 1) {
                    rightPosition = 0;
                    rt = 0;
                    rightSpawn = false;
                }
            }
        }


        ClearBackground(BLACK);
        player.draw();

        checkMove(player, columns);

        EndDrawing();

        ++spawnTime;

    }

    return 0;
}

void checkMove(Player& player, int columns) {
    if(IsKeyPressed(KEY_A) && player.getRec().x > player.getRec().width) {
        player.moveLeft();
    }
    else if (IsKeyPressed(KEY_D) && player.getRec().x < player.getRec().width * (columns - 2)) {
        player.moveRight();
    }
}

void drawRoad(int winHeight, int winWidth, int halfHeight, int halfWidth , Color&& color) {
    //horizon line
    DrawLine(0, halfHeight, winWidth, halfHeight, color);

    //road
    DrawLine(halfWidth, halfHeight, 0, winHeight, color);        //left road edge
    DrawLine(halfWidth, halfHeight, winWidth, winHeight, color); //right road edge

    //road lines
    DrawLine(halfWidth, halfHeight, winWidth * .30f, winHeight, color); // left lines
    DrawLine(halfWidth, halfHeight, winWidth * .70f, winHeight, color); // right lines
}
