#pragma once

#include <iostream>
#include <raylib.h>

#include "config.h"

#include "drawable.hpp"
#include "sprite.hpp"
#include "table.hpp"
#include "main_menu.hpp"
#include "settings_menu.hpp"

#include <physac.h>

namespace GameManager
{
    enum GameScene
    {
        MAIN_MENU = 0,
        SETTINGS_MENU = 1,
        IN_GAME = 2,
    };

    enum Turn
    {
        SMALL_BALL = 0,
        BIG_BALL = 1,
    };

    struct GameState
    {
        bool scene_update;
        bool should_quit;
        bool audio_uninitialized;
        float master_volume;
        GameScene scene;
        Turn current_turn;
    };


    void Initialize(); // meant to be used in main.cpp to initialize the program
    void Deinitialize(); // meant to be used in main.cpp to deinitialize the program
    void Update(); // meant to be used in main.cpp to step or update the program
    bool ShouldQuit(); // meant to be used in main.cpp; similar to the WindowShouldClose function in raylib.h

    void Quit(); // api function which triggers a boolean telling the program it should quit; meant to be used at any point in the code (unlike functions like initialize and deinitialize)
    void ChangeScene(GameScene scene); // api function which changes the current scene; it is meant to be used at any point in the code

    void ToggleAudio(); // api function which turns audio on or off
    bool IsAudioOn(); // api function which checks the game manager's last stored master volume and tells if the audio is on or not
}