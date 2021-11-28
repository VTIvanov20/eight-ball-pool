#include "drawable.hpp"

namespace DrawableManager
{
    std::list<Drawable*> drawablePool;
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
            std::cout << "INFO: DrawableManager: Destroyed Drawable with ID: " << drawable->GetID() << std::endl;

            delete drawable;
        }

        drawablePool.clear();
        currentId = 0;
    }

    void DestroyDrawableFromID(int id)
    {
        for (auto drawable = drawablePool.begin(); drawable != drawablePool.end(); ++drawable)
        {
            Drawable* drawablePtr = *drawable;

            if (drawablePtr->GetID() == id)
            {
                drawablePool.erase(drawable);
                delete drawablePtr;

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