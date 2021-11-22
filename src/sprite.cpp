#include "sprite.hpp"

void Sprite::SetScale(float scale)
{
    scale_factor = scale;
}

void Sprite::SetPosition(Vector2 position)
{
    sprite_position->x = position.x;
    sprite_position->y = position.y;
}

Vector2 Sprite::GetPosition()
{
    return { sprite_position->x, sprite_position->y };
}

float Sprite::GetWidth()
{
    return sprite_texture.width * scale_factor;
}

float Sprite::GetHeight()
{
    return sprite_texture.height * scale_factor;
}

void Sprite::Draw()
{
    DrawTextureEx(
        sprite_texture,
        { sprite_position->x, sprite_position->y },
        0.0f,
        scale_factor,
        WHITE
    );
}