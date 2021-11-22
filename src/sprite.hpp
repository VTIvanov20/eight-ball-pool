#pragma once

#include "drawable.hpp"
#include <iostream>
#include <raylib.h>

class Sprite : public DrawableManager::Drawable
{
protected:
    Vector2* sprite_position;
    Texture2D sprite_texture;
    float scale_factor;

public:
    Sprite(const char* texture_file_name, Vector2 initial_position, float scale = 1) : Drawable()
    {
        sprite_position = new Vector2;
        sprite_position->x = initial_position.x;
        sprite_position->y = initial_position.y;
        sprite_texture = LoadTexture(texture_file_name);
        
        if (sprite_texture.id == 0)
        {
            std::cout << "ERROR: Failed loading texture (" << texture_file_name << "), halting process" << std::endl;
            exit(-1);
        }

        scale_factor = scale;
    }

    virtual ~Sprite()
    {
        UnloadTexture(sprite_texture);
        delete sprite_position;
    }

    void SetScale(float scale);
    void SetPosition(Vector2 position);
    Vector2 GetPosition();
    float GetWidth();
    float GetHeight();

    void Draw() override;
};