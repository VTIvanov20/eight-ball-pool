#include "hud.hpp"

void HUD::Draw()
{
    if (state.player_winner)
    {
        switch(state.player_winner)
        {
        case Turn::SMALL_BALL:
            DrawText("Small ball player is the winner!", 0, 0, 50, WHITE);
            break;
        case Turn::BIG_BALL:
            DrawText("Big ball player is the winner!", 0, 0, 50, WHITE);
            break;
        default: break;
        }

        return;
    }

    switch (state.current_turn)
    {
    case Turn::UNKNOWN:
        DrawText("Unknown Turn", 0, 0, 30, WHITE);
        break;
    case Turn::SMALL_BALL:
        DrawText("Small ball player's Turn", 0, 0, 30, WHITE);
        break;
    case Turn::BIG_BALL:
        DrawText("Big ball player's Turn", 0, 0, 30, WHITE);
        break;
    }

    if (state.is_foul)
    {
        switch (state.current_turn)
        {
        case Turn::SMALL_BALL:
            DrawText("Foul! Small ball player gets to place the white ball", 0, 30, 20, WHITE);
            break;
        case Turn::BIG_BALL:
            DrawText("Foul! Big ball player gets to place the white ball", 0, 30, 20, WHITE);
            break;
        default: break;
        }

        DrawCircleV(GetMousePosition(), 25.f, WHITE);
    }
    
    Vector2 balls_amount_text_position;
    
    if (state.is_foul)
        balls_amount_text_position = {0, 50};
    else
        balls_amount_text_position = {0, 30};

    DrawText(
        TextFormat(
            "Small Balls in: %i\nBig Balls in: %i",
            state.small_balls_inside, state.big_balls_inside
        ),
        balls_amount_text_position.x, balls_amount_text_position.y, 10,
        WHITE
    );
}

void HUD::UpdateInternalState(TableState value)
{
    state = value;
}