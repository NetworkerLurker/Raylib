//
// Created by Justice Bole on 10/8/22.
//

#ifndef RPG_COMMAND_H
#define RPG_COMMAND_H

#include "Player.h"


class Command
{
public:
    virtual ~Command() = default;
    virtual void execute(Player&) = 0;
};

class UpCommand : public Command
{
public:
    void execute(Player& player) override { player.moveUp(); }
};

class DownCommand : public Command
{
public:
    void execute(Player& player) override { player.moveDown(); }
};

class LeftCommand : public Command
{
public:
    void execute(Player& player) override { player.moveLeft(); }
};

class RightCommand : public Command
{
public:
    void execute(Player& player) override { player.moveRight(); }
};


#endif //RPG_COMMAND_H
