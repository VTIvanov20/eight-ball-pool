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

        /**
         * @brief Sets the sprites' IDs. 
         */
        
    public:
        Drawable();
        virtual ~Drawable() = default;

        virtual void Create() {}; // Gets called once whenever the program is initializing itself
        virtual void Update() {}; // Gets called once per frame
        virtual void Draw() {}; // Gets called once per frame (after Update)

        int GetID()
        {
            return id;

            /**
             * @brief Gets the IDs of the sprites.
             * 
             * @returns int id
             */
        }
    };
    
    /**
     * @brief Calls the Create() function for every Drawable in the drawablePool
     */
    void CreateAll();

    /**
     * @brief Calls the Update() function for every Drawable in the drawablePool
     */
    void UpdateAll(); 

    /**
     * @brief Calls the Draw() function for every Drawable in the drawablePool
     */
    void DrawAll();

    /**
     * @brief Destroys every Drawable in the drawablePool and clears drawablePool
     */
    void DestroyAllDrawables();

    /**
     * @brief Iterates through drawablePool and destroys the Drawable corresponding to the ID
     * 
     * @param id This describes the sprite's id
     */
    void DestroyDrawableFromID(int id);

    /**
     * @brief Get the Drawable From ID object
     * 
     * Iterates through drawablePool and gets the Drawable corresponding to the ID (returns nullptr if ID is non-existent)
     * 
     * @param id This describes the sprite's id
     * 
     * @return Drawable*
     */
    Drawable* GetDrawableFromID(int id);
};