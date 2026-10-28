#include "PowerupFastBall.h"
#include "GameManager.h"

PowerupFastBall::PowerupFastBall(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls, float x_pos)
    : PowerupBase(gameManager, window, paddle, balls, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupFastBall::~PowerupFastBall()
{
}

std::pair<POWERUPS, float> PowerupFastBall::applyEffect()
{
    for (Ball* ball : *_balls) {
        ball->setVelocity(2.f, 5.0f);
    }
    return { fastBall, 5.0f };
}