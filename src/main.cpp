#include <iostream>
#include "game_manager.hpp"

#define PHYSAC_IMPLEMENTATION
#define PHYSAC_AVOID_TIMMING_SYSTEM
#define PHYSAC_DEBUG

#include <physac.h>

#define RAYGUI_IMPLEMENTATION

#include <raygui.h>

int main()
{
    // Initializes the Window
    GameManager::Initialize();
    
    while (!GameManager::ShouldQuit())
    {
        // Updates the current scene while the game hasn't been quit yet
        GameManager::Update();
    }

    // After the game has been quit, deinitializes the Window
    GameManager::Deinitialize();
}