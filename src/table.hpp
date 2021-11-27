#pragma once

#include "sprite.hpp"
#include "config.h"
#include <list>
#include <physac.h>
#include <raylib.h>
#include <iostream>
#include <string>

class Ball : public Sprite
{
private:
    int ball_number;
    PhysicsBody body;

public:
    Ball(int number, Vector2 initial_position) 
        : Sprite(
            Sprite("resources/images/white_ball.png", initial_position)
            // number == 0 ?
            //     Sprite("resources/images/white_ball.png", initial_position) :
            //     number == 8 ?
            //         Sprite("resources/images/black_ball.png", initial_position) : 
            //         number <= 7 ?
            //             Sprite("resources/images/yellow_ball.png", initial_position) :
            //             Sprite("resources/images/red_ball.png", initial_position)
        )
    {
        std::cout << "Called Ball()" << std::endl;
        ball_number = number;
        sprite_scale_factor = 50.0f / sprite_texture.width;
    }

    virtual ~Ball()
    {
        DestroyPhysicsBody(body);
    }

    Vector2 GetPosition();

    void Create() override;
    void Update() override;
    void Draw() override;
};

class Stick : public Sprite
{
private:
    const Vector2 starting_stick_position = { WINDOW_WIDTH / 2 - 340, WINDOW_HEIGHT / 2 };

public:
    Stick() : Sprite("resources/images/stick.png", {})
    {
        sprite_scale_factor = (float)WINDOW_WIDTH / sprite_texture.width;
    }

    virtual ~Stick() = default;

    void Create() override;
    void Update() override;
};

class Table : public Sprite
{
private:
    std::list<Ball*> balls;
    Ball* whiteBall;

    Stick* stick;

    const Vector2 starting_ball_position = {930, 350};

    PhysicsBody top_wall[2];
    PhysicsBody bottom_wall[2];
    PhysicsBody left_wall[2];
    PhysicsBody right_wall[2];

    PhysicsBody hole[6];

public:
    Table() : Sprite("resources/images/table.png", {})
    {
        sprite_scale_factor = (float)WINDOW_WIDTH / sprite_texture.width;
    }

    virtual ~Table()
    {
        delete whiteBall;
        delete stick;
        for (int i = 0; i < 2; i++)
        {
            DestroyPhysicsBody(top_wall[i]);
            DestroyPhysicsBody(bottom_wall[i]);
            DestroyPhysicsBody(left_wall[i]);
            DestroyPhysicsBody(right_wall[i]);
        }

        for (int i = 0; i < 6; i++)
        {
            DestroyPhysicsBody(hole[i]);
        }
    };

    void Create() override;
    void Update() override;
};