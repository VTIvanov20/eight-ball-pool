#pragma once

#include "sprite.hpp"
#include "config.h"
#include <list>
#include <physac.h>
#include <iostream>

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
        scale_factor = 50.0f / sprite_texture.width;
    }

    virtual ~Ball()
    {
        DestroyPhysicsBody(body);
    }

    void Create() override;
    void Update() override;
    void Draw() override;
};

class Table : public Sprite
{
private:
    std::list<Ball*> balls;
    const Vector2 starting_ball_position = {930, 352};

public:
    Table() : Sprite("resources/images/table.png", {})
    {
        scale_factor = (float)WINDOW_WIDTH / sprite_texture.width;
    }

    virtual ~Table() = default;

    void Create() override;
    void Update() override;
};