#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class GameManager;  // forward declaration

class Paddle
{
public:
    Paddle(sf::RenderWindow* window, GameManager* gameManager);
    ~Paddle();

    void moveLeft(float dt);
    void moveRight(float dt);
    void setHorizontalPosition(float x);
    void update(float dt);
    void render();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);

private:


    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    GameManager* _gameManager;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
};
