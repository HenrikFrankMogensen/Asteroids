#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//#include <vector>
#include "sSpaceObject.h"



class Draw {

public:
	// Functions
	void drawWireFrameModel(sf::RenderWindow& window, const std::vector<std::pair<float, float>>& vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f);
	void wrapCoordinates(float ix, float iy, float& ox, float& oy);
	void drawPixel(sf::RenderWindow& window, float x, float y);
	void drawPixel2(sf::RenderWindow& window, float x, float y);
	void drawLine(sf::RenderWindow& window, float p0x, float p0y, float p1x, float p1y);
	
};