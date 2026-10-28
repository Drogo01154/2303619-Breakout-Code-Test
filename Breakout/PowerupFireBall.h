#pragma once
#include "PowerupBase.h"
class PowerupFireBall : public PowerupBase
{
public:
    PowerupFireBall(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls, float x_pos);
    ~PowerupFireBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

