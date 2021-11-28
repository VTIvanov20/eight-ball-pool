#include "game_manager.hpp"

namespace GameManager
{
    GameState state;
    
    void DrawColliders()
    {
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
    }

    void ReinitializeScene()
    {
        // Destroy any leftover drawables to prevent memory leaking
        DrawableManager::DestroyAllDrawables();
        
        // Destroy any leftover physics bodies to prevent memory leaking
        while (GetPhysicsBodiesCount() != 0)
        {
            for (int i = 0; i < GetPhysicsBodiesCount(); i++)
                DestroyPhysicsBody(GetPhysicsBody(i));
        }

        switch(state.scene)
        {
        case GameScene::MAIN_MENU:
            new MainMenu();
            break;
        case GameScene::SETTINGS_MENU:
            new Sprite("resources/images/stick.png", {0, 0});
            break;
        case GameScene::IN_GAME:
            new Table();
            break;
        default:
            break;
        };

        DrawableManager::CreateAll();
    }

    void Initialize()
    {
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

        // don't quit on any key
        SetExitKey(0);

        InitPhysics();

        state.sceneUpdate = false;
        state.shouldQuit = false;
        state.scene = GameScene::MAIN_MENU;

        SetPhysicsGravity(0.0f, 0.0f);
        SetTargetFPS(60);

        ReinitializeScene();
    }

    void ChangeScene(GameScene scene)
    {
        state.scene = scene;
        state.sceneUpdate = true;
    }

    void Quit()
    {
        std::cout << "triggered shouldQuit boolean" << std::endl;
        state.shouldQuit = true;
    }

    void Update()
    {
        if (state.sceneUpdate)
        {
            ReinitializeScene();
            state.sceneUpdate = false;
            std::cout << "INFO: GameManager: Scene Update!" << std::endl;
        }

        if (IsKeyPressed(KEY_F))
            ToggleFullscreen();
        
        if (IsKeyPressed(KEY_ESCAPE))
            ChangeScene(GameScene::MAIN_MENU);
        
        BeginDrawing();
            ClearBackground(BLACK);

            DrawableManager::UpdateAll();
            DrawableManager::DrawAll();

            UpdatePhysics();
            DrawColliders();

            // Draw FPS
            DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 20, GREEN);

            // Draw Mouse Position
            DrawText(TextFormat("%.0f, %.0f", GetMousePosition().x, GetMousePosition().y), 0, WINDOW_HEIGHT - 20, 20, GREEN);
            
        EndDrawing();
    }
    
    void Deinitialize()
    {
        // Destroy any leftover drawables to prevent memory leaking
        DrawableManager::DestroyAllDrawables();
        
        // Destroy any leftover physics bodies to prevent memory leaking
        while (GetPhysicsBodiesCount() != 0)
        {
            for (int i = 0; i < GetPhysicsBodiesCount(); i++)
                DestroyPhysicsBody(GetPhysicsBody(i));
        }

        ClosePhysics();
        CloseWindow();

        std::cout << "INFO: Goodbye!" << std::endl;
    }

    bool ShouldQuit()
    {
        return state.shouldQuit || WindowShouldClose();
    }
}