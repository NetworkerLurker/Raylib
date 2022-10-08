#include <raylib.h>

#include "Boundary.h"
#include "InputHandler.h"
#include "Player.h"
#include "Window.h"

int main()
{
    Window window{425, 640, "Dodger", 120};
    InputHandler handler{};
    Boundary boundary{0, 400 };

    Vector2 position{ static_cast<float>(window.getWidth()/2.0f),static_cast<float>(window.getHeight()/1.2f)};
    Vector2 size{100,100};
    Player player{position, size, RED, 100.f};

    while(!WindowShouldClose())
    {
        if(boundary.isInBound(player))
        {
            handler.handleInput(player);
        }
        else if(!boundary.isInLeftBound(player))
        {
            player.moveRight();
        }
        else if(!boundary.isInRightBound(player))
        {
            player.moveLeft();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("move the square with the arrow keys", 10, 10, 20, DARKGRAY);

        player.drawPlayer();
        EndDrawing();
    }

    return 0;
}

//check if move is legal
//if it is make the move
//if it isnt 