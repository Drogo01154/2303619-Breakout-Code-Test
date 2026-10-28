#include "PowerupManager.h"
#include "GameManager.h"
#include <ctime>


PowerupManager::PowerupManager(GameManager* gameManager, sf::RenderWindow* window, Paddle* paddle, std::list<Ball*>* balls)
    : _gameManager(gameManager), _window(window), _paddle(paddle), _balls(balls), _rng(std::random_device{}())
{
    srand(static_cast<unsigned>(time(nullptr))); // Seed randomness based on time so results are random to user. 
}

PowerupManager::~PowerupManager()
{
    for (auto powerup : _powerups)
    {
        delete powerup;
    }
    _powerups.clear();
}

void PowerupManager::update(float dt)
{
    // tick down powerup effect time. Reset if elapsed.
    if (_powerupInEffect)
    {
        _powerupInEffect->second -= dt;
        if (_powerupInEffect->second <= 0)
        {
            _powerupInEffect.reset();
        }
    }


    for (auto it = _powerups.begin(); it != _powerups.end(); )
    {
        checkCollision();
        
        // Delete powerups queued for removal
        (*it)->update(dt);
        if (!(*it)->isAlive())
        {
            delete* it;
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::render()
{
    for (auto& powerup : _powerups)
    {
        powerup->render();
    }
}

void PowerupManager::spawnPowerup()
{

    sf::Vector2u gameSize = _gameManager->getGameDimensions();

    std::uniform_real_distribution<float> xDist(
        gameSize.x * 0.05f,
        gameSize.x * 0.95f
    );

    float spawnX = xDist(_rng);

    switch (rand() % 6)
    {
    case 0:
        _powerups.push_back(new PowerupBigPaddle(_gameManager, _window, _paddle, _balls, spawnX));
        break;
    case 1:
        _powerups.push_back(new PowerupSlowBall(_gameManager, _window, _paddle, _balls, spawnX));
        break;
    case 2:
        _powerups.push_back(new PowerupFastBall(_gameManager, _window, _paddle, _balls, spawnX));
        break;
    case 3:
        _powerups.push_back(new PowerupSmallPaddle(_gameManager, _window, _paddle, _balls, spawnX));
        break;
    case 4:
        _powerups.push_back(new PowerupFireBall(_gameManager, _window, _paddle, _balls, spawnX));
        break;
    case 5:
        _powerups.push_back(new PowerupMultiBall(_gameManager, _window, _paddle, _balls, spawnX));
    }

}

void PowerupManager::checkCollision()
{
    for (auto& powerup : _powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            _powerupInEffect = powerup->applyEffect();
            powerup->setAlive(false);
        }
    }
}

void PowerupManager::stopCurrentPowerUp()
{
    _powerupInEffect.reset();
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerups.size();
}

std::pair<POWERUPS, float> PowerupManager::getPowerupInEffect()
{
    if (!_powerupInEffect) return { none, 0.f };
    return *_powerupInEffect;
}
