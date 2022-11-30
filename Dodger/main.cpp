#include <iostream>

#include <raylib.h>
#include <array>
#include <fstream>

#include "Window.h"
#include "Player.h"
#include "Racer.h"

enum class GameState {
    logo,
    title,
    game,
    end,
    maxstates,
};

void checkMove(Player& player, int columns);
void drawRoad(int winHeight, int winWidth, int halfHeight, int halfWidth , Color&& color);
void drawRoadMarkers(int winHeight, int winWidth, int halfHeight, int halfWidth , Color&& color);

int main() {

    std::ofstream data{};

    //Window settings
    constexpr int winWidth{960};
    constexpr int winHeight{static_cast<int>(winWidth * .75f)}; //we can change the winWidth and keep the same aspect ratio
    Window window{winWidth, winHeight, "Dodger"};
    window.initialize();
    Window::setDefaultFps(); //sets fps to monitors max refresh rate

    //Audio settings
    InitAudioDevice();
    Music song1{LoadMusicStream("Music/Line%20Noise%20-%20Magenta%20Moon%20%28Part%20II%29.mp3")};
    PlayMusicStream(song1);

    constexpr int halfWidth{static_cast<int>(winWidth * 0.5f)};
    constexpr int halfHeight{static_cast<int>(winHeight * 0.5f)};

    constexpr int columns = 5;
    constexpr int rows = 5;

    //SHAPE SETTINGS
    constexpr int rectWidth{winWidth / columns};
    constexpr int rectHeight{halfHeight / rows};

    //player
    constexpr int startRow{1};
    constexpr int startColumn{2};
    Rectangle playerRect{rectWidth * startColumn, winHeight - (rectHeight * startRow), rectWidth, rectHeight};
    Player player{playerRect, DARKBLUE};

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

    int baseRacerSpeed{60};
    int minSpeed{10};
    int leftSpeed{baseRacerSpeed};
    int midSpeed{baseRacerSpeed};
    int rightSpeed{baseRacerSpeed};
    int speed{0};

    int timeToSpawn{baseRacerSpeed * 2};
    int spawnTime{timeToSpawn};

    bool leftSpawn = false;
    bool midSpawn = false;
    bool rightSpawn = false;

    int score{0};
    int highscore{0};
    int distance{0};

    int frameCounter{0};

    auto currentState{GameState::logo};

    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch(currentState) {
            case GameState::logo : {

                if(frameCounter > GetFPS() * 2) {
                    currentState = GameState::title;
                    frameCounter = 0;
                }

                std::ifstream iData{"save.txt"};
                int tempVar;
                iData >> tempVar;
                highscore = tempVar;

                DrawText("Loading", winHeight / 2, halfHeight, 124, DARKBLUE);
                DrawLine(3 * frameCounter, 0, 3 * frameCounter, winHeight, DARKBLUE);
                DrawLine(0, 2 * frameCounter, winWidth, 2 * frameCounter, DARKBLUE);

                frameCounter++;
            } break;

            case GameState::title : {

                if(IsKeyPressed(KEY_SPACE)) {
                    currentState = GameState::game;
                }
                DrawText("Dodger", winWidth * .25f, winHeight * .25, 124, DARKBLUE);
                DrawText("Press Space To Start", winWidth * .10f, winHeight / 2, 64, DARKBLUE);

            } break;

            case GameState::game : {

                UpdateMusicStream(song1);
                distance = (180 - (speed * 2) ) * frameCounter / GetFPS();

                if(IsKeyReleased(KEY_W)) {
                    if(leftSpeed > minSpeed) {
                        --leftSpeed;
                        timeToSpawn = leftSpeed * 2;
                    }
                    if(midSpeed > minSpeed) {
                        --midSpeed;
                        timeToSpawn = midSpeed * 2;
                    }
                    if(rightSpeed > minSpeed) {
                        --rightSpeed;
                        timeToSpawn = rightSpeed * 2;
                    }
                }

                if(spawnTime > timeToSpawn) {
                    switch(GetRandomValue(1, 4)) {
                        case 1: leftSpawn = true; break;
                        case 2: midSpawn = true; break;
                        case 3: rightSpawn = true; break;
                    }

                    spawnTime = 0;
                }

                if(leftSpeed < rightSpeed && midSpeed) {
                    speed = leftSpeed;
                } else if ( midSpeed < rightSpeed && leftSpeed ) {
                    speed = midSpeed;
                } else
                {
                    speed = rightSpeed;
                }

                checkMove(player, columns);
                player.draw();

                DrawText(TextFormat("Dodges: %i",score),winWidth * .70f,winHeight * .05f,36,DARKBLUE);
                DrawText(TextFormat("Speed: %imph",180 - (speed * 2)),winWidth * .70f,winHeight * .10f,36,DARKBLUE);
                DrawText(TextFormat("Distance: %i'",distance),winWidth * .70f,winHeight * .15f,36,DARKBLUE);


                drawRoad(winHeight, winWidth, halfHeight, halfWidth , DARKBLUE);
                drawRoadMarkers(winHeight, winWidth, halfHeight, halfWidth , DARKBLUE);

                if(leftSpawn) {
                    DrawRectangleLinesEx(allRacerRecs[static_cast<int>(Racers::leftRacer)][leftPosition], leftPosition + 1, GREEN);
                    ++lt;

                    if(CheckCollisionRecs(allRacerRecs[static_cast<int>(Racers::leftRacer)][leftPosition], player.getRec())) {
                        currentState = GameState::end;
                    }

                    if(lt > leftSpeed) {
                        ++leftPosition;
                        lt = 0;
                        if (leftPosition > leftRacerRecs.size() - 1) {
                            score++;
                            leftPosition = 0;
                            lt = 0;
                            if(leftSpeed > minSpeed) {
                                --leftSpeed;
                            }
                            leftSpawn = false;
                        }
                    }
                }

                if(midSpawn) {
                    DrawRectangleLinesEx(allRacerRecs[static_cast<int>(Racers::midRacer)][midPosition], midPosition + 1, GREEN);
                    ++mt;

                    if(CheckCollisionRecs(allRacerRecs[static_cast<int>(Racers::midRacer)][midPosition], player.getRec())) {
                        currentState = GameState::end;
                    }

                    if(mt > midSpeed) {
                        ++midPosition;
                        mt = 0;

                        if (midPosition > middleRacerRecs.size() - 1) {
                            score++;
                            midPosition = 0;
                            mt = 0;
                            if(midSpeed > minSpeed) {
                                --midSpeed;
                            }
                            midSpawn = false;
                        }
                    }
                }

                if(rightSpawn) {
                    DrawRectangleLinesEx(allRacerRecs[static_cast<int>(Racers::rightRacer)][rightPosition], rightPosition + 1, GREEN);
                    ++rt;

                    if(CheckCollisionRecs(allRacerRecs[static_cast<int>(Racers::rightRacer)][rightPosition], player.getRec())) {
                        currentState = GameState::end;
                    }

                    if(rt > rightSpeed) {
                        ++rightPosition;
                        rt = 0;

                        if (rightPosition > rightRacerRecs.size() - 1) {
                            score++;
                            rightPosition = 0;
                            rt = 0;
                            if(rightSpeed > minSpeed) {
                                --rightSpeed;
                            }
                            rightSpawn = false;
                        }
                    }

                }

                ++spawnTime;
                ++frameCounter;
            } break;

            case GameState::end : {

                leftPosition = 0;
                midPosition = 0;
                rightPosition = 0;

                lt = 0;
                mt = 0;
                rt = 0;

                leftSpawn = false;
                midPosition = false;
                rightPosition = false;

                leftSpeed = baseRacerSpeed;
                midSpeed = baseRacerSpeed;
                rightSpeed = baseRacerSpeed;

                if(score > highscore) {
                    highscore = score;
                    data.open("save.txt");
                    data << highscore;
                    data.close();
                }

                score = 0;
                timeToSpawn = baseRacerSpeed * 2;
                speed = baseRacerSpeed;
                frameCounter = 0;

                drawRoad(winHeight, winWidth, halfHeight, halfWidth , DARKBLUE);
                drawRoadMarkers(winHeight, winWidth, halfHeight, halfWidth , DARKBLUE);

                DrawText("Press R To Retry", winWidth * .35f, winHeight * .30f, 36, DARKBLUE);
                DrawText("Press ESC To Quit", winWidth * .35f, winHeight * .40f, 36, DARKBLUE);

                DrawText("Highscore:", winWidth * .40f, winHeight * .20f, 36, DARKBLUE);
                DrawText(TextFormat("%i",highscore),winWidth * .61f,winHeight * .20f,36,DARKBLUE);


                if(IsKeyPressed(KEY_R)) {
                    currentState = GameState::game;
                }

            } break;
        }

        EndDrawing();
    }

    UnloadMusicStream(song1);
    CloseAudioDevice();

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
}

void drawRoadMarkers(int winHeight, int winWidth, int halfHeight, int halfWidth , Color&& color) {
    DrawLine(halfWidth, halfHeight, winWidth * .30f, winHeight, color); // left lines
    DrawLine(halfWidth, halfHeight, winWidth * .70f, winHeight, color); // right lines
}

