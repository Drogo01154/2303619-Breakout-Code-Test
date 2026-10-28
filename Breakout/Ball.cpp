#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies
#include <cmath>

Ball::Ball(sf::RenderWindow* window, float velocity, sf::Vector2f position, sf::Vector2f direction, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _type(BallType::BASIC), _isAlive(true), _direction(direction)
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(position);
}

Ball::~Ball()
{
}

sf::Vector2f rotateDirectionDegrees(sf::Vector2f direction, float rotation) {
    static const double PI = 3.14159265358979323846;
    
    float theta = rotation * (PI / 180.0);

    float cs = std::cos(theta);
    float sn = std::sin(theta);

    return(sf::Vector2f(
        direction.x * cs - (direction.y * sn),
        direction.x * sn + (direction.y * cs)
    ));
}

bool Ball::update(float dt)
{
    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY)
            _velocity = VELOCITY;   // reset speed.
        else
        {
            clearType();
        }        
    }

    // Fireball effect
    if (_type == BallType::FIREBALL)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u gameDimensions = _gameManager->getGameDimensions();

    // bounce on walls
    if ((position.x >= gameDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
    }

    // lose life bounce
    if (position.y > gameDimensions.y)
    {
        return true;
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_type == BallType::FIREBALL) return false; // no collisisons when in fireBall mode.
    if ((collisionResponse > 0) && (_type == BallType::MULTIBALL)) {
        //Spawn Balls
        
        //Calculate new balls directions
        sf::Vector2f leftBallDir = rotateDirectionDegrees(_direction, 25.f);
        sf::Vector2f rightBallDir = rotateDirectionDegrees(_direction, -25.f);

        // Spawn new balls 
        _gameManager->createBall(_velocity, _sprite.getPosition(), leftBallDir);
        _gameManager->createBall(_velocity, _sprite.getPosition(), rightBallDir);

        //Stop multi ball powerup
        _gameManager->endPowerUpEffect();
    }
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
    }
    return false;
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * VELOCITY;
    _timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        _type = BallType::FIREBALL;
        _timeWithPowerupEffect = duration;        
        return;
    }
    _type = BallType::BASIC;
    _timeWithPowerupEffect = 0.f;    
}

void Ball::setMultiBall(float duration) {
    if (duration)
    {
        _type = BallType::MULTIBALL;
        _timeWithPowerupEffect = duration;
        return;
    }
    _type = BallType::BASIC;
    _timeWithPowerupEffect = 0.f;
}

void Ball::clearType()
{
    _type = BallType::BASIC;
    _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
}
