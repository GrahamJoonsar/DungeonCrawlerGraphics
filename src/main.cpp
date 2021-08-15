#include "../build/tigr.h"
#include "tile.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <Windows.h> // Hiding the console

bool gameOver = false;

int main(void){
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    srand(time(0));

    // Creating the screen instance
    Tigr *screen = tigrWindow(swidth, sheight, "GAMING", 0);

    Tile board[sheight/tileSideLength][swidth/tileSideLength];

    int k = 0;

    for (int i = 0; i < (sheight/tileSideLength); i++){
        for (int j = 0; j < (swidth/tileSideLength); j++){
            // Setting position
            board[i][j].x = j * tileSideLength;
            board[i][j].y = i * tileSideLength;
            // Setting color
            board[i][j].color = k % 2 == 0 ? tigrRGB(50,205,50) : tigrRGB(0,255,0);
            if (k % 2 == 1){
                board[i][j].lighter = true;
            }
            k++;

            if (rand() % 12 == 0){
                board[i][j].isBomb = true;
                board[i][j].color = tigrRGB(0, 0, 0);
            }
        }
        k++;
    }

    for (int i = 0; i < (sheight/tileSideLength); i++){
        for (int j = 0; j < (swidth/tileSideLength); j++){
            int bombNum = 0;
            if (i > 0){ // Top row
                if (board[i-1][j].isBomb){
                    bombNum++;
                }
                if (j > 0 && board[i-1][j-1].isBomb){
                    bombNum++;
                }
                if (j < (swidth/tileSideLength) - 1 && board[i-1][j+1].isBomb){
                    bombNum++;
                }
            }
            if (i < (sheight/tileSideLength) - 1){ // Bottom row
                if (board[i+1][j].isBomb){
                    bombNum++;
                }
                if (j > 0 && board[i+1][j-1].isBomb){
                    bombNum++;
                }
                if (j < (swidth/tileSideLength) - 1 && board[i+1][j+1].isBomb){
                    bombNum++;
                }
            }
            if (j > 0 && board[i][j-1].isBomb){
                bombNum++;
            }
            if (j < (swidth/tileSideLength) - 1 && board[i][j+1].isBomb){
                bombNum++;
            }
            board[i][j].adjacentBombs = bombNum;
        }
    }

    int mousex, mousey, buttonPressed;

    while (!tigrClosed(screen)){ // Main loop
        tigrClear(screen, tigrRGB(255, 255, 255)); // ClearScrn
        
        // Drawing the board
        for (int i = 0; i < sheight/tileSideLength; i++){
            for (int j = 0; j < swidth/tileSideLength; j++){
                board[i][j].draw(screen);
                if (board[i][j].uncovered && board[i][j].adjacentBombs > 0){ // Player clicked on
                    tigrPrint(screen, tfont, j * tileSideLength + tileSideLength/4, i * tileSideLength + tileSideLength/4, tigrRGB(255, 0, 0), "%d", (board[i][j].adjacentBombs));
                }
            }
        }

        tigrMouse(screen, &mousex, &mousey, &buttonPressed);

        mousex -= mousex % tileSideLength; // Changed to the top left of the nearest box
        mousey -= mousey % tileSideLength;

        // Alpha doesn't work for some reason, so this jank
        tigrFill(screen, mousex, mousey, tileSideLength, tileSideLength, tigrRGB(
            (tigrGet(screen, mousex, mousey).r + 255)/2,
            (tigrGet(screen, mousex, mousey).g + 255)/2,
            (tigrGet(screen, mousex, mousey).b + 255)/2
        ));

        if (board[mousey/tileSideLength][mousex/tileSideLength].adjacentBombs > 0 && board[mousey/tileSideLength][mousex/tileSideLength].uncovered)
            tigrPrint(screen, tfont, mousex + tileSideLength/4, mousey + tileSideLength/4, tigrRGB(255, 0, 0), "%d", (board[mousey/tileSideLength][mousex/tileSideLength].adjacentBombs));

        if (!gameOver){
            if (buttonPressed == 1 && mousey/tileSideLength < sheight/tileSideLength && mousex/tileSideLength < swidth/tileSideLength){ // Left mouse
                if (board[mousey / tileSideLength][mousex / tileSideLength].isBomb){
                    gameOver = true;
                } else {
                    if (board[mousey / tileSideLength][mousex / tileSideLength].lighter){
                        board[mousey / tileSideLength][mousex / tileSideLength].color = tigrRGB(222, 206, 185);
                    } else {
                        board[mousey / tileSideLength][mousex / tileSideLength].color = tigrRGB(211, 180, 140);
                    }
                    board[mousey / tileSideLength][mousex / tileSideLength].uncovered = true;
                }
            }
        }

        if (gameOver){
            tigrPrint(screen, tfont, swidth/2 - 30, sheight/3, tigrRGB(255, 0, 0), "GAME OVER");
        }

        tigrUpdate(screen); // Update the screen
    }
    tigrFree(screen);
    return 0;
}