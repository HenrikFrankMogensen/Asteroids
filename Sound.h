#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include "sSpaceObject.h"
#include "Asteroids.h"
#include "Draw.h"


class Sound {
	

public:
    sf::SoundBuffer buffer1;
    sf::SoundBuffer buffer2;
    sf::SoundBuffer buffer3;
    sf::SoundBuffer buffer4;
    sf::SoundBuffer buffer5;
    sf::SoundBuffer buffer6;
    sf::SoundBuffer buffer7;

    sf::Sound sound1; // Fire
    sf::Sound sound2; // Explosion
    sf::Sound beat1; // Beat1
    sf::Sound beat2; // Beat2
    sf::Sound thrust;
    sf::Sound saucerBigSound;
    sf::Sound extraShip;

public:
    // Constructor
    Sound();
        
    void initSounds();
};

/*
        sf::SoundBuffer buffer;
        sf::SoundBuffer buffer2;
        sf::SoundBuffer buffer3;
        sf::SoundBuffer buffer4;
        sf::SoundBuffer buffer5;
        sf::SoundBuffer buffer6;
        if (!buffer.loadFromFile("fire.wav")) {
            std::cout << "Fejl" << std::endl;
        }
        if (!buffer2.loadFromFile("bangMedium.wav")) {
            std::cout << "Fejl" << std::endl;
        }
        if (!buffer3.loadFromFile("beat1.wav")) {
            std::cout << "Fejl" << std::endl;
        }
        if (!buffer4.loadFromFile("beat2.wav")) {
            std::cout << "Fejl" << std::endl;
        }
        if (!buffer5.loadFromFile("thrust.wav")) {
            std::cout << "Fejl" << std::endl;
        }
        if (!buffer6.loadFromFile("saucerBig.wav")) {
            std::cout << "Fejl" << std::endl;
        }
        sf::Sound sound; // Fire
        sf::Sound sound2; // Explosion
        sf::Sound beat1; // Beat1
        sf::Sound beat2; // Beat2
        sf::Sound thrust;
        sf::Sound saucerBigSound;
        sound.setBuffer(buffer); // Fire
        sound2.setBuffer(buffer2); // Explosion
        beat1.setBuffer(buffer3); // Beat1
        beat2.setBuffer(buffer4);
        thrust.setBuffer(buffer5);
        saucerBigSound.setBuffer(buffer6);

*/
