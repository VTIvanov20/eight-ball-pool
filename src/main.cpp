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
    
    std::vector<Drawable*> drawables;
    drawables.push_back(new Player("resources/images/square.png", {0, 0, 0, 0}));
    drawables.push_back(new Sprite("resources/images/square.png", {100, 100, 0, 0}));
    drawables.push_back(new Sprite("resources/images/square.png", {200, 200, 0, 0}));
    drawables.push_back(new Sprite("resources/images/square.png", {300, 300, 0, 0}));
    drawables.push_back(new Sprite("resources/images/square.png", {400, 400, 0, 0}));

    for (auto& drawable : drawables)
    {
        drawable->Create();
    }
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);

            for (auto& drawable : drawables)
            {
                drawable->Update();
                drawable->Draw();
            }

            UpdatePhysics();

            DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 20, GREEN);
            DrawText("Ya like Jazz?", 1000, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    for (auto& drawable : drawables)
    {
        delete drawable;
    }

    ClosePhysics();
    CloseWindow();
}