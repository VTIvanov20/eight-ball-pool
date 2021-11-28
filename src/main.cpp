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
    GameManager::Initialize();
    
    while (!GameManager::ShouldQuit())
    {
        GameManager::Update();
    }

    GameManager::Deinitialize();
}