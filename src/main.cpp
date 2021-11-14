#include "config.h"

#include <iostream>
#include <string>
#include <raylib.h>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 20, GREEN);
            DrawText("Hello, World!", 100, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
}