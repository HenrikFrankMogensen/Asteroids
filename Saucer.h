#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <string>

//#include "sSpaceObject.h"
//#include "Asteroids.h"
//#include "Draw.h"
//#include "Sound.h"
#include "Player.h"
#include "Asteroids.h"
class Sound;
class Player; // forward declaration. It was an syntax fault because Player was
// not identified by the Saucer class beginning at line 39.
class Asteroids;
class Saucer {

	Draw draw;

	std::vector<sSpaceObject> vecBulletSaucer;
	float pauseToShut = 10.0f;
	float pauseBeforeSaucer = 1000.0f;
	bool saucerOnScreenSoundOn = true;
	bool shutFromSaucer = false;
	float counterSaucerDestroyed = 0.0f;
	bool allowedToShut = true;

public:
	
	bool hit = false;
	bool saucerOn = false;
	sSpaceObject saucerVariables;

	Saucer();

	void takeCareOfShutFromSaucer(Player &player, sf::RenderWindow& window, sSpaceObject& player1, Asteroids& asteroid);
	void drawSaucer(sf::RenderWindow& window, Sound& sound, Player& player, Asteroids asteroid);
	void drawLinesToSaucer(sf::RenderWindow& window, float p0x, float p0y, float p1x, float p1y);
	void drawBullet(sf::RenderWindow& window, sSpaceObject player, Player& player1, Asteroids& asteroid);
	void removeBulletsOutOffScreen();
	float calculateAngleToTheShipFromSaucer(sSpaceObject player);
	void bulletFromSaucerHitPlayer(Player& player);
	void saucerDestroyer(sf::RenderWindow &window, float mx[], float my[]);
};