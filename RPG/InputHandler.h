//
// Created by Justice Bole on 10/8/22.
//

#ifndef RPG_INPUTHANDLER_H
#define RPG_INPUTHANDLER_H
#include "raylib.h"

#include "Command.h"
#include "Player.h"

class InputHandler
{
private:
    Command* m_keyUp{};
    Command* m_keyDown{};
    Command* m_keyLeft{};
    Command* m_keyRight{};

public:
    InputHandler();
    ~InputHandler();

    void handleInput(Player& player);

    void setUpCommand(Command* c);
    void setDownCommand(Command* c);
    void setLeftCommand(Command* c);
    void setRightCommand(Command* c);
};

#endif //RPG_INPUTHANDLER_H
