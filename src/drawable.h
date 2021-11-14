#pragma once

#include <raylib.h>
#include <iostream>

class Drawable
{
public:
    Drawable() = default;
    virtual ~Drawable() = default;

    virtual void Create() {};
    virtual void Update() {};
    virtual void Draw() {};
};

class Sprite : public Drawable
{
protected:
    Rectangle* position;
    Texture2D texture;

public:
    Sprite(const char* texture_file_name, Rectangle initial_position)
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