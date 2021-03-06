#include "hud.hpp"

void HUD::Draw()
{
    // If the game has been won, write the winner text and delete all other text
    if (hasWon)
    {
        switch(state.player_winner)
        {
        case Turn::UNKNOWN:
            DrawText(TextFormat("Player %i is the winner!", player + 1), 10, 10, 50, WHITE);
            break;
        case Turn::SMALL_BALL:
            DrawText("Small ball player is the winner!", 10, 10, 50, WHITE);
            break;
        case Turn::BIG_BALL:
            DrawText("Big ball player is the winner!", 10, 10, 50, WHITE);
            break;
        }

        // Stop all the writing here
        return;
    }

    switch (state.current_turn)
    {
    case Turn::UNKNOWN:
        DrawText(TextFormat("Player %i's Turn", player + 1), 10, 10, 30, WHITE);
        break;
    case Turn::SMALL_BALL:
        DrawText("Small ball player's Turn", 10, 10, 30, WHITE);
        break;
    case Turn::BIG_BALL:
        DrawText("Big ball player's Turn", 10, 10, 30, WHITE);
        break;
    }

    // If there is a foul, write text that says there is one
    if (state.is_foul)
    {
        switch (state.current_turn)
        {
        case Turn::UNKNOWN:
            DrawText(TextFormat("Foul! Player %i gets to place the white ball.", player + 1), 10, 45, 20, WHITE);
            break;
        case Turn::SMALL_BALL:
            DrawText("Foul! Small ball player gets to place the white ball.", 10, 45, 20, WHITE);
            break;
        case Turn::BIG_BALL:
            DrawText("Foul! Big ball player gets to place the white ball.", 10, 45, 20, WHITE);
            break;
        }

        DrawCircleV(GetMousePosition(), 25.f, WHITE);
    }
    
    // Bring the balls amount text position down if there is a foul
    Vector2 balls_amount_text_position;
    
    if (state.is_foul)
        balls_amount_text_position = {10, 72.5f};
    else
        balls_amount_text_position = {10, 50};

    DrawText(
        TextFormat(
            "Small Balls in: %i\nBig Balls in: %i",
            state.small_balls_inside, state.big_balls_inside
        ),
        balls_amount_text_position.x, balls_amount_text_position.y, 12,
        WHITE
    );
}

// Update TableState
void HUD::UpdateInternalState(TableState value)
{
    state = value;
}

// Set the current Player
void HUD::SetPlayer(bool value)
{
    player = value;
}

// Set the boolean variable if the game has been won
void HUD::SetHasWon()
{
    player = !player;
    hasWon = true;
}

// Returns which player is in turn right now
bool HUD::GetPlayer()
{
    return player;
}

// Returns the boolean variable if the game has been won
bool HUD::GetHasWon()
{
    return hasWon;
}