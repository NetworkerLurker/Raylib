#include "Drawing.h"
#include "Logic.h"

int main() {

    //Window settings
    constexpr int winWidth{960};
    constexpr int winHeight{static_cast<int>(winWidth * .75f)}; //we can change the winWidth and keep the same aspect ratio
    std::string title{"Dodger"};
    Window window{winWidth, winHeight, title.c_str()};
    window.initialize();
    Window::setDefaultFps(); //sets fps to monitors max refresh rate

    int frameCounter{0};

    //Colors
    Color fontColor{DARKBLUE};
    Color roadColor{DARKBLUE};
    Color roadMarkerColor{DARKBLUE};
    Color buildingsColor{DARKBLUE};
    Color racerColor{BLUE};
    Color statsColor{RAYWHITE};

    constexpr int halfHeight{static_cast<int>(winHeight * 0.5f)};

    constexpr int columns = 5;
    constexpr int rows = 5;

    //Audio settings
    InitAudioDevice();
    std::vector<Music> tracks{};
    std::string musicPath{"Music"};

    //Load music into vector
    for (const auto& entry : std::filesystem::directory_iterator(musicPath)) {
        tracks.push_back(LoadMusicStream(entry.path().c_str()));
    }

    int currentTrack{GetRandomValue(0, static_cast<int>(tracks.size() - 1))};
    PlayMusicStream(tracks[currentTrack]);
    float timePlayed{0};

    //Shape settings
    constexpr int rectWidth{winWidth / columns};
    constexpr int rectHeight{halfHeight / rows};

    //Player settings
    constexpr int startRow{1};
    constexpr int startColumn{2};
    Rectangle playerRect{rectWidth * startColumn, winHeight - (rectHeight * startRow), rectWidth, rectHeight};
    Player player{playerRect, DARKBLUE};

    //Player stats
    int score{0};
    int highscore{0};
    int playerDistanceTraveled;
    int playerSpeed{0};

    //Racer settings
    float row2Width{rectWidth * .75f};
    float row3Width{rectWidth *.50f};
    float row4Width{rectWidth *.25f};
    float row5Width{rectWidth *.12f};

    float row2Height{rectHeight *.75f};
    float row3Height{rectHeight *.50f};
    float row4Height{rectHeight *.25f};
    float row5Height{rectHeight *.12f};

    //Racer rectangles closest to furthest
    Rectangle leftRacer1{rectWidth * .5f, winHeight - (rectHeight * 1), rectWidth, rectHeight};
    Rectangle leftRacer2{rectWidth * 1, winHeight - (rectHeight * 2), row2Width, row2Height};
    Rectangle leftRacer3{rectWidth * 1.5, winHeight - (rectHeight * 3), row3Width, row3Height};
    Rectangle leftRacer4{rectWidth * 2, winHeight - (rectHeight * 4), row4Width, row4Height};
    Rectangle leftRacer5{rectWidth * 2.25f, winHeight - (rectHeight * 4.5), row5Width, row5Height};

    Rectangle middleRacer1{rectWidth * 2, winHeight - (rectHeight * 1), rectWidth, rectHeight};
    Rectangle middleRacer2{rectWidth * 2.12, winHeight - (rectHeight * 2), row2Width, row2Height};
    Rectangle middleRacer3{rectWidth * 2.25, winHeight - (rectHeight * 3), row3Width, row3Height};
    Rectangle middleRacer4{rectWidth * 2.37, winHeight - (rectHeight * 4), row4Width, row4Height};
    Rectangle middleRacer5{rectWidth * 2.44f, winHeight - (rectHeight * 4.5), row5Width, row5Height};

    Rectangle rightRacer1{rectWidth * 3.5f, winHeight - (rectHeight * 1), rectWidth, rectHeight};
    Rectangle rightRacer2{rectWidth * 3.25, winHeight - (rectHeight * 2), row2Width, row2Height};
    Rectangle rightRacer3{rectWidth * 3.0, winHeight - (rectHeight * 3), row3Width, row3Height};
    Rectangle rightRacer4{rectWidth * 2.75, winHeight - (rectHeight * 4), row4Width, row4Height};
    Rectangle rightRacer5{rectWidth * 2.63f, winHeight - (rectHeight * 4.5), row5Width, row5Height};

    std::array<Rectangle, 5> leftRacerRecs{leftRacer5, leftRacer4, leftRacer3, leftRacer2, leftRacer1};
    std::array<Rectangle, 5> middleRacerRecs{middleRacer5, middleRacer4, middleRacer3, middleRacer2, middleRacer1};
    std::array<Rectangle, 5> rightRacerRecs{rightRacer5, rightRacer4, rightRacer3, rightRacer2, rightRacer1};
    std::array<std::array<Rectangle , 5>, 3> allRacerRecs{leftRacerRecs, middleRacerRecs, rightRacerRecs};

    //Timings for movement in frames per second
    int racerMoveCooldown{0};
    int racerPosition{0};
    int baseRacerUpdateInterval{60};
    int minUpdateInterval{10};
    int racerUpdateInterval{baseRacerUpdateInterval};
    int timeToSpawn{baseRacerUpdateInterval * 2};
    int spawnCooldown{timeToSpawn};

    bool racerCanSpawn = false;

    //Creating racers
    Racer racerL{allRacerRecs, RacerType::leftRacer, racerMoveCooldown, racerUpdateInterval, racerPosition, racerCanSpawn, racerColor};
    Racer racerM{allRacerRecs, RacerType::midRacer, racerMoveCooldown, racerUpdateInterval, racerPosition, racerCanSpawn, racerColor};
    Racer racerR{allRacerRecs, RacerType::rightRacer, racerMoveCooldown, racerUpdateInterval, racerPosition, racerCanSpawn, racerColor};

    //Load highscore
    std::ofstream playerHSFile{};
    std::ifstream inputPlayerHSFile{"save.txt"};
    inputPlayerHSFile >> highscore;

    //Set entry state
    auto currentState{GameState::logo};

    //Game loop
    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);


        UpdateMusicStream(tracks[currentTrack]);
        timePlayed = GetMusicTimePlayed(tracks[currentTrack])/GetMusicTimeLength(tracks[currentTrack]);
        autoPlayTracks(tracks, timePlayed, currentTrack);

        switch(currentState) {
            case GameState::logo : {

                if(frameCounter > GetFPS() * 2) {
                    currentState = GameState::title;
                    frameCounter = 0;
                }

                drawLogoScreen(window, frameCounter, 126, fontColor);

                frameCounter++;

            } break;

            case GameState::title : {

                if(IsKeyPressed(KEY_SPACE))
                    currentState = GameState::game;

                DrawText("Dodger", winWidth * .25f, winHeight * .25f, 124, fontColor);
                DrawText("Press Space To Start", winWidth * .10f, halfHeight, 64, fontColor);

            } break;

            case GameState::game : {

                playerDistanceTraveled = (180 - (playerSpeed * 2) ) * frameCounter / GetFPS();

                if(IsKeyReleased(KEY_W)) {
                    increaseRacerSpeed(racerL, minUpdateInterval, timeToSpawn);
                    increaseRacerSpeed(racerM, minUpdateInterval, timeToSpawn);
                    increaseRacerSpeed(racerR, minUpdateInterval, timeToSpawn);
                }

                if(spawnCooldown > timeToSpawn) {
                    switch(GetRandomValue(1, 3)) {
                        case 1: racerL.spawn(); break;
                        case 2: racerM.spawn(); break;
                        case 3: racerR.spawn(); break;
                    }

                    spawnCooldown = 0;
                }

                //Increase player speed based on "fastest" racer
                if(racerL.getUpdateInterval() < racerM.getUpdateInterval() && racerR.getUpdateInterval()) {
                    playerSpeed = racerL.getUpdateInterval();
                }
                else if(racerM.getUpdateInterval() < racerL.getUpdateInterval() && racerR.getUpdateInterval()) {
                    playerSpeed = racerM.getUpdateInterval();
                }
                else {
                    playerSpeed = racerR.getUpdateInterval();
                }

                //Background gradient
                DrawRectangleGradientV(0,0,winWidth, halfHeight, DARKBLUE, RAYWHITE);
                DrawRectangleGradientV(0, halfHeight, winWidth, winHeight, RAYWHITE, GRAY);

                //Draw environment
                drawRoad(window, roadColor);
                drawRoadMarkers(window, roadMarkerColor);
                drawBuildings(window, buildingsColor);

                drawStats(window, score, 36, playerSpeed, playerDistanceTraveled, statsColor);

                //Racer behavior
                controlRacer(racerL, currentState, player, score);
                controlRacer(racerM, currentState, player, score);
                controlRacer(racerR, currentState, player, score);

                //Player behavior
                checkMove(player, columns);
                player.draw();

                ++spawnCooldown;
                ++frameCounter;
            } break;

            case GameState::end : {

                //Reset variables for new game
                resetRacer(racerL);
                resetRacer(racerM);
                resetRacer(racerR);

                timeToSpawn = baseRacerUpdateInterval * 2;
                playerSpeed = baseRacerUpdateInterval;
                frameCounter = 0;

                updateSaveHighscore(score, highscore, playerHSFile);

                score = 0;

                drawRoad(window, roadColor);
                drawRoadMarkers(window, roadMarkerColor);
                drawGameOverScreen(window, highscore, 36, fontColor);

                if(IsKeyPressed(KEY_R)) {
                    currentState = GameState::game;
                }

            } break;
        }

        EndDrawing();
    }

    UnloadMusicStream(tracks[currentTrack]);
    CloseAudioDevice();

    return 0;
}
