#pragma once

#include "PowerupManager.h"

class PowerupBigPaddle : public PowerupBase
{
public:
    PowerupBigPaddle(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls, float x_pos);
    ~PowerupBigPaddle();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
