#include "table.hpp"

#include <math.h>

Vector2 Ball::GetPosition()
{
    return { body->position.x - GetWidth() / 2, body->position.y - GetHeight() / 2 };
}

void Ball::Create()
{
    std::cout << "Called Ball::Create()" << std::endl;
    body = CreatePhysicsBodyCircle({ sprite_position.x + GetWidth() / 2, sprite_position.y + GetHeight() / 2 }, GetWidth() / 2, 1.0f);
    body->restitution = 1.0f;
    body->dynamicFriction = 0.5f;
    body->staticFriction = 0.5f;
    body->enabled = true;
}

void Ball::Update()
{
    
};

void Ball::Draw()
{
    DrawTextureEx(
        sprite_texture,
        { body->position.x - GetWidth() / 2, body->position.y - GetHeight() / 2 },
        0.0f,
        sprite_scale_factor,
        WHITE
    );

    DrawText(
        TextFormat(
            "pos(%0.f, %0.f)\nvel(%0.f, %0.f)",
            GetPosition().x, GetPosition().y,
            body->velocity.x, body->velocity.y
        ),
        GetPosition().x + GetWidth(), GetPosition().y,
        10, WHITE
    );
}

void Table::Create()
{
    Vector2 position[6] =
    {
        { 25, 25 },
        { WINDOW_WIDTH / 2, -5 },
        { WINDOW_WIDTH - 25, 25 },
        { 25, WINDOW_HEIGHT - 25 - 15 },
        { WINDOW_WIDTH / 2, WINDOW_HEIGHT + 5 - 15 },
        { WINDOW_WIDTH - 25, WINDOW_HEIGHT - 25 - 15 }
    };

    top_wall[0] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH / 4 + 32.5f, 25 }, WINDOW_WIDTH / 2 - 125, 50, 1);
    top_wall[1] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH - WINDOW_WIDTH / 4 - 32.5f, 25 }, WINDOW_WIDTH / 2 - 125, 50, 1);

    bottom_wall[0] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH / 4 + 32.5f, WINDOW_HEIGHT - 40 }, WINDOW_WIDTH / 2 - 125, 50, 1);
    bottom_wall[1] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH - WINDOW_WIDTH / 4 - 32.5f, WINDOW_HEIGHT - 40 }, WINDOW_WIDTH / 2 - 125, 50, 1);

    left_wall[0] = CreatePhysicsBodyRectangle({ 25, WINDOW_HEIGHT / 2 - 7.5f }, 50, WINDOW_HEIGHT - 210, 1);
    left_wall[1] = CreatePhysicsBodyRectangle({ 25, WINDOW_HEIGHT / 2 - 7.5f }, 50, WINDOW_HEIGHT - 210, 1);

    right_wall[0] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH - 25, WINDOW_HEIGHT / 2 - 7.5f }, 50, WINDOW_HEIGHT - 210, 1);
    right_wall[1] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH - 25, WINDOW_HEIGHT / 2 - 7.5f }, 50, WINDOW_HEIGHT - 210, 1);

    for (int i = 0; i < 6; i++)
    {
        hole[i] = CreatePhysicsBodyCircle(position[i], 30, 1);
        hole[i]->enabled = false;
    }

    top_wall[0]->enabled = false;
    top_wall[1]->enabled = false;

    bottom_wall[0]->enabled = false;
    bottom_wall[1]->enabled = false;
    
    left_wall[0]->enabled = false;
    left_wall[1]->enabled = false;

    right_wall[0]->enabled = false;
    right_wall[1]->enabled = false;

    for (int i = 1; i <= 5; i++)
    {
        float j;
        if (i % 2 == 0)
            j = 0.5 - i / 2;
        else
            j = 0 - i / 2;

        std::cout << j << std::endl;
            
        for (; j < (float)i / 2; j++)
        {
            balls.push_back(new Ball(i + j, starting_ball_position));

            // gets last element (in iterator) of std::list
            // converts iterator to type
            Ball* ballPtr = *(--balls.end());

            ballPtr->SetPosition({
                starting_ball_position.x - ballPtr->GetWidth() / 2 + ballPtr->GetWidth() * (i - 1) - ballPtr->GetWidth() * 2,
                starting_ball_position.y - ballPtr->GetHeight() / 2 + j * ballPtr->GetHeight()
            });
        }
    }

    whiteBall = new Ball(0, { 350, 350 });

    whiteBall->SetPosition({
        350 - whiteBall->GetWidth() / 2,
        350 - whiteBall->GetHeight() / 2
    });

    stick = new Stick();
};

void Table::Update()
{
    // Stick
    
    /*float dy, dx;
    dy = GetMousePosition().x - whiteBall->GetPosition().x;
    dx = GetMousePosition().y - whiteBall->GetPosition().y;

    stick->SetRotation(atan2f(-dy, dx));*/
    stick->SetPosition({ whiteBall->GetPosition().x - stick->GetWidth() / 2, whiteBall->GetPosition().y - stick->GetHeight() / 2 });
    //stick->SetRotation();
};

void Stick::Create()
{
    std::cout << "Called Stick::Create()" << std::endl;
};

void Stick::Update()
{
    //SetPosition({ GetMouseX() - GetWidth() / 2, GetMouseY() - GetHeight() / 2 });
};