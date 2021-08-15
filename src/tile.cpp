#include "tile.h"
#include "../build/tigr.h"

void Tile::draw(Tigr * s){
    tigrFill(s, x, y, tileSideLength, tileSideLength, color);
}