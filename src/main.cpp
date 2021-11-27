#include "config.h"


#include <iostream>
#include <string>
#include <raylib.h>
#include <vector>

#include "sprite.hpp"
#include "table.hpp"

#define PHYSAC_IMPLEMENTATION
#define PHYSAC_AVOID_TIMMING_SYSTEM
#define PHYSAC_DEBUG

#include <physac.h>

enum GameScene
{
    MAIN_MENU = 0,
    SETTINGS_MENU = 1,
    IN_GAME_SCENE = 2,
};

enum Turn
{
    SMALL_BALL = 0,
    BIG_BALL = 1,
};

struct GameState
{
    GameScene scene;
    Turn currentTurn;
};

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitPhysics();

    SetPhysicsGravity(0.0f, 0.0f);

    SetTargetFPS(60);

    new Table();

    DrawableManager::CreateAll();
    
    while(!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F))
            ToggleFullscreen();
        
        BeginDrawing();
            ClearBackground(BLACK);

            DrawableManager::UpdateAll();
            DrawableManager::DrawAll();

            // draw colliders
            for (int i = 0; i < GetPhysicsBodiesCount(); i++)
            {
                PhysicsBody body = GetPhysicsBody(i);

                if (body != NULL)
                {
                    int vertexCount = GetPhysicsShapeVerticesCount(i);
                    for (int j = 0; j < vertexCount; j++)
                    {
                        // Get physics bodies shape vertices to draw lines
                        // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                        Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                        int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                        Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                        DrawLineV(vertexA, vertexB, GREEN);     // Draw a line between two vertex positions
                    }
                }
            }

            UpdatePhysics();

            // Draw FPS
            DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 20, GREEN);

            // Draw Mouse Position
            DrawText(TextFormat("%.0f, %.0f", GetMousePosition().x, GetMousePosition().y), 0, WINDOW_HEIGHT - 20, 20, GREEN);
            
        EndDrawing();
    }

    DrawableManager::DestroyAllDrawables();

    ClosePhysics();
    CloseWindow();

    std::cout << "INFO: Goodbye!" << std::endl;
}