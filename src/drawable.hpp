#pragma once

#include <raylib.h>
#include <iostream>
#include <list>

// DrawableManager - Consists of functions which make drawable management easier
// The point of this is so you can create Drawables at any point in the program
namespace DrawableManager
{
    class Drawable
    {
    private:
        int id;

    public:
        Drawable();
        virtual ~Drawable() = default;

        virtual void Create() {}; // Gets called once whenever the program is initializing itself
        virtual void Update() {}; // Gets called once per frame
        virtual void Draw() {}; // Gets called once per frame (after Update)

        int GetID()
        {
            return id;
        }
    };
    
    void CreateAll(); // Calls Create function in every Drawable in drawablePool
    void UpdateAll(); // Calls Update function in every Drawable in drawablePool
    void DrawAll(); // Calls Draw function in every Drawable in drawablePool

    void DestroyAllDrawables(); // Destroys every Drawable in drawablePool and clears drawablePool
    void DestroyDrawableFromID(int id); // Iterates through drawablePool and destroys the Drawable corresponding to the ID

    Drawable* GetDrawableFromID(int id); // Iterates through drawablePool and gets the Drawable corresponding to the ID (returns nullptr if ID is non-existent)
};