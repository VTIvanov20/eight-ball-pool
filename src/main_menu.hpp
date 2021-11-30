#pragma once

#include "drawable.hpp"
#include "ui_elements.hpp"
#include "game_manager.hpp"

#include "config.h"

#include <raygui.h>
#include <raylib.h>
#include <iostream>
#include <list>

class MainMenu : public DrawableManager::Drawable
{
private:
    std::list<Button*> buttons;

public:
    MainMenu() = default;
    virtual ~MainMenu() = default;

    void Create() override;
    void Update() override;
};