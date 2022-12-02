//
// Created by Justice Bole on 12/1/22.
//
#include "Racer.h"

Racer::Racer(std::array<std::array<Rectangle , 5>, 3>& rec, RacerType&& racerT, int moveCD, int updateInter, int pos, bool canSpawn, Color& color) :
    m_rec{rec},
    m_rType{racerT},
    m_moveCooldown{moveCD},
    m_updateInterval{updateInter},
    m_position{pos},
    m_canSpawn{canSpawn},
    m_color{color} {
}

void Racer::drawRacer() const {
    DrawRectangleLinesEx(getRec(), getPosition() + 1, BLUE);
}

bool Racer::isColliding(Rectangle otherRec) const {
    return CheckCollisionRecs(getRec(), otherRec);
}

void Racer::move() { ++m_position; }
void Racer::resetPosition() { m_position = 0; }
void Racer::decrementMoveCooldown() { ++m_moveCooldown; }
void Racer::resetMoveCooldown() { m_moveCooldown = 0; }
void Racer::spawn() { m_canSpawn = true;}
void Racer::resetSpawn() { m_canSpawn = false; }
void Racer::resetUpdateInterval() { m_updateInterval = 60; }
void Racer::increaseUpdateInterval() { --m_updateInterval; }

bool Racer::canSpawn() const { return m_canSpawn; }
int Racer::getMoveCooldown() const { return m_moveCooldown; }
int Racer::getPosition() const { return m_position; }
int Racer::getType() const { return static_cast<int>(m_rType); }
int Racer::getUpdateInterval() const { return m_updateInterval; }
Rectangle Racer::getRec() const { return m_rec[getType()][getPosition()]; }
