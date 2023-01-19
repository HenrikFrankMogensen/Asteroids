#include "Player.h"

Player::Player()
{
	playerVariables.x = 400.0f;
	playerVariables.y = 300.0f;
	playerVariables.dx = 0.0f;
	playerVariables.dy = 0.0f;
	playerVariables.angle = 0.0f;
	
	vecModelShip = { { 0.0f, -5.5 },{ -2.0f, 2.0f },{ 2.0f, 2.0f },{ -1.5f, 1.1f},{ 1.5f, 1.1f},{ -1.0f, 1.1f},{ 0.0f, 2.5f},{ 1.0f, 1.1f} };
}

void Player::startGame(sf::RenderWindow& window, bool& gameOn) {
	sf::Font font;
	
	if (!font.loadFromFile("bahnschrift.ttf"))
		std::cout << "ERROR" << std::endl;
	if (gameOn == false && gameOverScreen == true) {
		sf::Text text3;
		text3.setFont(font);
		text3.setCharacterSize(24);
		text3.setPosition(sf::Vector2f(330.0f, 250.0f));
		text3.setString(" GAME OVER!\nPress Return!");
		window.draw(text3);
		heatbeetHastighed = 1.0f;
		secondGameForward = true;
		drawNScoreAndDoc(window, gameOn);
	}
	if (gameOn == false && gameOverScreen == false) {
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(24);
		text.setPosition(sf::Vector2f(300.0f, 260.0f));
		text.setString("Press Return Key");

		sf::Text text2;
		text2.setFont(font);
		text2.setCharacterSize(24);
		text2.setPosition(sf::Vector2f(30.0f, 10.0f));

		std::string s = std::to_string(nScore);
		text2.setString(s);
		window.draw(text);
		window.draw(text2);
		drawNScoreAndDoc(window, gameOn);
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		gameOn = true;
		nScore = 0;
	}
}

void Player::drawNScoreAndDoc(sf::RenderWindow& window, bool& gameOn) {
	sf::Font font;
	if (!font.loadFromFile("bahnschrift.ttf"))
		std::cout << "ERROR" << std::endl;

	sf::Text text2;
	text2.setFont(font);
	text2.setCharacterSize(24);
	text2.setPosition(sf::Vector2f(30.0f, 10.0f));

	std::string s = std::to_string(nScore);
	text2.setString(s);
	window.draw(text2);
	bool dontShowShips = gameOn == false && gameOverScreen == true;
	if (!dontShowShips) {
		drawShipsInDoc(window);
	}
}

void Player::checkPlayerInput(bool gameOn, Sound &sound)
{
	bool upkeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	if (gameOn == true && pause == false) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			playerVariables.angle -= 0.07f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerVariables.angle += 0.07f;
		}

		bool upkeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		if (upkeyPressed) {
			// ACCELERATION changes VELOCITY (with respect to time)
			playerVariables.dx += sin(playerVariables.angle) * 0.03f;
			playerVariables.dy += -cos(playerVariables.angle) * 0.03f;
			if (!thrustSoundPlay) {
				sound.thrust.play();
				thrustSoundPlay = true;
			}
		}
	}
	if (!upkeyPressed && thrustSoundPlay || gameOn == false || pause == true) {
		sound.thrust.stop();
		thrustSoundPlay = false;
	}

	heatbeetHastighed = heatbeetHastighed * 1.0005f;
	if (gameOn == true) {
		if (heatbeetHastighed >= 2.4f) heatbeetHastighed = 2.4f;
		heatbeetCounter = heatbeetCounter + heatbeetHastighed;
		//std::cout << heatbeetCounter << std::endl;
		if (heatbeetCounter >= 100.0f) {
			if (beat1Actuel) {
				heatbeetCounter = 0.0f;
				sound.beat1.play();
				beat1Actuel = false;
			}
			else {
				heatbeetCounter = 0.0f;
				sound.beat2.play();
				beat1Actuel = true;
			}


			//Sleep(200);
		}
	}
	draw.wrapCoordinates(playerVariables.x, playerVariables.y, playerVariables.x, playerVariables.y);
	// ACCELERATION changes VELOCITY (with respect to time)
	playerVariables.x += playerVariables.dx;
	playerVariables.y += playerVariables.dy;
}

void Player::drawShip(sf::RenderWindow& window, Sound &sound) {
	float mx[8];
	float my[8];
	int mCounter = 0;
	float x = 4.f; // Scale factor of the ship
	/*
	if (bDead) {
		for (int i = 0; i < 8; i++) {
			vecModelShip[0].first += 1.0f;
		}
	}
	else {
		for (auto data : vecModelShip) {
			mx[mCounter] = data.first * x;
			my[mCounter] = data.second * x;
			mCounter += 1;
		}
	}*/
	for (auto data : vecModelShip) {
		mx[mCounter] = data.first * x;
		my[mCounter] = data.second * x;
		mCounter += 1;
	}
	/*
	for (int i = 0; i < 8; i++) {
		vecModelShip[0].first += 0.01f;
		vecModelShip[0].second += 0.01f;
	}*/
	//}
	//std::cout << "Data fra vecModelShip: " << vecModelShip << std::endl;
	// Setup points for the ship
	//float mx[8] = { 0.0f * x, -2.0f * x, +2.0f * x, -1.5f * x, 1.5f * x, -1.0f * x, 0.0f * x, 1.0f * x };
	//float my[8] = { -5.5f * x, +2.0f * x, +2.0f * x, 1.1f * x, 1.1f * x, 1.1f * x, 2.5f * x, 1.1f * x };
	//mx[0] = 1.0f;

	float sx[8], sy[8];

	// Rotate
	for (int i = 0; i < 8; i++) {
		sx[i] = mx[i] * cosf(playerVariables.angle) - my[i] * sinf(playerVariables.angle);
		sy[i] = mx[i] * sinf(playerVariables.angle) + my[i] * cosf(playerVariables.angle);
	}
	// Translate
	for (int i = 0; i < 8; i++) {
		sx[i] = sx[i] + playerVariables.x;
		sy[i] = sy[i] + playerVariables.y;
	}
	
	// Draw Closed Polygon
	/*
	for (int i = 0; i < 2; i++) {
		int j = (i + 2);
		draw.drawLine(window, sx[i % 3], sy[i % 3], sx[j % 3], sy[j % 3]);
	}*/
	if (bDead) {
		playerDestroyer(window, sx, sy, sound);
	}
	else {
		
		draw.drawLine(window, sx[0], sy[0], sx[1], sy[1]);
		draw.drawLine(window, sx[0], sy[0], sx[2], sy[2]);
		draw.drawLine(window, sx[3], sy[3], sx[4], sy[4]);
	}
	
	// Forklaring til ovenstående for løkke. Først er i = 0 og j bliver
	// derfor i + 1 = 1. Første linie der tegnes er derfor sx der er lig
	// med den nye linies x værdi der skal tegnes efter clear(). og sy er
	// y værdien begge begyndelsespunktet. sx og sy er index'et og linien
	// tegnes mellem sx[0],sy[0] og sx[1],sy[1] henholdsvis 0.0(x),-5.5(y)
	// og -2.0(x),2.0(y). Opsat i et cordinatsystem giver det følgende
	// linie.
	//  
	// 
	// 
	// 

	//draw.drawLine(window, sx[3 % 5], sy[3 % 5], sx[4 % 5], sy[4 % 5]);
	//std::cout << "3 % 5: " << 3 % 5 << std::endl;
	
	
	if (thrustSoundPlay) {
		trustDelayCounter = trustDelayCounter * 1.5f;
		
		if (trustDelayCounter >= trustDelay) {
			trustDelayCounter = 1;
			
			if (flameOn) {
				draw.drawLine(window, sx[5], sy[5], sx[6], sy[6]);
				draw.drawLine(window, sx[6], sy[6], sx[7], sy[7]);
				trustDelayCounter = trustDelayCounter * 1.5f;
				if (trustDelayCounter >= trustDelay) {
					flameOn = false;
				}
				else {
					flameOn = true;
				}
			}
			
		}
		
	}
	/*
	do {
		draw.drawLine(window, sx[5], sy[5], sx[6], sy[6]);
		draw.drawLine(window, sx[6], sy[6], sx[7], sy[7]);
		trustDelayCounter = trustDelayCounter * 1.5f;
	} while (trustDelayCounter <= trustDelay);*/
	
}

void Player::drawShipsInDoc(sf::RenderWindow& window) {

	float x = 2.5f; // Scale factor of the ship

	// Setup points for the ship
	float mx[8] = { 0.0f * x, -2.0f * x, +2.0f * x, -1.5f * x, 1.5f * x, -1.0f * x, 0.0f * x, 1.0f * x };
	float my[8] = { -5.5f * x, +2.0f * x, +2.0f * x, 1.1f * x, 1.1f * x, 1.1f * x, 2.5f * x, 1.1f * x };

	float sx[8], sy[8];
	
	// Rotate
	for (int i = 0; i < 8; i++) {
		sx[i] = mx[i] * cosf(0) - my[i] * sinf(0);
		sy[i] = mx[i] * sinf(0) + my[i] * cosf(0);
	}
	// Translate
	for (int i = 0; i < 8; i++) {
		sx[i] = sx[i] + 36.0f;
		sy[i] = sy[i] + 60.0f;
	}
	
	// Draw Closed Polygon
	int distanceBFALS = 0;
	for (int i = 0; i < numberOfShips; i++) {
		draw.drawLine(window, sx[0]+ distanceBFALS, sy[0], sx[1]+ distanceBFALS, sy[1]);
		draw.drawLine(window, sx[0]+ distanceBFALS, sy[0], sx[2]+ distanceBFALS, sy[2]);
		draw.drawLine(window, sx[3]+ distanceBFALS, sy[3], sx[4]+ distanceBFALS, sy[4]);
		distanceBFALS += 15;
	}
}

void Player::checkFireButton(sf::Event ev, bool gameOn, Sound &sound)
{
	if (gameOn == true) {
		vecBulletsPlayer.push_back({ playerVariables.x, playerVariables.y, 50.0f * sinf(playerVariables.angle), -50.0f * cosf(playerVariables.angle), 0, 0 });
		sound.sound1.play();
	}
}

void Player::drawBullets(sf::RenderWindow& window, Asteroids& asteroid, Player &player, Sound &sound)
{
	std::vector<sSpaceObject> newAsteroids;
	// Update and draw bullets
	for (auto& b : vecBulletsPlayer) {
		b.x += b.dx * 0.3f;
		b.y += b.dy * 0.3f;
		draw.drawPixel(window, b.x, b.y);

		// Check collision with asteroids
		for (auto& a : asteroid.vecAsteroids) {
			//asteroid.asteroidHit = asteroid.isPointInsidéCircle(a.x, a.y, a.nSize, b.x, b.y);
			if (asteroid.isPointInsidéCircle(a.x, a.y, a.nSize, b.x, b.y)) {
				
				// Asteroid hit
				b.x = -100;
				
				if (a.nSize > 20) {
					// Create two child asteroids
					
					float angle1 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
					float angle2 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
					newAsteroids.push_back({ a.x, a.y, 10.0f * sinf(angle1), 10.0f * cosf(angle1), a.nSize / 2, 0.0f });
					newAsteroids.push_back({ a.x, a.y, 10.0f * sinf(angle2), 10.0f * cosf(angle2), a.nSize / 2, 0.0f });
				}
				else {
					asteroid.dustPoints.push_back({ a.x, a.y, 0.5f, 0.5f, 100.0f });
					asteroid.dustPoints.push_back({ a.x + 2, a.y, -1.5f, 0.5f, 100.0f });
					asteroid.dustPoints.push_back({ a.x, a.y +3, 0.5f, -0.3f, 100.0f });
					asteroid.dustPoints.push_back({ a.x-2, a.y, -1.5f, -0.5f, 100.0f });
					asteroid.dustPoints.push_back({ a.x+1, a.y+2, 0.5f, 0.5f, 100.0f });
					asteroid.dustPoints.push_back({ a.x + 2, a.y-3, -1.5f, 0.5f, 100.0f });
				}
				
				a.x = -100;
				nScore += 100;
				drawScore();
				sound.sound2.play();
			}
		}
	}
	// Append new asteroids to existing vector
	for (auto a : newAsteroids) {
		asteroid.vecAsteroids.push_back(a);
	}
}

void Player::bulletFromPlayerHitSaucer(Saucer &saucer, Asteroids& asteroid, Sound &sound) {

	for (auto& a : vecBulletsPlayer) {
		if (sqrt((saucer.saucerVariables.x - a.x) * (saucer.saucerVariables.x - a.x) + (saucer.saucerVariables.y - a.y) * (saucer.saucerVariables.y - a.y)) < 30) {
			
			// Destroy saucer
			sound.sound2.play();
			saucer.saucerOn = false;
			saucer.hit = true;
			a.x = -100;
		}
		removeBulletsOutOffScreen(asteroid);
	}
}

void Player::removeBulletsOutOffScreen(Asteroids& asteroid)
{
	if (vecBulletsPlayer.size() > 0) {
		auto i = remove_if(vecBulletsPlayer.begin(), vecBulletsPlayer.end(), [&](sSpaceObject o) {return (o.x < 1 || o.y < 1 || o.x >= 799 || o.y >= 599);});
		if (i != vecBulletsPlayer.end())
			vecBulletsPlayer.erase(i);
	}

	if (asteroid.vecAsteroids.size() > 0) {
		
		auto i = remove_if(asteroid.vecAsteroids.begin(), asteroid.vecAsteroids.end(), [&](sSpaceObject o) {return (o.x < 0); });
		if (i != asteroid.vecAsteroids.end()) {
			asteroid.vecAsteroids.erase(i);
		}
	}
}

void Player::resetGameIfbDead(Asteroids& asteroid, sf::RenderWindow& window, bool& gameOn) {
	if (pause == false && bDead == true) {
		resetGame(asteroid, window, gameOn);
	}
	
}

void Player::collisionPlayerAsteroids(Asteroids& asteroid, sf::RenderWindow& window, bool& gameOn) {
	for (auto& a : asteroid.vecAsteroids) {
		if (asteroid.isPointInsidéCircle(a.x, a.y, a.nSize, playerVariables.x, playerVariables.y)) {
			bDead = true; // Uh oh...
			pause = true;
		}
	}
	
	if (bDead) {
		//playerDestroyer(window, sx, sy);
		//resetGame(asteroid, window, gameOn);
	}
}

void Player::resetGame(Asteroids& asteroid, sf::RenderWindow& window, bool& gameOn)
{
	vecBulletsPlayer.clear();
	if (secondGameForward) {
		asteroid.vecAsteroids.clear();
		asteroid.vecAsteroids.push_back({ 20.0f, 200.0f, 8.0f, -6.0f, (int)100, 0.0f });
		asteroid.vecAsteroids.push_back({ 100.0f, 200.0f, -5.0f, 3.0f, (int)100, 0.0f });
	}
	playerVariables.x = 400.0f;
	playerVariables.y = 300.0f;
	playerVariables.dx = 0.0f;
	playerVariables.dy = 0.0f;
	playerVariables.angle = 0.0f;

	bDead = false;
	playerHitTickSound = true;
	counterPlayerDestroyed = 0.0f;
	numberOfShips -= 1;
	if (numberOfShips == -1) {
		std::cout << "Game over" << std::endl;
		numberOfShips = 3;
		gameOn = false;
		gameOverScreen = true;
	}
	
	startGame(window, gameOn);
	
}

void Player::drawScore() {
	std::cout << "Scroe is: " << nScore << std::endl;
}


void Player::checkForNoMoreAsteroids(Asteroids& asteroid) {
	if (asteroid.vecAsteroids.empty()) {
		//std::cout << "Was here" << std::endl;
		nScore += 1000;
		drawScore();
	asteroid.vecAsteroids.push_back({ 30.0f * sinf(playerVariables.angle - 3.14159 / 2.0f),
									30.0f * cosf(playerVariables.angle - 3.14159f / 2.0f),
									10.0f * sinf(playerVariables.angle),
									10.0f * cosf(playerVariables.angle),
									(int)100, 0.0f });

	asteroid.vecAsteroids.push_back({ 30.0f * sinf(playerVariables.angle + 3.14159 / 2.0f),
									30.0f * cosf(playerVariables.angle + 3.14159f / 2.0f),
									10.0f * sinf(-playerVariables.angle),
									10.0f * cosf(-playerVariables.angle),
									(int)100, 0.0f });
	}
}

void Player::playerDestroyer(sf::RenderWindow &window, float sx[], float sy[], Sound &sound)
{
	if (playerHitTickSound) {
		sound.sound2.play();
		playerHitTickSound = false;
	}
	counterPlayerDestroyed += 0.1f;
	draw.drawLine(window, sx[0] - counterPlayerDestroyed, sy[0] - counterPlayerDestroyed, sx[1] - counterPlayerDestroyed, sy[1] - counterPlayerDestroyed);
	draw.drawLine(window, sx[0] + counterPlayerDestroyed, sy[0] + counterPlayerDestroyed, sx[2] + counterPlayerDestroyed, sy[2] + counterPlayerDestroyed);
	draw.drawLine(window, sx[3], sy[3] - counterPlayerDestroyed, sx[4], sy[4] - counterPlayerDestroyed);
}

void Player::checkForExtraShip(Sound &sound) {
	
	if (extraShip1000Finish == false && nScore >= 1000) {
		numberOfShips += 1;
		nScore += 200;
		sound.extraShip.play();
		delayExtraSSound = 100;
		extraSoundOn = true;
		extraShip1000Finish = true;
	}
	if (extraShip4000Finish == false && nScore >= 4000) {
		numberOfShips += 1;
		nScore += 200;
		sound.extraShip.play();
		delayExtraSSound = 100;
		extraSoundOn = true;
		extraShip4000Finish = true;
	}
	if (extraShip8000Finish == false && nScore >= 8000) {
		numberOfShips += 1;
		nScore += 200;
		sound.extraShip.play();
		delayExtraSSound = 100;
		extraSoundOn = true;
		extraShip8000Finish = true;
	}
	if (extraShip12000Finish == false && nScore >= 12000) {
		numberOfShips += 1;
		nScore += 200;
		sound.extraShip.play();
		delayExtraSSound = 100;
		extraSoundOn = true;
		extraShip12000Finish = true;
	}
	
	if (extraSoundOn) {
		delayExtraSSound -= 1;
	}
	if (delayExtraSSound < 0) {
		sound.extraShip.stop();
		extraSoundOn = false;
	}
}


