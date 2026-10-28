#include "Paddle.h"
#include "GameManager.h"
#include <iostream>


Paddle::Paddle(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true)
{
    sf::Vector2u gameDimensions = gameManager->getGameDimensions();
    //Store windows initial size
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, gameDimensions.y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
    {
        _sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
    }
}

void Paddle::moveRight(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _gameManager->getGameDimensions().x - _width)
    {
        _sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
    }
}

void Paddle::setHorizontalPosition(float newXPosition)
{
    //Calculate half size of paddle
    float halfWidth = _width / 2.f;

    sf::Vector2u gameDimensions = _gameManager->getGameDimensions();

    //get x position for new centre of paddle
    float checkPos = (newXPosition * gameDimensions.x) - (halfWidth);

    //get sprites current positon
    sf::Vector2f spritePos = _sprite.getPosition();
    
    //if new positon within bounds
    if ((checkPos < gameDimensions.x - _width) && (checkPos > 0)) {
        _sprite.setPosition(sf::Vector2f(checkPos, spritePos.y));
    }
}

void Paddle::update(float dt)
{
    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
    }
}

void Paddle::render()
{
    _window->draw(_sprite);
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    _width = coeff * PADDLE_WIDTH;
    _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    _timeInNewSize = duration;
    float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
    _sprite.setPosition(newX, _sprite.getPosition().y);
}
