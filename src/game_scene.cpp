#include "game_scene.hpp"

void GameScene::Create()
{
    new Table();
    
    for (int i = 1; i <= 5; i++)
    {
        float j;
        if (i % 2 == 0)
            j = 0.5 - i / 2;
        else
            j = 0 - i / 2;
            
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

    white_ball = new Ball(0, { 350, 350 });
    stick = new Stick(white_ball->GetPosition());

    white_ball->SetPosition({
        350 - white_ball->GetWidth() / 2,
        350 - white_ball->GetHeight() / 2
    });
};

void GameScene::Update()
{
    // Stick
    Vector2 white_ball_pos = white_ball->GetPosition();
    stick->SetPosition({ white_ball_pos.x + white_ball->GetWidth() / 2, white_ball_pos.y + white_ball->GetHeight() / 2 });

    // TODO: IMPLEMENT FORCE ADDING TO WHITE BALL PROPERLY
};