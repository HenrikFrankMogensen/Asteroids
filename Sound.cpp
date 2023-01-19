#include "Sound.h"

Sound::Sound()
{
	initSounds();
}

void Sound::initSounds()
{
    if (!buffer1.loadFromFile("fire.wav")) {
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
    if (!buffer7.loadFromFile("extraShip.wav")) {
        std::cout << "Fejl" << std::endl;
    }

    sound1.setBuffer(buffer1); // Fire
    sound2.setBuffer(buffer2); // Explosion
    beat1.setBuffer(buffer3); // Beat1
    beat2.setBuffer(buffer4);
    thrust.setBuffer(buffer5);
    saucerBigSound.setBuffer(buffer6);
    extraShip.setBuffer(buffer7);
    thrust.setLoop(true);
    saucerBigSound.setLoop(true);
    extraShip.setBuffer(buffer7);
    extraShip.setLoop(true);
}
