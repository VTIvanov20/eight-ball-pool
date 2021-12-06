#pragma once

enum Turn
{
    // Enumerator of the possible turns
    UNKNOWN = -1,
    SMALL_BALL = 0,
    BIG_BALL = 1,
};

struct TableState
{
    // Table state struct
    Turn current_turn;
    Turn player_winner;
    bool is_foul;
    int small_balls_inside;
    int big_balls_inside;
};