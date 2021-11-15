#include "drawable.h"
#include <raylib.h>
#include <iostream>
#include <vector>

namespace DrawableManager
{
    std::vector<Drawable*> drawablePool;
    int currentId = 0;

    Drawable::Drawable()
    {
        id = currentId;
        ++currentId;

        std::cout << "INFO: DrawableManager: Created Drawable with ID: " << id << std::endl;

        drawablePool.push_back(this);
    }

    void CreateAll()
    {
        for (auto& drawable : drawablePool)
        {
            drawable->Create();
        }
    }

    void UpdateAll()
    {
        for (auto& drawable : drawablePool)
        {
            drawable->Update();
        }
    }

    void DrawAll()
    {
        for (auto& drawable : drawablePool)
        {
            drawable->Draw();
        }
    }

    void DestroyAllDrawables()
    {
        for (auto& drawable : drawablePool)
        {
            delete drawable;
        }

        drawablePool.clear();
    }

    void DestroyDrawableFromID(int id)
    {
        for (auto drawable = drawablePool.begin(); drawable != drawablePool.end(); ++drawable)
        {
            Drawable* drawablePtr = *drawable;

            if (drawablePtr->GetID() == id)
            {
                delete drawablePtr;
                drawablePool.erase(drawable);

                std::cout << "INFO: DrawableManager: Destroyed Drawable with ID: " << id << std::endl;

                break;
            }
        }
    }

    Drawable* GetDrawableFromID(int id)
    {
        for (auto& drawable : drawablePool)
        {
            if (drawable->GetID() == id)
            {
                return drawable;
            }
        }

        return nullptr;
    }
}

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