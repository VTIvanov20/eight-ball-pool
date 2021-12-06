#pragma once

enum Turn
{
    UNKNOWN = -1,
    SMALL_BALL = 0,
    BIG_BALL = 1,
};

struct TableState
{
    Turn current_turn;
    Turn player_winner;
    bool is_foul;
    int small_balls_inside;
    int big_balls_inside;
};