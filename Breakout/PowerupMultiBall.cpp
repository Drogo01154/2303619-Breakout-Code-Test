#include "PowerupMultiBall.h"
#include "GameManager.h"

PowerupMultiBall::PowerupMultiBall(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls, float x_pos)
    : PowerupBase(gameManager, window, paddle, balls, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupMultiBall::~PowerupMultiBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }
}

std::pair<POWERUPS, float> PowerupMultiBall::applyEffect()
{
    for (Ball* ball : *_balls) {
        ball->setMultiBall(5.0f);
    }
    return { multiBall, 5.0f };
}