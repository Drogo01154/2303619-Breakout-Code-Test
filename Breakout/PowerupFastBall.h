#pragma once
#include "PowerupBase.h"
class PowerupFastBall : public PowerupBase
{
public:
    PowerupFastBall(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* _balls, float x_pos);
    ~PowerupFastBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect


};

