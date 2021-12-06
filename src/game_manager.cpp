#include "game_manager.hpp"

namespace GameManager
{
    GameState state;
    
    void DrawColliders()
    {
        for (int i = 0; i < GetPhysicsBodiesCount(); i++)
        {
            // Gets a physicbody for every physicbody loaded
            PhysicsBody body = GetPhysicsBody(i);

            if (body != NULL)
            {
                // If the physicbody isn't drawn
                int vertexCount = GetPhysicsShapeVerticesCount(i);

                for (int j = 0; j < vertexCount; j++)
                {
                    // It gets the physics bodies shape vertices to draw lines
                    // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                    Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                    // Get next vertex or first to close the shape
                    int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);
                    Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                    DrawLineV(vertexA, vertexB, GREEN);
                    // Draw a line between two vertex positions
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

        // Gets the wanted scene and initializes it
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

        // Creates all the drawables in the newly initialized scene
        DrawableManager::CreateAll();
    }

    void Initialize()
    {
        // Initializes the windows, audio, physics and icon
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
        InitAudioDevice();
        InitPhysics();

        SetWindowIcon(LoadImage("resources/images/icon.png"));

        // Sets the exit key to 0 so the windows closes when the quit button is pressed
        SetExitKey(0);

        // Checks if the audio devices work properly
        if (!IsAudioDeviceReady())
        {
            std::cout << "INFO: Audio device wasn't initialized properly" << std::endl;
            state.audio_uninitialized = true;
        }
        else state.audio_uninitialized = false;

        // Sets the main menu scene
        state.scene_update = false;
        state.should_quit = false;
        state.scene = Scene::MAIN_MENU;

        state.master_volume = 100.f;

        // Disables the gravity and sets the targetfps to 60
        SetPhysicsGravity(0.0f, 0.0f);
        SetTargetFPS(60);

        // If the audio isn't unitialized, initialize it again
        if (!state.audio_uninitialized)
            SetMasterVolume(state.master_volume);

        // Reinitialize scene
        ReinitializeScene();
    }

    void ChangeScene(Scene scene)
    {
        // Changes scene to wanted scene and sets the bool to true
        state.scene = scene;
        state.scene_update = true;
    }

    void Quit()
    {
        // Sets the bool to true
        std::cout << "triggered should_quit boolean" << std::endl;
        state.should_quit = true;
    }

    void Update()
    {
        // If a scene has recently been changes initialize it
        if (state.scene_update)
        {
            ReinitializeScene();
            state.scene_update = false;
            std::cout << "INFO: GameManager: Scene Update!" << std::endl;
        }

        // If the F key is pressed - toggle Fullscreen
        if (IsKeyPressed(KEY_F))
            ToggleFullscreen();
        
        // If the Escape key is pressed - go to the Main Menu
        if (IsKeyPressed(KEY_ESCAPE))
            ChangeScene(Scene::MAIN_MENU);
        
        BeginDrawing();
            ClearBackground(BLACK);

            // Draws and updates all drawables
            DrawableManager::UpdateAll();
            DrawableManager::DrawAll();

            // Updates the physics
            UpdatePhysics();
            //DrawColliders();

            // Draws FPS
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

        // Close physics, audio and the windows when the scene is deinitialized
        ClosePhysics();
        CloseAudioDevice();
        CloseWindow();

        std::cout << "INFO: Goodbye!" << std::endl;
    }

    bool ShouldQuit()
    {
        // Returns if the window should quit
        return state.should_quit || WindowShouldClose();
    }

    void ToggleAudio()
    {
        // If the audio isn't initialized - initialize it
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
        // Returns if the audio is initialized
        if (state.audio_uninitialized) return false;
        else
        {
            if (state.master_volume > 0.0f) return true;
            else return false;
        }
    }
}