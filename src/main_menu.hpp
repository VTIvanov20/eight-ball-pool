#pragma once

#include "drawable.hpp"
#include "game_manager.hpp"

#include "config.h"

#include <raygui.h>
#include <raylib.h>
#include <iostream>
#include <list>

class Button : DrawableManager::Drawable
{
private:
    Rectangle bounds;
    bool is_clicked;
    const char* text;
    
public:
    Button(const char* text, Rectangle bounds) : Drawable()
    {
        this->bounds = bounds;
        this->text = text;
        this->is_clicked = false;
    }

    virtual ~Button() = default;

    bool IsClicked();

    void Draw() override;
};

class MainMenu : DrawableManager::Drawable
{
private:
    std::list<Button*> buttons;

public:
    MainMenu() = default;
    ~MainMenu() = default;

    void Create() override;
    void Update() override;
};