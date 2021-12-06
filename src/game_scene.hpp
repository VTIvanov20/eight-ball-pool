#pragma once

#include "drawable.hpp"
#include "table.hpp"
#include "hud.hpp"
#include "state.h"

class GameScene : public DrawableManager::Drawable
{
private:
    Turn current_turn;
    Turn player_winner;
    bool is_foul;
    bool any_balls_in_flag = false;
    int big_balls_inside;
    int small_balls_inside;

    std::list<Ball*> balls;
    Ball* white_ball;
    Stick* stick;
    
    HUD* user_interface;

    const Vector2 starting_ball_position = { 930, 350 };
    const Vector2 starting_white_ball_position = { 350, 350 };

public:
    GameScene() : Drawable()
    {
        current_turn = Turn::UNKNOWN;
        is_foul = false;
        big_balls_inside = 0;
        small_balls_inside = 0;
        player_winner = Turn::UNKNOWN;
    }

    virtual ~GameScene() = default;

    TableState GetTableState();

    void Create() override;
    void Update() override;
};