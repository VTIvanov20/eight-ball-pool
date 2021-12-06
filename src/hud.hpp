#pragma once

#include "drawable.hpp"
#include "state.h"

class HUD : public DrawableManager::Drawable
{
private:
    int timer;
    TableState state;

public:
    HUD() : Drawable()
    {
        timer = 0;
        state.current_turn = Turn::UNKNOWN;
        state.is_foul = false;
        state.small_balls_inside = 0;
        state.big_balls_inside = 0;
    };
    ~HUD() = default;

    void UpdateInternalState(TableState value);

    void Draw() override;
};