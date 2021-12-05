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

        body = CreatePhysicsBodyCircle({ sprite_position.x + GetWidth() / 2, sprite_position.y + GetHeight() / 2 }, GetWidth() / 2, .5f);
        body->restitution = 1.0f;
        body->dynamicFriction = 0.5f;
        body->staticFriction = 0.5f;
        body->enabled = true;
    }

    virtual ~Ball() = default;

    Vector2 GetPosition();
    Vector2 GetVelocity();
    void SetPosition(Vector2 pos);
    void AddForce(Vector2 force);

    void Update() override;
    void Draw() override;
};

class Stick : public Sprite
{
private:
    const Vector2 starting_stick_position = { WINDOW_WIDTH / 2 - 340, WINDOW_HEIGHT / 2 };
    float force_amount;
    bool shown;

public:
    Stick(Vector2 position) : Sprite("resources/images/stick.png", position)
    {
        sprite_scale_factor = 0.8f;
        force_amount = 30.f;
        shown = true;
    }

    virtual ~Stick() = default;

    void SetShown(bool value);
    void SetForce(float value);
    bool GetShown();
    Vector2 GetCurrentForce();

    void Create() override;
    void Update() override;
    void Draw() override;
};

class Table : public Sprite
{
private:
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

    void Create() override;
};

