#include "game_scene.hpp"

void GameScene::Create()
{
    new Table();
    
    int index = 0;
    int number;
    int placed[20];

    bool isPlaced = false;

    srand(time(0));

    for (int i = 1; i <= 5; i++)
    {
        float j;
        if (i % 2 == 0)
            j = 0.5 - i / 2;
        else
            j = 0 - i / 2;
            
        for (; j < (float)i / 2; j++)
        {
            if (index == 4)
                balls.push_back(new Ball(8, starting_ball_position));
            else
            {
                do {
                    isPlaced = false;
                    if (index == 0 || index == 1 || index == 5 || index == 6 || index == 8 || index == 12 || index == 14)
                        number = rand() % 7 + 9;
                    else
                        number = rand() % 7 + 1;
                    for (int i = 0; i < index; i++)
                    {
                        if (placed[i] == number)
                            isPlaced = true;
                    }
                } while (isPlaced);
                balls.push_back(new Ball(number, starting_ball_position));
                placed[index] = number;
            }
            index++;

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
    // Stick Position
    Vector2 white_ball_pos = white_ball->GetPosition();
    stick->SetPosition({ white_ball_pos.x + white_ball->GetWidth() / 2, white_ball_pos.y + white_ball->GetHeight() / 2 });

    if (IsKeyPressed(KEY_SPACE) && stick->GetShown())
    {
        // Ball
        white_ball->AddForce(stick->GetCurrentForce());

        // Stick
        stick->SetRotation(0.0f);
        stick->SetForce(30.0f);
    }

    if (white_ball->GetVelocity().x == 0 && white_ball->GetVelocity().y == 0) stick->SetShown(true);
    else stick->SetShown(false);
};