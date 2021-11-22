#include "table.hpp"

Vector2 Ball::GetPosition()
{
    return { body->position.x - GetWidth() / 2, body->position.y - GetHeight() / 2 };
}

void Ball::Create()
{
    std::cout << "Called Ball::Create()" << std::endl;
    body = CreatePhysicsBodyCircle({ sprite_position->x + GetWidth() / 2, sprite_position->y + GetHeight() / 2 }, GetWidth() / 2, 1.0f);
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
        scale_factor,
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
    top_wall = CreatePhysicsBodyRectangle({ WINDOW_WIDTH / 2, 25 }, WINDOW_WIDTH, 50, 1);
    bottom_wall = CreatePhysicsBodyRectangle({ 0, GetHeight() - 50 }, WINDOW_WIDTH, 50, 1);

    top_wall->enabled = false;
    bottom_wall->enabled = false;

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
};

void Table::Update() {};