#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Asteroids.h"
#include "Player.h"
#include "Draw.h"
#include "sSpaceObject.h"
#include "Sound.h"
#include "Saucer.h"
/*
    Class that acts as the game engine.
    Wrapper class.
*/

class Game
{
private:
    //Variables
    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    Asteroids asteroid;
    Player player;
    Saucer saucer;
    Sound sound;
   
    //Private functions
    void initVariables();
    void initWindow();
    bool gameOn = false;

public:
    //Constructors / Destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool running() const;

    //Functions
    
    void pollEvents();
    void update();
    void render();
};


