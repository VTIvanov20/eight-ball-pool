#include "game_scene.hpp"

void GameScene::Create()
{
    // Creates the table when the gamescene is created
    new Table();
    
    int index = 0;
    int number;
    int placed[20];

    bool isPlaced = false;

    // Returns a different seed every time a rand() function is called
    srand(time(0));

    // Draws all the balls
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
                // Randomizes the ball configuration and following the ball configuration formation rules
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

            // Gets last element (in iterator) of std::list
            // Converts iterator to type
            Ball* ball_ptr = *(--balls.end());

            ball_ptr->SetPosition({
                starting_ball_position.x - ball_ptr->GetWidth() / 2 + ball_ptr->GetWidth() * (i - 1) - ball_ptr->GetWidth() * 2,
                starting_ball_position.y - ball_ptr->GetHeight() / 2 + j * ball_ptr->GetHeight()
            });

            ball_ptr->DisablePhysicsBody();
        }
    }

    // Defines a new Ball variable, which is the white ball and a new stick variable which is the pool cue's
    white_ball = new Ball(0, starting_white_ball_position);
    stick = new Stick(white_ball->GetPosition());

    // Defines a new Heads-up Display variable
    user_interface = new HUD();

    white_ball->SetPosition({
        350 - white_ball->GetWidth() / 2,
        350 - white_ball->GetHeight() / 2
    });

    white_ball->DisablePhysicsBody();
};

void GameScene::Update()
{
    // Updates the state of the table through the UpdateInternalState function
    user_interface->UpdateInternalState(GetTableState());

    // Defines a Vector2 variable of the white ball and sticks the stick to it
    Vector2 white_ball_pos = white_ball->GetPosition();
    stick->SetPosition({ white_ball_pos.x + white_ball->GetWidth() / 2, white_ball_pos.y + white_ball->GetHeight() / 2 });

    if (player_winner != Turn::UNKNOWN)
        return;
    
    // Const Vector2 array for the position of every hole
    const Vector2 position[6] =
    {
        { 25, 25 },
        { WINDOW_WIDTH / 2, -5 },
        { WINDOW_WIDTH - 25, 25 },
        { 25, WINDOW_HEIGHT - 25 - 15 },
        { WINDOW_WIDTH / 2, WINDOW_HEIGHT + 5 - 15 },
        { WINDOW_WIDTH - 25, WINDOW_HEIGHT - 25 - 15 }
    };

    // Checks whether the white ball touches any of the holes
    for (int i = 0; i < 6; i++)
    {
        if (CheckCollisionCircles(position[i], 30.f, { white_ball->GetPosition().x + 25.f, white_ball->GetPosition().y + 25.f }, white_ball->GetWidth()))
        {
            // If it does, trigger a foul
            white_ball->DisablePhysicsBody();
            white_ball->SetPosition({ -white_ball->GetWidth() * 2, -white_ball->GetHeight() * 2 });

            if (!user_interface->GetHasWon())
            {
                if (current_turn != Turn::UNKNOWN)
                    current_turn = (Turn)!current_turn;
                else
                    current_turn = Turn::UNKNOWN;
                is_foul = true;
            }
        }
    }

    // Checks whether all of the other balls touch any of the holes
    for (auto ball : balls)
    {
        for (int i = 0; i < 6; i++)
        {
            if (CheckCollisionCircles(position[i], 30.f, { ball->GetPosition().x + 25.f, ball->GetPosition().y + 25.f }, ball->GetWidth()))
            {
                ball->DisablePhysicsBody();
                ball->SetPosition({ -ball->GetWidth() * 2, -ball->GetHeight() * 2 });
                
                // Checks if the ball that just got in is small or big
                if (ball->GetNumber() < 8)
                    small_balls_inside++;
                else if (ball->GetNumber() > 8)
                    big_balls_inside++;

                // Sets a bool variable whether or not a ball just got in
                any_balls_in_flag = true;

                // If nobody has scored yet assignes the small and big balls to every player
                if (current_turn == Turn::UNKNOWN)
                {
                    if (ball->GetNumber() < 8)
                        current_turn = Turn::SMALL_BALL;
                    else if (ball->GetNumber() > 8)
                        current_turn = Turn::BIG_BALL;
                }
                else
                {
                    // If a player has scored a ball that is not his, there is a foul
                    if (current_turn == Turn::SMALL_BALL && ball->GetNumber() > 8)
                    {
                        is_foul = true;
                        current_turn = Turn::BIG_BALL;
                        white_ball->SetPosition({ -white_ball->GetWidth() * 2, -white_ball->GetHeight() * 2 });
                        white_ball->DisablePhysicsBody();
                    }
                    else if (current_turn == Turn::BIG_BALL && ball->GetNumber() < 8)
                    {
                        is_foul = true;
                        current_turn = Turn::SMALL_BALL;
                        white_ball->SetPosition({ -white_ball->GetWidth() * 2, -white_ball->GetHeight() * 2 });
                        white_ball->DisablePhysicsBody();
                    }
                }

                // Checks who scored the eight ball
                if (ball->GetNumber() == 8)
                {
                    if (current_turn == Turn::SMALL_BALL && small_balls_inside == 7)
                        player_winner = Turn::SMALL_BALL;
                    else if (!any_balls_in_flag)
                        player_winner = Turn::BIG_BALL;
                    else
                        player_winner = Turn::SMALL_BALL;
                        
                    if (current_turn == Turn::BIG_BALL && big_balls_inside == 7)
                        player_winner = Turn::BIG_BALL;
                    else if (!any_balls_in_flag)
                        player_winner = Turn::SMALL_BALL;
                    else
                        player_winner = Turn::BIG_BALL;

                    if (current_turn == Turn::UNKNOWN)
                        player_winner = Turn::UNKNOWN;

                    // Sets the hasWon boolean variable to true
                    user_interface->SetHasWon();
                }
            }
        }
    }

    // Checks if there is a foul and if there is performs it
    if (is_foul)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            bool can_place = true;

            // Checks if the player can place the white ball where he wants to
            for (auto ball : balls)
            {
                if (CheckCollisionCircles(
                    { GetMousePosition().x - ball->GetWidth() / 2, GetMousePosition().y - ball->GetHeight() / 2 },
                    white_ball->GetWidth() / 2, ball->GetPosition(), ball->GetWidth() / 2
                )) can_place = false;
            }

            // Checks if the player can place the white ball where he wants to
            for (int i = 0; i < 6; i++)
            {
                if (CheckCollisionCircles(
                    position[i], 30.f,
                    { GetMousePosition().x - white_ball->GetWidth() / 2, GetMousePosition().y - white_ball->GetHeight() / 2 }, white_ball->GetWidth() / 2
                )) can_place = false;
            }

            // If the player can place the white ball there, it gets placed
            if (can_place)
            {
                is_foul = false;
                if (current_turn == Turn::UNKNOWN)
                    current_turn = Turn::UNKNOWN;
                else if (!any_balls_in_flag)
                    current_turn = (Turn)!current_turn;

                white_ball->SetPosition({
                    GetMousePosition().x - white_ball->GetWidth() / 2,
                    GetMousePosition().y - white_ball->GetHeight() / 2
                });
                stick->SetRotation(180.0f);
            }
        }
    }

    // If the velocity of the white ball is 0 and there is no foul, it shows the pool cue's
    if (white_ball->GetVelocity().x == 0 && white_ball->GetVelocity().y == 0 && !is_foul)
    {
        if (!any_balls_in_flag && !stick->GetShown() && current_turn != Turn::UNKNOWN)
            current_turn = (Turn)!current_turn;
        
        stick->SetShown(true);
        white_ball->DisablePhysicsBody();

        for (auto ball : balls)
            ball->DisablePhysicsBody();

        if (white_ball->GetPosition().x < 0)
            white_ball->SetPosition({
                starting_white_ball_position.x - white_ball->GetWidth() / 2,
                starting_white_ball_position.y - white_ball->GetHeight() / 2
            });
    }
    else stick->SetShown(false);

    // If the key Space is pressed, hit the white ball with the pool cue's
    if (IsKeyPressed(KEY_SPACE) && stick->GetShown())
    {
        white_ball->EnablePhysicsBody();

        for (auto ball : balls)
            ball->EnablePhysicsBody();

        // Changes between Player 1 and Player 2
        user_interface->SetPlayer(!user_interface->GetPlayer());
        any_balls_in_flag = false;

        // Ball
        white_ball->AddForce(stick->GetCurrentForce());

        // Stick
        stick->SetRotation(180.0f);
        stick->SetForce(30.0f);
    }
};

// Returns the current TableState
TableState GameScene::GetTableState()
{
    return
    {
        current_turn,
        player_winner,
        is_foul,
        small_balls_inside,
        big_balls_inside
    };
}