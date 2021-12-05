#pragma once

#include <iostream>
#include <raylib.h>

#include "config.h"

#include "drawable.hpp"
#include "sprite.hpp"
#include "table.hpp"
#include "main_menu.hpp"
#include "settings_menu.hpp"
#include "game_scene.hpp"

#include <physac.h>

namespace GameManager
{
    enum Scene
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
        Scene scene;
        Turn current_turn;
    };

    /**
     * @brief Initializes the program
     * 
     * @note Meant to be used in main.cpp
     */
    void Initialize();

    /**
     * @brief Deinitializes the program
     * 
     * @note Meant to be used in main.cpp
     */
    void Deinitialize();

    /**
     * @brief Steps or updates the program
     * 
     * @note Meant to be used in main.cpp
     */
    void Update();

    /**
     * @brief Similar to the WindowShouldClose() function in raylib.h
     * 
     * @note Meant to be used in main.cpp
     * 
     * @return bool
     */
    bool ShouldQuit();

    /**
     * @brief An API function, which triggers a boolean telling the program it should quit;
     * 
     * @attention Meant to be used at any point in the code (unlike functions like initialize and deinitialize)
     */
    void Quit();

    /**
     * @brief An API function, which changes the current scene
     * 
     * @param scene This describes the current scene
     * 
     * @note Meant to be used at any point in the code
     */
    void ChangeScene(Scene scene); 

    /**
     * @brief An API function, which turns audio on or off
     */
    void ToggleAudio();

    /**
     * @brief An API function which checks the game manager's last stored master volume and tells if the audio is on or not
     * 
     * @return bool
     */
    bool IsAudioOn();
}