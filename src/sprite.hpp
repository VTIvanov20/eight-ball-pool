#pragma once

#include "drawable.hpp"
#include <iostream>
#include <raylib.h>

class Sprite : public DrawableManager::Drawable
{
protected:
    Vector2 sprite_position;
    Texture2D sprite_texture;
    float sprite_scale_factor;
    float sprite_rotation;

public:
    Sprite(const char* texture_file_name, Vector2 initial_position, float scale = 1.0f, float rotation = 0.0f) : Drawable()
    {
        sprite_position = initial_position;
        sprite_texture = LoadTexture(texture_file_name);
        sprite_rotation = rotation;
        
        if (sprite_texture.id == 0)
        {
            std::cout << "ERROR: Failed loading texture (" << texture_file_name << "), halting process" << std::endl;
            exit(-1);
        }

        sprite_scale_factor = scale;
    }

    virtual ~Sprite()
    {
        UnloadTexture(sprite_texture);
    }

    void SetScale(float scale);
    void SetPosition(Vector2 position);
    void SetRotation(float rotation);
    Vector2 GetPosition();
    float GetWidth();
    float GetHeight();
    float GetRotation();

    void Draw() override;
};
