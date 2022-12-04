//
// Created by Justice Bole on 12/3/22.
//

#ifndef DODGER_DRAWING_H
#define DODGER_DRAWING_H

#include "Window.h"

void drawBuildings(Window& window, Color& color);
void drawGameOverScreen(Window& window, int highscore, int score, int fontsize, Color& color);
void drawLogoScreen(Window& window, int frameCounter, int fontSize, Color& color);
void drawRoad(Window& window, Color& color);
void drawRoadMarkers(Window& window , Color& color);
void drawStats(Window& window, int score, int fontSize, int playerSpeed, int playerDistanceTraveled, Color& color);


#endif //DODGER_DRAWING_H
