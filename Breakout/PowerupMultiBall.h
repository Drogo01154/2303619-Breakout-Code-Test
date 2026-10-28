#pragma once
#include "PowerupBase.h"
class PowerupMultiBall : public PowerupBase
{
public:
    PowerupMultiBall(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls, float x_pos);
    ~PowerupMultiBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};