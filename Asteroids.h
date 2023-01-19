#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include "sSpaceObject.h"
#include "Draw.h"
#include "Player.h"
#include "AstDustPoints.h"

class Player;

class Asteroids {

	std::vector<std::pair<float, float>> vecModelAsteroid;
	
	Draw draw;

public:
	std::vector<sSpaceObject> vecAsteroids;
	std::vector<AstDustPoints> dustPoints;
	//bool asteroidHit = false;

	Asteroids();

	//Functions
	void drawAsteroids(sf::RenderWindow& window);
	bool isPointInsidéCircle(float cx, float cy, float radius, float x, float y);
	void checkForNoMoreAsteroids(Player &player);
	void drawDustPoints(sf::RenderWindow &window);
	
};