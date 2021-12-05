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

    /**
     * @brief Sets the scale of the sprites
     * 
     * @param scale This describes the scale factor  
     */
    void SetScale(float scale);

    /**
     * @brief Sets the position of the sprites
     * 
     * @param position This describes the exact position of every sprite
     */
    void SetPosition(Vector2 position);

    /**
     * @brief Sets the rotation of the sprites
     * 
     * @param rotation This describes the exact rotation of the pool cue
     */
    void SetRotation(float rotation);

    /**
     * @brief Gets the position of the sprites
     * 
     * @return Vector2 This returns the exact position of the various sprites
     */
    Vector2 GetPosition();

    /**
     * @brief Gets the width of the sprites
     * 
     * @return float This returns the width of all the sprites
     */
    float GetWidth();
    
    /**
     * @brief Gets the height of the sprites
     * 
     * @return float This returns the height of all the sprites
     */
    float GetHeight();

    /**
     * @brief Gets the exact rotation of the sprites
     * 
     * @return float This returns the exact rotation of the sprites
     */
    float GetRotation();

    /**
     * @brief Draws the sprites
     */
    void Draw() override;
};
