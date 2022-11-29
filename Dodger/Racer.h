//
// Created by Justice Bole on 11/29/22.
//

#ifndef DODGER_RACER_H
#define DODGER_RACER_H

#include "raylib.h"

enum class Racers {
    leftRacer,
    midRacer,
    rightRacer,
    maxRacers,
};

class Racer {
private:
    Rectangle m_rec{};
    Racers m_racersType{};
    float m_rowWidth{};
    float m_rowHeight{};

public:
    Racer();

};

#endif //DODGER_RACER_H
