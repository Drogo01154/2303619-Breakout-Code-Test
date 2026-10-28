#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);

    _gameDimensions = _window->getSize();

}

GameManager::~GameManager()
{
    //Cleanup Memory 
    for (Ball* ball : _balls) {
        delete ball;
    }
    _balls.clear();
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window, this);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    createBall(400.0f);
    _powerupManager = new PowerupManager(this, _window, _paddle, &_balls);
    _ui = new UI(_window, _lives, this);

    _peviousMousePosition = sf::Mouse::getPosition();

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        return;
    }
    else if (_balls.size() == 0) {
        createBall(400.0f);
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }


    // move paddle

    sf::Vector2i currentMousePos = sf::Mouse::getPosition(*_window);

    // if mouse position changed set paddles x position to that of mouse
    if (currentMousePos != _peviousMousePosition) {
        //store mouse position as changed
        _peviousMousePosition = currentMousePos;
        //normalise x mouse position to between 0 and 1
        float normalisedX = (float)currentMousePos.x / (float)_window->getSize().x;
        //set paddles relative position
        _paddle->setHorizontalPosition(normalisedX);
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);
    }
    

    // update everything 
    _paddle->update(dt);
    for (auto it = _balls.begin(); it != _balls.end(); ) {
        if ((*it)->update(dt)) {
            delete *it;
            it = _balls.erase(it);
        } else {
            ++it;
        }
    }
    if (_balls.size() <= 0) {
        loseLife();
    }
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
   _lives--;
   _ui->lifeLost(_lives);
    // TODO screen shake.
}

void GameManager::render()
{
    _paddle->render();
    for (Ball* ball : _balls) {
        ball->render();
    }
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::createBall(float velocity, sf::Vector2f position, sf::Vector2f direction)
{
    _balls.push_back(new Ball(_window, velocity, position, direction, this));
}

void GameManager::endPowerUpEffect()
{
    _powerupManager->stopCurrentPowerUp();
    for (Ball* ball : _balls) {
        ball->clearType();
    }
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
sf::Vector2u GameManager::getGameDimensions() const { return _gameDimensions; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
