#pragma once

#include "PowerupBase.h"

class PowerupSmallPaddle : public PowerupBase
{
public:
    PowerupSmallPaddle(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls, float x_pos);
    ~PowerupSmallPaddle();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
