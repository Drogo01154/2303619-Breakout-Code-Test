#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <random>
#include "PowerupBase.h"
#include "PowerupBigPaddle.h"
#include "PowerupSmallPaddle.h"
#include "PowerupSlowBall.h"
#include "PowerupFastBall.h"
#include "PowerupFireBall.h"
#include "PowerupMultiBall.h"
#include "Paddle.h"
#include "Ball.h"
#include <list>


class PowerupManager
{
public:
    PowerupManager(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls);
    ~PowerupManager();

    void update(float dt);
    void render();
    void spawnPowerup(); // Method to spawn a power-up
    void checkCollision(); // Check collision with paddle
    void stopCurrentPowerUp(); // Stops active powerup
    int getPowerupsSpawned();
    std::pair<POWERUPS, float> getPowerupInEffect();

private:
    GameManager* _gameManager;
    sf::RenderWindow* _window;
    Paddle* _paddle;
    std::list<Ball*>* _balls;
    std::vector<PowerupBase*> _powerups;            // used to manage deletion.
    std::optional<std::pair<POWERUPS, float>> _powerupInEffect;    // used for gameManager to get reference.
    std::mt19937 _rng; // mersenne twister
};
