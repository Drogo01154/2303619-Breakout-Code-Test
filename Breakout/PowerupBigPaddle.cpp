#include "PowerupBigPaddle.h"
#include "GameManager.h"

PowerupBigPaddle::PowerupBigPaddle(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls, float x_pos)
    : PowerupBase(gameManager, window, paddle, balls, x_pos)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
}

PowerupBigPaddle::~PowerupBigPaddle()
{
}

std::pair<POWERUPS,float> PowerupBigPaddle::applyEffect()
{
    _paddle->setWidth(1.5f, 5.0f);
    return { bigPaddle, 5.0f };
}