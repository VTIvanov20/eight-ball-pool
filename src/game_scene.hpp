#pragma once

#include "drawable.hpp"
#include "table.hpp"

class GameScene : public DrawableManager::Drawable
{
private:
    std::list<Ball*> balls;
    Ball* white_ball;

    Stick* stick;

    const Vector2 starting_ball_position = {930, 350};

public:
    GameScene() : Drawable()
    {}

    virtual ~GameScene() = default;

    void Create() override;
    void Update() override;
};