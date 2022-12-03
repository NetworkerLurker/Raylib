//
// Created by Justice Bole on 12/3/22.
//

#ifndef DODGER_LOGIC_H
#define DODGER_LOGIC_H

#include <vector>
#include <fstream>
#include "Racer.h"
#include "Player.h"

enum class GameState {
    logo,
    title,
    game,
    end,
};

void autoPlayTracks(std::vector<Music>& tracks, float& timePlayed, int& currentTrack);
void checkMove(Player& player, int columns);
void controlRacer(Racer& racer, GameState& currentState, Player& player, int& score);
void increaseRacerSpeed(Racer& racer, int minUpdate, int& timeToSpawn);
void resetRacer(Racer& racer);
void updateSaveHighscore(int& score, int& highscore, std::ofstream& osFile);

#endif //DODGER_LOGIC_H
