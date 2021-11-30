#include "ui_elements.hpp"

void UIElement::SetPosition(Vector2 position)
{
    bounds.x = position.x;
    bounds.y = position.y;
}

Vector2 UIElement::GetPosition()
{
    return { bounds.x, bounds.y };
}

void UIElement::SetRotation(float rotation)
{
    this->rotation = rotation;
}

float UIElement::GetRotation()
{
    return rotation; 
}

void UIElement::SetSize(Vector2 size)
{
    bounds.width = size.x;
    bounds.height = size.y;
}

Vector2 UIElement::GetSize()
{
    return { bounds.width, bounds.height };
}

void Button::Draw()
{
    is_clicked = GuiButton(bounds, text);
}

void Button::Update()
{
    if (is_clicked)
        PlaySound(click_sound);
}

bool Button::IsClicked()
{
    return is_clicked;
}

void Label::Draw()
{
    GuiLabel(bounds, text);
}

void CheckBox::Draw()
{
    checked = GuiCheckBox(bounds, placeholder_text, checked);
}

bool CheckBox::IsChecked()
{
    return checked;
}

void CheckBox::SetChecked(bool value)
{
    checked = value;
}