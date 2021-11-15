#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>

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
}

class Sprite : public DrawableManager::Drawable
{
protected:
    Rectangle* position;
    Texture2D texture;

public:
    Sprite(const char* texture_file_name, Rectangle initial_position) : Drawable()
    {
        position = new Rectangle;
        position->x = initial_position.x;
        position->y = initial_position.y;
        position->width = initial_position.width;
        position->height = initial_position.height;
        texture = LoadTexture(texture_file_name);
        
        if (texture.id == 0)
        {
            std::cout << "ERROR: Failed loading texture (" << texture_file_name << "), halting process" << std::endl;
            exit(-1);
        }
    }

    virtual ~Sprite()
    {
        UnloadTexture(texture);
        delete position;
    }

    void Create() override;
    void Update() override;
    void Draw() override;
};

class Player : public Sprite
{
public:
    Player(const char* sprite_file_name, Rectangle initial_pos)
        : Sprite(sprite_file_name, initial_pos) {}
    
    virtual ~Player() {};

    void Update() override;
};