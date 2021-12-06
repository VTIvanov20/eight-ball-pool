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
        case Scene::MAIN_MENU:
            new MainMenu();
            break;
        case Scene::SETTINGS_MENU:
            new SettingsMenu();
            break;
        case Scene::IN_GAME:
            new GameScene();
            break;
        default:
            break;
        };

        DrawableManager::CreateAll();
    }

    void Initialize()
    {
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
        InitAudioDevice();
        InitPhysics();

        SetWindowIcon(LoadImage("resources/images/icon.png"));

        // don't quit on any key
        SetExitKey(0);

        if (!IsAudioDeviceReady())
        {
            std::cout << "INFO: Audio device wasn't initialized properly" << std::endl;
            state.audio_uninitialized = true;
        }
        else state.audio_uninitialized = false;

        state.scene_update = false;
        state.should_quit = false;
        state.scene = Scene::MAIN_MENU;

        state.master_volume = 100.f;

        SetPhysicsGravity(0.0f, 0.0f);
        SetTargetFPS(60);

        if (!state.audio_uninitialized)
            SetMasterVolume(state.master_volume);

        ReinitializeScene();
    }

    void ChangeScene(Scene scene)
    {
        state.scene = scene;
        state.scene_update = true;
    }

    void Quit()
    {
        std::cout << "triggered should_quit boolean" << std::endl;
        state.should_quit = true;
    }

    void Update()
    {
        if (state.scene_update)
        {
            ReinitializeScene();
            state.scene_update = false;
            std::cout << "INFO: GameManager: Scene Update!" << std::endl;
        }

        if (IsKeyPressed(KEY_F))
            ToggleFullscreen();
        
        if (IsKeyPressed(KEY_ESCAPE))
            ChangeScene(Scene::MAIN_MENU);
        
        BeginDrawing();
            ClearBackground(BLACK);

            DrawableManager::UpdateAll();
            DrawableManager::DrawAll();

            UpdatePhysics();
            //DrawColliders();

            // Draw FPS
            DrawText(std::to_string(GetFPS()).c_str(), 0, WINDOW_HEIGHT - 20, 20, GREEN);

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
        CloseAudioDevice();
        CloseWindow();

        std::cout << "INFO: Goodbye!" << std::endl;
    }

    bool ShouldQuit()
    {
        return state.should_quit || WindowShouldClose();
    }

    void ToggleAudio()
    {
        if (!state.audio_uninitialized)
        {
            if (state.master_volume > 0.0f)
            {
                state.master_volume = 0.0f;
                SetMasterVolume(state.master_volume);
            }
            else
            {
                state.master_volume = 1.0f;
                SetMasterVolume(state.master_volume);
            }
        }
    }

    bool IsAudioOn()
    {
        if (state.audio_uninitialized) return false;
        else
        {
            if (state.master_volume > 0.0f) return true;
            else return false;
        }
    }
}