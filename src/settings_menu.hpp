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

    void Create() override;
    void Update() override;
};