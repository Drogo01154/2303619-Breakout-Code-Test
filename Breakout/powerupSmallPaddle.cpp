#include "PowerupSmallPaddle.h"
#include "GameManager.h"

PowerupSmallPaddle::PowerupSmallPaddle(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls, float x_pos)
    : PowerupBase(gameManager, window, paddle, balls, x_pos)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as SmallPaddle
}

PowerupSmallPaddle::~PowerupSmallPaddle()
{
}

std::pair<POWERUPS, float> PowerupSmallPaddle::applyEffect()
{
    _paddle->setWidth(0.67f, 5.0f);
    return { smallPaddle, 5.0f };
}