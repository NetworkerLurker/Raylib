#include <raylib.h>

#include "Command.h"
#include "InputHandler.h"
#include "Player.h"
#include "Window.h"

int main()
{
    Window window{};
    InputHandler handler{};

    Vector2 position{ static_cast<float>(window.getWidth()/2),static_cast<float>(window.getHeight()/2)};
    Vector2 size{10,10};
    Player player{position, size, RED};

    while(!WindowShouldClose())
    {
        handler.handleInput(player);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("move the square with the arrow keys", 10, 10, 20, DARKGRAY);

        player.drawPlayer();
        EndDrawing();
    }

    return 0;
}