#include "drawable.hpp"

namespace DrawableManager
{
    std::list<Drawable*> drawablePool;
    int currentId = 0;

    Drawable::Drawable()
    {
        id = currentId;
        ++currentId;

        // Sets the id of the current sprite as the currentId variable and then moves on to the next sprite

        std::cout << "INFO: DrawableManager: Created Drawable with ID: " << id << std::endl;

        drawablePool.push_back(this);
    }

    void CreateAll()
    {
        for (auto& drawable : drawablePool)
        {
            drawable->Create();
        }

        // Calls the Create() function for every drawable in the drawablePool
    }

    void UpdateAll()
    {
        for (auto& drawable : drawablePool)
        {
            drawable->Update();
        }

        // Calls the Update() function for every drawable in the drawablePool
    }

    void DrawAll()
    {
        for (auto& drawable : drawablePool)
        {
            drawable->Draw();
        }

        // Calls the Draw() function for every drawable in the drawablePool
    }

    void DestroyAllDrawables()
    {
        for (auto& drawable : drawablePool)
        {
            std::cout << "INFO: DrawableManager: Destroyed Drawable with ID: " << drawable->GetID() << std::endl;

            delete drawable;
        }

        // Deletes every drawable in the drawablePool and then clears it and sets the currentId variable to 0

        drawablePool.clear();
        currentId = 0;
    }

    void DestroyDrawableFromID(int id)
    {
        for (auto drawable = drawablePool.begin(); drawable != drawablePool.end(); ++drawable)
        {
            Drawable* drawablePtr = *drawable;
            // Makes a pointer of the current drawable in the drawablePool

            if (drawablePtr->GetID() == id)
            {
                drawablePool.erase(drawable);
                delete drawablePtr;

                // Checks if the drawable pointer has the id we want to destroy
                // If it is it erases it and deletes it

                std::cout << "INFO: DrawableManager: Destroyed Drawable with ID: " << id << std::endl;

                break;
            }
        }

        // Deletes a drawable by getting the specific id of a sprite
    }

    Drawable* GetDrawableFromID(int id)
    {
        for (auto& drawable : drawablePool)
        {
            // Checks every drawable in the drawablePool
            if (drawable->GetID() == id)
            {
                // Checks if the drawable from the for loop has the id we want to destroy
                // If it is we return it

                return drawable;
            }
        }

        // If it isn't we return null
        return nullptr;

        // Returns a drawable by getting the specific id of a sprite
    }
}