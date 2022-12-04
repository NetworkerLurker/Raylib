//
// Created by Justice Bole on 12/3/22.
//
#include "Drawing.h"

void drawBuildings(Window& window, Color& color) {
    for(int i{0}; i < 10; ++i) {
        int yPosition{i * 30};
        DrawRectangleLines(10 * i * i, yPosition, 50 - i, window.getHalfHeight() - yPosition, color );
        DrawRectangleLines(window.getWidth() - (100 * i), yPosition, 50 + i, window.getHalfHeight() - yPosition, color );
    }
}

void drawGameOverScreen(Window& window, int highscore, int score, int fontsize, Color& color) {
    DrawText("Press R To Retry", window.getWidth() * .34f, window.getHeight() * .30f, fontsize, color);
    DrawText("Press ESC To Quit", window.getWidth() * .34f, window.getHeight() * .40f, fontsize, color);
    DrawText(TextFormat("Highscore: %i", highscore),window.getWidth() * .38f,window.getHeight() * .10f,fontsize,color);
    DrawText(TextFormat("Your Score: %i", score),window.getWidth() * .38f,window.getHeight() * .20f,fontsize,color);
}

void drawLogoScreen(Window& window, int frameCounter, int fontSize, Color& color) {
    DrawText("Justice", window.getHalfHeight(), window.getHalfHeight(), fontSize, color);
    DrawLine(3 * frameCounter, 0, 3 * frameCounter, window.getHeight(), color);
    DrawLine(0, 2 * frameCounter, window.getWidth(), 2 * frameCounter, color);
}

void drawRoad(Window& window, Color& color) {
    DrawLine(0, window.getHalfHeight(), window.getWidth(), window.getHalfHeight(), color); //Horizon line
    DrawLine(window.getHalfWidth(), window.getHalfHeight(), 0, window.getHeight(), color); //Left edge
    DrawLine(window.getHalfWidth(), window.getHalfHeight(), window.getWidth(), window.getHeight(), color); //Right edge
}

void drawRoadMarkers(Window& window , Color& color) {
    DrawLine(window.getHalfWidth(), window.getHalfHeight(), window.getWidth() * .30f, window.getHeight(), color); //Left marker
    DrawLine(window.getHalfWidth(), window.getHalfHeight(), window.getWidth() * .70f, window.getHeight(), color); //Right marker
}

void drawStats(Window& window, int score, int fontSize, int playerSpeed, int playerDistanceTraveled, Color& color) {
    DrawText(TextFormat("Dodges: %i",score),window.getWidth() * .70f,window.getHeight() * .05f,fontSize,color);
    DrawText(TextFormat("Speed: %imph",180 - (playerSpeed * 2)), window.getWidth() * .70f,window.getHeight() * .10f,fontSize,color);
    DrawText(TextFormat("Distance: %i'",playerDistanceTraveled),window.getWidth() * .70f,window.getHeight() * .15f,fontSize,color);
}



