//
// Created by Justice Bole on 10/8/22.
//

#ifndef MAIN_CPP_BOUNDARY_H
#define MAIN_CPP_BOUNDARY_H

#include "Player.h"

class Boundary
{
private:
    float m_leftBoundary{};
    float m_rightBoundary{};

public:
    Boundary(float left, float right) :
    m_leftBoundary{left}, m_rightBoundary{right}
    {

    }

    bool isInBound(Player& player) const
    {
        if((player.getPosition().x > m_rightBoundary) || (player.getPosition().x < m_leftBoundary))
        {
            return false;
        }
        return true;
    }

    bool wouldGoOutOfBounds(Player& player) const
    {
        if((player.getPosition().x > m_rightBoundary + player.getSpeed()) || (player.getPosition().x < m_leftBoundary - player.getSpeed()))
        {
            return false;
        }
        return true;
    }

    bool isInRightBound(Player& player) const
    {
        if(player.getPosition().x > m_rightBoundary)
        {
            return false;
        }
        return true;
    }

    bool isInLeftBound(Player& player) const
    {
        if(player.getPosition().x < m_leftBoundary)
        {
            return false;
        }
        return true;
    }

};

#endif //MAIN_CPP_BOUNDARY_H
