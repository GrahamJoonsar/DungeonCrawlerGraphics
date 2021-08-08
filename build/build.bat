@echo OFF
cls
echo Beginning Build
g++ -o game.exe main.cpp build/tigr.c -lopengl32 -lgdi32
START game
echo Build Complete