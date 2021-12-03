#include "table.hpp"

Vector2 Ball::GetPosition()
{
    return { body->position.x - GetWidth() / 2, body->position.y - GetHeight() / 2 };
}

void Ball::SetPosition(Vector2 position)
{
    body->position = { position.x + GetWidth() / 2, position.y + GetHeight() / 2 };
}

void Ball::Update()
{
    
};

void Ball::Draw()
{
    DrawTextureEx(
        sprite_texture,
        { body->position.x - GetWidth() / 2, body->position.y - GetHeight() / 2 },
        0.f,
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

void Ball::AddForce(Vector2 force)
{
    PhysicsAddForce(body, force);
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
}

void Stick::Create()
{
    std::cout << "Called Stick::Create()" << std::endl;
    SetScale(0.7f);
};

void Stick::Update()
{
    if (IsKeyDown(KEY_Q))
        sprite_rotation--;
    
    if (IsKeyDown(KEY_E))
        sprite_rotation++;

    if (sprite_rotation > 360) sprite_rotation = 0;
    if (sprite_rotation < 0) sprite_rotation = 359;
    
    if (IsKeyDown(KEY_A) && force_amount >= 30.0f)
        force_amount--;
    
    if (IsKeyDown(KEY_D) && force_amount <= 80.0f)
        force_amount++;
};

void Stick::Draw()
{
    DrawTexturePro(
        sprite_texture,
        { 0, 0, (float)sprite_texture.width, (float)sprite_texture.height },
        { sprite_position.x, sprite_position.y, sprite_texture.width * sprite_scale_factor, sprite_texture.height * sprite_scale_factor },
        { -force_amount, sprite_texture.height * (sprite_scale_factor / 2.f) },
        sprite_rotation,
        WHITE
    );
}

void Stick::SetShown(bool value)
{
    shown = value;
}

Vector2 Stick::GetCurrentForce()
{
    // TODO: IMPLEMENT PROPERLY
    float force = force_amount * 50;
    return { force - sprite_rotation / 360 * force, 0.f - sprite_rotation };
}