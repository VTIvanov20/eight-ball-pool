#include "table.hpp"

Vector2 Ball::GetPosition()
{
    // Returns the position of a ball
    return { body->position.x - GetWidth() / 2, body->position.y - GetHeight() / 2 };
}

Vector2 Ball::GetVelocity()
{
    // Returns the velocity of a ball
    return { body->velocity.x, body->velocity.y };
}

void Ball::EnablePhysicsBody()
{
    // Enables the physicsbody of a ball
    body->enabled = true;
}

void Ball::DisablePhysicsBody()
{
    // Disables the physicsbody of a ball and sets it velocity and orient to 0
    body->enabled = false;
    body->velocity = { 0.f, 0.f };
    body->orient = 0.f;
}

void Ball::SetPosition(Vector2 position)
{
    // Sets the position of a ball
    body->position = { position.x + GetWidth() / 2, position.y + GetHeight() / 2 };
}

int Ball::GetNumber()
{
    // Returns the ball number of a ball
    return ball_number;
}

void Ball::Update()
{
    // Friction
    if (body->velocity.x != 0)
    {
        if (body->velocity.x < 0)
            body->velocity.x += 0.005f;
        
        if (body->velocity.x > 0)
            body->velocity.x -= 0.005f;
    }

    if (body->velocity.y != 0)
    {
        if (body->velocity.y < 0)
            body->velocity.y += 0.005f;
        
        if (body->velocity.y > 0)
            body->velocity.y -= 0.005f;
    }

    if ((body->velocity.x < 0.005f && body->velocity.x > -0.005f) && (body->velocity.y < 0.005f && body->velocity.y > -0.005f))
    {
        body->velocity.x = 0.0f;
        body->velocity.y = 0.0f;
    }
};

void Ball::Draw()
{
    Color colors[20] = {
        WHITE,
        { 255, 240, 0, 255 },
        { 72, 114, 212, 255 },
        { 255, 61, 61, 255 },
        { 86, 0, 123, 255 },
        { 254, 151, 54, 255 },
        { 22, 121, 57, 255 },
        { 140, 32, 20, 255 },
        BLACK,
        { 255, 240, 0, 255 },
        { 72, 114, 212, 255 },
        { 255, 61, 61, 255 },
        { 86, 0, 123, 255 },
        { 254, 151, 54, 255 },
        { 22, 121, 57, 255 },
        { 140, 32, 20, 255 }
    };

    // Draws the ball with the corresponding color for the ball number
    DrawTextureEx(
        sprite_texture,
        { body->position.x - GetWidth() / 2, body->position.y - GetHeight() / 2 },
        0.f,
        sprite_scale_factor,
        colors[ball_number]
    );

    // If the ball is the white ball doesn't write the number of the ball
    if (ball_number != 0)
    {
        DrawCircle(
            GetPosition().x + GetWidth() / 2, GetPosition().y + GetHeight() / 2,
            10,
            WHITE
        );

        DrawText(
            TextFormat(
                "%i",
                ball_number
            ),
            GetPosition().x + GetWidth() / 2 - 2.5, GetPosition().y + GetHeight() / 2 - 5,
            10, BLACK
        );
    }
}

void Ball::AddForce(Vector2 force)
{
    // Adds force to a ball
    PhysicsAddForce(body, force);
}

void Table::Create()
{
    // Creates colliders for the table
    top_wall[0] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH / 4 + 32.5f, 25 }, WINDOW_WIDTH / 2 - 125, 50, 1);
    top_wall[1] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH - WINDOW_WIDTH / 4 - 32.5f, 25 }, WINDOW_WIDTH / 2 - 125, 50, 1);

    bottom_wall[0] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH / 4 + 32.5f, WINDOW_HEIGHT - 40 }, WINDOW_WIDTH / 2 - 125, 50, 1);
    bottom_wall[1] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH - WINDOW_WIDTH / 4 - 32.5f, WINDOW_HEIGHT - 40 }, WINDOW_WIDTH / 2 - 125, 50, 1);

    left_wall[0] = CreatePhysicsBodyRectangle({ 25, WINDOW_HEIGHT / 2 - 7.5f }, 50, WINDOW_HEIGHT - 210, 1);
    left_wall[1] = CreatePhysicsBodyRectangle({ 25, WINDOW_HEIGHT / 2 - 7.5f }, 50, WINDOW_HEIGHT - 210, 1);

    right_wall[0] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH - 25, WINDOW_HEIGHT / 2 - 7.5f }, 50, WINDOW_HEIGHT - 210, 1);
    right_wall[1] = CreatePhysicsBodyRectangle({ WINDOW_WIDTH - 25, WINDOW_HEIGHT / 2 - 7.5f }, 50, WINDOW_HEIGHT - 210, 1);

    // Enables the colliders and makes them unmovable
    top_wall[0]->enabled = false;
    top_wall[1]->enabled = false;

    bottom_wall[0]->enabled = false;
    bottom_wall[1]->enabled = false;
    
    left_wall[0]->enabled = false;
    left_wall[1]->enabled = false;

    right_wall[0]->enabled = false;
    right_wall[1]->enabled = false;

    // Sets the restitution (bounciness) of the walls to 1
    top_wall[0]->restitution = 1;
    top_wall[1]->restitution = 1;

    bottom_wall[0]->restitution = 1;
    bottom_wall[1]->restitution = 1;
    
    left_wall[0]->restitution = 1;
    left_wall[1]->restitution = 1;

    right_wall[0]->restitution = 1;
    right_wall[1]->restitution = 1;
}

void Stick::Create()
{
    // Creates the stick and sets its scale to 0.7 and rotation to 180.0
    std::cout << "Called Stick::Create()" << std::endl;
    SetScale(0.7f);
    SetRotation(180.0f);
};

void Stick::Update()
{
    // Rotates the stick and increases and reduces force
    if (IsKeyDown(KEY_LEFT) && shown)
        sprite_rotation--;
    
    if (IsKeyDown(KEY_RIGHT) && shown)
        sprite_rotation++;

    if (IsKeyDown(KEY_DOWN) && force_amount >= 30.0f && shown)
        force_amount--;
    
    if (IsKeyDown(KEY_UP) && force_amount <= 80.0f && shown)
        force_amount++;

    if (IsKeyPressed(KEY_F1) && shown)
        sprite_rotation = 180.0;
    
    if (IsKeyPressed(KEY_F2) && shown)
        sprite_rotation = 270.0;

    if (IsKeyPressed(KEY_F3) && shown)
        sprite_rotation = 0.0;
    
    if (IsKeyPressed(KEY_F4) && shown)
        sprite_rotation = 90.0;

    if (sprite_rotation > 360) sprite_rotation = 0;
    if (sprite_rotation < 0) sprite_rotation = 359;
};

void Stick::Draw()
{
    // If the stick is shown, renders it
    if (shown)
    {
        DrawLineV({ GetPosition().x, GetPosition().y }, { GetCurrentForce().x + GetPosition().x, GetCurrentForce().y + GetPosition().y }, WHITE);

        DrawTexturePro(
            sprite_texture,
            { 0, 0, (float)sprite_texture.width, (float)sprite_texture.height },
            { sprite_position.x, sprite_position.y, sprite_texture.width * sprite_scale_factor, sprite_texture.height * sprite_scale_factor },
            { -force_amount, sprite_texture.height * (sprite_scale_factor / 2.f) },
            sprite_rotation,
            WHITE
        );
    }
}

void Stick::SetShown(bool value)
{
    // Sets the boolean variable shown of the stick
    shown = value;
}

void Stick::SetForce(float value)
{
    // Sets the force amount of the hit
    force_amount = value;
}

bool Stick::GetShown()
{
    // Returns whether or not the stick is shown
    return shown;
}

Vector2 Stick::GetCurrentForce()
{
    // Sets the force and returns the hit trajectory based on the rotation
    float factor = force_amount / 30;
    float force = force_amount * 50 * factor;

    if (sprite_rotation < 90)                            return { (sprite_rotation - 90) / 90 * force, sprite_rotation / 90 * -force };
    if (sprite_rotation >= 90 && sprite_rotation < 180)  return { (sprite_rotation - 90) / 90 * force, (sprite_rotation - 180) / 90 * force };
    if (sprite_rotation >= 180 && sprite_rotation < 270) return { (90 - (sprite_rotation - 180)) / 90 * force, (sprite_rotation - 180) / 90 * force };
    if (sprite_rotation >= 270)                          return { (90 - (sprite_rotation - 180)) / 90 * force, (90 - (sprite_rotation - 270)) / 90 * force };

    return { 0, 0 };
}