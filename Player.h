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
#include "Sound.h"
#include "Saucer.h"
#include "Asteroids.h"

class Asteroids;
class Saucer; // forward declaration. Is used when 2 header files include each
// other. In this case Player and Saucer. And now I have free hands to code.
// class Saucer; is only necessarry when Saucer identifier is used as in line 56

class Player {
	//Asteroids asteroid;
	Draw draw;
	std::vector<std::pair<float, float>> vecModelShip;

	bool thrustSoundPlay = false;
	bool beat1Actuel = true;
	bool flameOn = true;
	bool saucerOnScreenSoundOn = true;
	bool gameOverScreen = false;
	
	bool secondGameForward = false;
	bool playerHitSaucer = false;
	bool playerHitTickSound = true;
	bool extraSoundOn = false;
	bool extraShip1000Finish = false;
	bool extraShip4000Finish = false;
	bool extraShip8000Finish = false;
	bool extraShip12000Finish = false;
	
	float trustDelay = 100.0f;
	float trustDelayCounter = 100.0f;
	float heatbeetHastighed = 1.0f;
	float heatbeetCounter = 0.0f;
	
	int numberOfShips = 3;
	int delayExtraSSound = 400;
	int numberOfExtraShips = 0;
	int delayDust = 100;
	
public:
	//bool playerCollideWithAsteroid = false;
	float counterPlayerDestroyed = 0.0f;
	int nScore = 0;
	std::vector<sSpaceObject> vecBulletsPlayer;
	sSpaceObject playerVariables;
	bool bDead = false;
	Player();
	bool pause = false;
	int gameOverDelay = 200;
	//bool saucerOn = false;
	//float pauseBeforeSaucer = 1000.0f;
	//Functions
	//void initVecModelShip(Saucer saucer);
	void drawNScoreAndDoc(sf::RenderWindow& window, bool& gameOn);
	void startGame(sf::RenderWindow& window, bool& gameOn);
	void drawShipsInDoc(sf::RenderWindow& window);
	void checkPlayerInput(bool gameOn, Sound &sound);
	void drawShip(sf::RenderWindow& window, Sound &sound);
	void checkFireButton(sf::Event ev, bool gameOn, Sound &sound);
	void drawBullets(sf::RenderWindow& window, Asteroids& asteroid, Player &player, Sound &sound);
	void bulletFromPlayerHitSaucer(Saucer &saucer, Asteroids &asteroid, Sound &sound);
	void removeBulletsOutOffScreen(Asteroids& asteroid);
	void resetGameIfbDead(Asteroids& asteroid, sf::RenderWindow& window, bool& gameOn);
	void collisionPlayerAsteroids(Asteroids& asteroid, sf::RenderWindow& window, bool& gameOn);
	void resetGame(Asteroids& asteroid, sf::RenderWindow& window, bool& gameOn);
	void drawScore();
	void checkForNoMoreAsteroids(Asteroids& asteroid);
	void playerDestroyer(sf::RenderWindow& window, float sx[], float sy[], Sound &sound);
	void checkForExtraShip(Sound &sound);
	// Der kom en fejl efter indførelse af den ovenstående function. Syntax
	// fejl: identifier "Asteroids". Declarereret i Game.h. Løst!
	//void saucerShut(sf::RenderWindow& window, float x1, float y1, float x2, float y2); 
		
};
