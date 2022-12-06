//
// Created by Justice Bole on 12/3/22.
//

#include "Logic.h"

void autoPlayTracks(std::vector<Music>& tracks, float& timePlayed, int& currentTrack) {
    if (timePlayed >= 1.0f) {
        if(currentTrack < tracks.size() - 1) {
            StopMusicStream(tracks[currentTrack]);
            ++currentTrack;
        }
        else {
            StopMusicStream(tracks[currentTrack]);
            currentTrack = 0;
        }

        PlayMusicStream(tracks[currentTrack]);
    }
}

void checkMove(Player& player, int columns) {
    if(IsKeyPressed(KEY_A) && player.getRec().x > player.getRec().width) {
        player.moveLeft();
    }
    else if (IsKeyPressed(KEY_D) && player.getRec().x < player.getRec().width * (columns - 2)) {
        player.moveRight();
    }
}

void controlRacer(Racer& racer, GameState& currentState, Player& player, int& score) {
    if(!racer.canSpawn()) return;
    racer.drawRacer();
    racer.decrementMoveCooldown();

    if(racer.isColliding(player.getRec()))
        currentState = GameState::end;

    if(racer.getMoveCooldown() > racer.getUpdateInterval()) {
        racer.move();
        racer.resetMoveCooldown();

        if (racer.getPosition() > 4) {
            ++score;
            racer.resetPosition();
            racer.resetMoveCooldown();

            if(racer.getUpdateInterval() > 15) {
                racer.decreaseUpdateInterval();
            }

            racer.resetSpawn();
        }
    }
}

void increaseRacerSpeed(Racer& racer, int minUpdate, int& timeToSpawn) {
    if(racer.getUpdateInterval() > minUpdate) {
        racer.decreaseUpdateInterval();
        timeToSpawn = racer.getUpdateInterval() * 2;
    }
}

void resetRacer(Racer& racer, int baseRacerUpdateInterval) {
    racer.resetPosition();
    racer.resetMoveCooldown();
    racer.resetSpawn();
    racer.resetUpdateInterval(baseRacerUpdateInterval);
}

void updateSaveHighscore(int& score, int& highscore, std::ofstream& osFile) {
    if(score > highscore) {
        highscore = score;
        osFile.open("save.txt");
        osFile << highscore;
        osFile.close();
    }
}
