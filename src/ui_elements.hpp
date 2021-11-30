#pragma once

#include <raygui.h>
#include "drawable.hpp"

class UIElement : public DrawableManager::Drawable
{
protected:
    Rectangle bounds;
    float rotation;

public:
    UIElement(Rectangle bounds, float rotation) : Drawable()
    {
        this->bounds = bounds;
        this->rotation = rotation;
    }

    virtual ~UIElement() = default;

    void SetPosition(Vector2 position);
    Vector2 GetPosition();

    void SetRotation(float rotation);
    float GetRotation();

    void SetSize(Vector2 size);
    Vector2 GetSize();
};

class Button : public UIElement
{
protected:
    bool is_clicked;
    const char* text;

    Sound hover_sound;
    Sound click_sound;
    
public:
    Button(const char* text, Rectangle bounds, float rotation) : UIElement(bounds, rotation)
    {
        this->text = text;
        this->is_clicked = false;

        click_sound = LoadSound("resources/sfx/menu_hover.wav");
        hover_sound = LoadSound("resources/sfx/menu_click.wav");
    }

    virtual ~Button()
    {
        UnloadSound(hover_sound);
        UnloadSound(click_sound);
    }

    bool IsClicked();

    void Draw() override;
    void Update() override;
};

class Label : public UIElement
{
protected:
    const char* text;

public:
    Label(const char* text, Rectangle bounds, float rotation) : UIElement(bounds, rotation)
    {
        this->text = text;
    };

    virtual ~Label() = default;

    void Draw() override;
};

class CheckBox : public UIElement
{
private:
    bool checked;

protected:
    const char* placeholder_text;

public:
    CheckBox(const char* text, Rectangle bounds, float rotation, bool checked = false) : UIElement(bounds, rotation)
    {
        placeholder_text = text;
        this->checked = checked;
    }

    virtual ~CheckBox() = default;

    void Draw() override;
    bool IsChecked();
    void SetChecked(bool value);
};