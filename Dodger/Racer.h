//
// Created by Justice Bole on 11/29/22.
//

#ifndef DODGER_RACER_H
#define DODGER_RACER_H

#include <array>
#include "raylib.h"

enum class RacerType {
    leftRacer,
    midRacer,
    rightRacer,
    maxRacers,
};

class Racer {
private:
    std::array<std::array<Rectangle , 5>, 3> m_rec{};
    RacerType m_rType{};
    int m_moveCooldown{};
    int m_updateInterval{};
    int m_position{};
    bool m_canSpawn{};
    Color m_color{};


public:
    Racer(std::array<std::array<Rectangle , 5>, 3>& rec, RacerType&& racerT, int moveCD, int updateInter, int pos, bool canSpawn, Color& color);

    void drawRacer() const;
    bool isColliding(Rectangle otherRec) const;
    void move();
    void spawn();
    void addScore();
    void resetPosition();
    void decrementMoveCooldown();
    void resetMoveCooldown();
    void resetSpawn();
    void resetUpdateInterval();
    void increaseUpdateInterval();

    [[nodiscard]] bool canSpawn() const;
    [[nodiscard]] int getMoveCooldown() const;
    [[nodiscard]] int getType() const;
    [[nodiscard]] int getUpdateInterval() const;
    [[nodiscard]] int getPosition() const;
    [[nodiscard]] Rectangle getRec() const;

};

#endif //DODGER_RACER_H
