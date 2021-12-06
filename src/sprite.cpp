#include "sprite.hpp"

void Sprite::SetScale(float scale)
{
    // Sets the scale of size for a sprite
    sprite_scale_factor = scale;
}

void Sprite::SetPosition(Vector2 position)
{
    // Sets the position of a sprite
    sprite_position.x = position.x;
    sprite_position.y = position.y;
}

void Sprite::SetRotation(float rotation)
{
    // Sets the rotation of a sprite
    sprite_rotation = rotation;
}

Vector2 Sprite::GetPosition()
{
    // Returns the position of a sprite
    return { sprite_position.x, sprite_position.y };
}

float Sprite::GetWidth()
{
    // Returns the width of a sprite
    return sprite_texture.width * sprite_scale_factor;
}

float Sprite::GetHeight()
{
    // Returns the height of a sprite
    return sprite_texture.height * sprite_scale_factor;
}

float Sprite::GetRotation()
{
    // Returns the rotation of a sprite
    return sprite_rotation;
}

void Sprite::Draw()
{
    // Draws a sprite
    DrawTextureEx(
        sprite_texture,
        { sprite_position.x, sprite_position.y },
        sprite_rotation,
        sprite_scale_factor,
        WHITE
    );
}