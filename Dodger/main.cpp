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
    std::array<float, 5> sizeScalers{0.12, 0.25f, 0.50f, 0.75f, 1.00f};
    std::array<float, 5> yPositions{4.5f, 4.0f, 3.0f, 2.0f, 1.0f};
    std::array<float, 5> xPositionsL{2.25f, 2.00, 1.50f, 1.00f, 0.50f};
    std::array<float, 5> xPositionsM{2.44f, 2.37f, 2.25f, 2.12f, 2.00f};
    std::array<float, 5> xPositionsR{2.63f, 2.75f, 3.00f, 3.25f, 3.50f};
    std::array<Rectangle, 5> leftRacerRecs{};
    std::array<Rectangle, 5> midRacerRecs{};
    std::array<Rectangle, 5> rightRacerRecs{};

    for(int i{0}; i < leftRacerRecs.size(); ++i) {
        {
            leftRacerRecs[i] = Rectangle{rectWidth * xPositionsL[i], winHeight - (rectHeight * yPositions[i]),
                                         rectWidth * sizeScalers[i], rectHeight * sizeScalers[i]};
        }
    }

    for(int i{0}; i < midRacerRecs.size(); ++i) {
        {
            midRacerRecs[i] = Rectangle{rectWidth * xPositionsM[i], winHeight - (rectHeight * yPositions[i]),
                                        rectWidth * sizeScalers[i], rectHeight * sizeScalers[i]};
        }
    }

    for(int i{0}; i < rightRacerRecs.size(); ++i) {
        {
            rightRacerRecs[i] = Rectangle{rectWidth * xPositionsR[i], winHeight - (rectHeight * yPositions[i]),
                                          rectWidth * sizeScalers[i], rectHeight * sizeScalers[i]};
        }
    }

    std::array<std::array<Rectangle , 5>, 3> allRacerRecs{leftRacerRecs, midRacerRecs, rightRacerRecs};

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
