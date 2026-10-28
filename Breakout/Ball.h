#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration

enum BallType {
    BASIC,
    FIREBALL,
    MULTIBALL
};


class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, sf::Vector2f position, sf::Vector2f direction, GameManager* gameManager);
    ~Ball();
    bool update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setMultiBall(float duration);
    void clearType();

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    float _timeWithPowerupEffect;
    BallType _type;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

