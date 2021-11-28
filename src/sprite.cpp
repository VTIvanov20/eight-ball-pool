#include "sprite.hpp"

void Sprite::SetScale(float scale)
{
    sprite_scale_factor = scale;
}

void Sprite::SetPosition(Vector2 position)
{
    sprite_position.x = position.x;
    sprite_position.y = position.y;
}

void Sprite::SetRotation(float rotation)
{
    sprite_rotation = rotation;
}

Vector2 Sprite::GetPosition()
{
    return { sprite_position.x, sprite_position.y };
}

float Sprite::GetWidth()
{
    return sprite_texture.width * sprite_scale_factor;
}

float Sprite::GetHeight()
{
    return sprite_texture.height * sprite_scale_factor;
}

float Sprite::GetRotation()
{
    return sprite_rotation;
}

void Sprite::Draw()
{
    DrawTextureEx(
        sprite_texture,
        { sprite_position.x, sprite_position.y },
        sprite_rotation,
        sprite_scale_factor,
        WHITE
    );
}