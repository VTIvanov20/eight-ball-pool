#include "ui_elements.hpp"

void UIElement::SetPosition(Vector2 position)
{
    // Sets the position of an User-Interface element
    bounds.x = position.x;
    bounds.y = position.y;
}

Vector2 UIElement::GetPosition()
{
    // Returns the position of an User-Interface element
    return { bounds.x, bounds.y };
}

void UIElement::SetRotation(float rotation)
{
    // Sets the rotation of an User-Interface element
    this->rotation = rotation;
}

float UIElement::GetRotation()
{
    // Returs the rotation of an User-Interface element
    return rotation; 
}

void UIElement::SetSize(Vector2 size)
{
    // Sets the size of an User-Interface element
    bounds.width = size.x;
    bounds.height = size.y;
}

Vector2 UIElement::GetSize()
{
    // Returns the size of an User-Interface element
    return { bounds.width, bounds.height };
}

void Button::Draw()
{
    // Draws a button
    is_clicked = GuiButton(bounds, text);
}

void Button::Update()
{
    // Checks if a button is clicked and if it - plays sound
    if (is_clicked)
        PlaySound(click_sound);
}

bool Button::IsClicked()
{
    // Returns whether or not a button is clicked
    return is_clicked;
}

void Label::Draw()
{
    // Draws a label
    GuiLabel(bounds, text);
}

void CheckBox::Draw()
{
    // Draws a checkbox
    checked = GuiCheckBox(bounds, placeholder_text, checked);
}

bool CheckBox::IsChecked()
{
    // Returns whether or not a checkbox is checked
    return checked;
}

void CheckBox::SetChecked(bool value)
{
    // Sets the boolean variable whether or not a checkbox is clicked
    checked = value;
}