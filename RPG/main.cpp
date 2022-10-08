#include <raylib.h>

#include "InputHandler.h"
#include "Player.h"
#include "Window.h"

int main()
{
    Window window{425, 625, "Dodger", 120};
    InputHandler handler{};

    Vector2 position{ static_cast<float>(window.getWidth()/2),static_cast<float>(window.getHeight()/1.22f)};
    Vector2 size{100,100};
    Player player{position, size, GREEN, 100.0f};

    while(!WindowShouldClose())
    {
        handler.handleInput(player);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        player.drawPlayer();

        DrawText("move the square with the arrow keys", 10, 10, 20, DARKGRAY);


        EndDrawing();
    }

    return 0;
}