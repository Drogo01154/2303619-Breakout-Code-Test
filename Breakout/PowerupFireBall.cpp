#include "PowerupFireBall.h"
#include "GameManager.h"


PowerupFireBall::PowerupFireBall(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls, float x_pos)
    : PowerupBase(gameManager, window, paddle, balls, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupFireBall::~PowerupFireBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }
}

std::pair<POWERUPS, float> PowerupFireBall::applyEffect()
{
    for (Ball* ball : *_balls) {
        ball->setFireBall(5.0f);
    }
    return { fireBall, 5.0f };
}