//
// Created by Justice Bole on 10/8/22.
//

#include "InputHandler.h"

InputHandler::InputHandler()
{
    setDownCommand(new DownCommand);
    setUpCommand(new UpCommand);
    setLeftCommand(new LeftCommand);
    setRightCommand(new RightCommand);
}

InputHandler::~InputHandler()
{
    delete m_keyRight;
    delete m_keyLeft;
    delete m_keyDown;
    delete m_keyUp;
}

void InputHandler::handleInput(Player& player)
{
    if (IsKeyPressed(KEY_RIGHT)) m_keyRight->execute(player);
    else if (IsKeyPressed(KEY_LEFT)) m_keyLeft->execute(player);
//    else if (IsKeyPressed(KEY_UP)) m_keyUp->execute(player);
//    else if (IsKeyPressed(KEY_DOWN)) m_keyDown->execute(player);
}

void InputHandler::setUpCommand(Command* c)
{
    m_keyUp = c;
}
void InputHandler::setDownCommand(Command* c)
{
    m_keyDown = c;
}
void InputHandler::setLeftCommand(Command* c)
{
    m_keyLeft = c;
}
void InputHandler::setRightCommand(Command* c)
{
    m_keyRight = c;
}
