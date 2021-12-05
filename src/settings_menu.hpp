#include <raylib.h>
#include <iostream>
#include <list>

#include "drawable.hpp"
#pragma once

#include "ui_elements.hpp"
#include "game_manager.hpp"

#include "config.h"

class SettingsMenu : DrawableManager::Drawable
{
private:
    std::list<UIElement*> elements;

public:
    SettingsMenu() = default;
    virtual ~SettingsMenu() = default;

    /**
     * @brief Initializes the Settings Menu
     */
    void Create() override;

    /**
     * @brief Checks for updates in the Settings Menu
     */
    void Update() override;
};