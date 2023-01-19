#include "Game.h"

//Private functions
void Game::initVariables()
{
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
    //this->window(this->videoMode, "Game 1");
    this->window->setFramerateLimit(60);
}

//Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete window;
}

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

//Functions

void Game::pollEvents()
{
    //Event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            if (this->ev.key.code == sf::Keyboard::Space && !player.bDead)
                player.checkFireButton(ev, gameOn, sound);
            break;
        
            
        }
    }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    /*
        @return void
        - clear old frame
        - render objects
        - display frame in window

        Renders the game objects.
    */
    if (!gameOn) {
        this->window->clear();
        this->player.startGame(*window, gameOn);
        this->asteroid.drawAsteroids(*window);
        this->player.checkPlayerInput(gameOn, sound);
        this->saucer.drawSaucer(*window, sound, player, asteroid);
    }
    else {
        if (player.pause == false) {
            
            //Draw game objects
            this->window->clear();
            this->player.drawNScoreAndDoc(*window, gameOn);
            this->player.checkPlayerInput(gameOn, sound);
            this->player.drawBullets(*window, asteroid, player, sound);
            this->player.removeBulletsOutOffScreen(asteroid);
            this->saucer.removeBulletsOutOffScreen();
            this->player.collisionPlayerAsteroids(asteroid, *window, gameOn);
            this->asteroid.checkForNoMoreAsteroids(player);
            this->asteroid.drawAsteroids(*window);
            this->player.drawShip(*window, sound);
            this->saucer.drawSaucer(*window, sound, player, asteroid);
            this->player.resetGameIfbDead(asteroid, *window, gameOn);
            this->player.bulletFromPlayerHitSaucer(saucer, asteroid, sound);
            this->player.checkForExtraShip(sound);
            this->asteroid.drawDustPoints(*window);
        }
        else {
            this->window->clear();
            this->player.drawNScoreAndDoc(*window, gameOn);
            this->asteroid.drawAsteroids(*window);
            this->player.checkPlayerInput(gameOn, sound);
            this->saucer.drawSaucer(*window, sound, player, asteroid);
            if (player.counterPlayerDestroyed < 12.0f) {
                this->player.drawShip(*window, sound);
            }
            player.gameOverDelay -= 1;
            
            if (player.gameOverDelay < 0) {
                //std::cout << "saucerVariablesx >= 850.0f" << std::endl;
                player.pause = false;
                //saucer.saucerOn = false;
                player.gameOverDelay = 200;
            }
        }
    }

    this->window->display();
}