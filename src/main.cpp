#include "config.h"

#include <iostream>
#include <string>
#include <raylib.h>
#include <physac.h>
#include <vector>

#include "drawable.h"

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitPhysics();

    SetTargetFPS(60);
    
    new Player("resources/images/stick.png", {0, 0, 0, 0});
    new Sprite("resources/images/stick.png", {100, 100, 0, 0});
    new Sprite("resources/images/stick.png", {200, 200, 0, 0});
    new Sprite("resources/images/stick.png", {300, 300, 0, 0});
    new Sprite("resources/images/stick.png", {400, 400, 0, 0});

    DrawableManager::DestroyDrawableFromID(2);
    DrawableManager::CreateAll();
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);

            DrawableManager::UpdateAll();
            DrawableManager::DrawAll();

            UpdatePhysics();

            // Draw FPS
            DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 20, GREEN);
        EndDrawing();
    }

    DrawableManager::DestroyAllDrawables();

    ClosePhysics();
    CloseWindow();
}