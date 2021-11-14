#include "drawable.h"
#include <raylib.h>
#include <iostream>

void Sprite::Create()
{
    
}

void Sprite::Update()
{

}

void Sprite::Draw()
{
    DrawTexture(texture, position->x, position->y, WHITE);
}

void Player::Update()
{
    if (IsKeyDown(KEY_W))
        position->y -= GetFrameTime() * 200;
    if (IsKeyDown(KEY_S))
        position->y += GetFrameTime() * 200;
    if (IsKeyDown(KEY_A))
        position->x -= GetFrameTime() * 200;
    if (IsKeyDown(KEY_D))
        position->x += GetFrameTime() * 200;
}