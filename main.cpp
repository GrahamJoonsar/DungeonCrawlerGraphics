#include "build/tigr.h"
#include <math.h>

constexpr int tileSideLength = 20;
constexpr int swidth = 320;
constexpr int sheight = 240;

bool gameOver = false;

class Player {
    private:
        TPixel color = tigrRGB(255, 0, 0);
    public:
        int x, y, targx, targy; // Position
        Player (int _x, int _y) : x(_x), y(_y), targx(_x), targy(_y){} // Constructor

        // Drawing the player to to the screen
        void draw(Tigr * s){
            tigrFill(s, x, y, tileSideLength, tileSideLength, color);
        }

        // Moving the player legally
        void move(Tigr * screen){
            // Vertical
            if (tigrKeyDown(screen, 'W')){
                targy -= tileSideLength;
            } else if (tigrKeyDown(screen, 'S')){
                targy += tileSideLength;
            }
            // Horizontal
            if (tigrKeyDown(screen, 'A')){
                targx -= tileSideLength;
            } else if (tigrKeyDown(screen, 'D')){
                targx += tileSideLength;
            }

            // So the player doesn't move instantly
            if (targx < x){
                x--;
            } else if (targx > x){
                x++;
            }

            if (targy < y){
                y--;
            } else if (targy > y){
                y++;
            }
        }
};

int main(void){
    // Creating the screen instance
    Tigr *screen = tigrWindow(swidth, sheight, "GAMING", 0);

    Player player(160, 120);

    int k = 0;

    while (!tigrClosed(screen)){ // Main loop
        tigrClear(screen, tigrRGB(255, 255, 255)); // ClearScrn
        for (int i = 0; i < sheight; i += tileSideLength){
            for (int j = 0; j < swidth; j += tileSideLength){
                tigrFill(screen, j, i, tileSideLength, tileSideLength, k%2 == 0 ? tigrRGB(255, 255, 255) : tigrRGB(0, 0, 0));
                k++;
            }
            k++;
        }
        player.draw(screen);
        player.move(screen);
        tigrUpdate(screen); // Update the screen
    }
    tigrFree(screen);
    return 0;
}