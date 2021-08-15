#pragma once

#include "../build/tigr.h"
#include "main.h"

class Tile{
    public:
        TPixel color = tigrRGB(255, 0, 0);
        int x, y, adjacentBombs = 0; // Position
        bool isBomb = false;
        bool lighter = false;
        bool uncovered = false;
        Tile (int _x, int _y, TPixel _c) : x(_x), y(_y), color(_c){} // Constructor
        Tile (){} // Constructor

        // Drawing the player to to the screen
        void draw(Tigr * s);
};
