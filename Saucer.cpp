#include "Saucer.h"

Saucer::Saucer()
{
	saucerVariables.x = -50.0f;
	saucerVariables.y = 100.0f;
	saucerVariables.dx = 2.0f;
	saucerVariables.dy = 0.0f;
	saucerVariables.nSize = 4;
	saucerVariables.angle = 0.0f;
}

void Saucer::takeCareOfShutFromSaucer(Player &player, sf::RenderWindow& window, sSpaceObject &player1, Asteroids &asteroid) {
	if (saucerOn) {
		pauseToShut -= 0.05f;
	}

	if (pauseToShut < 0) {
		shutFromSaucer = true;
		pauseToShut = 10;
		float angleResult = 0.0f;
		angleResult = calculateAngleToTheShipFromSaucer(player.playerVariables);
		vecBulletSaucer.push_back({ saucerVariables.x, saucerVariables.y, 50.0f * cosf(angleResult), 50.0f * sinf(angleResult), 0, 0 });
	}
	if (shutFromSaucer && allowedToShut) {
		drawBullet(window, player1, player, asteroid);
	}
}

void Saucer::drawSaucer(sf::RenderWindow& window, Sound& sound, Player &player, Asteroids asteroid) {
	// Setup the points for the saucer
	/*
	if (saucerOnScreenSoundOn) {
		sound.saucerBigSound.play();
		saucerOnScreenSoundOn = false;
	}*/
	//std::cout << saucerOn << std::endl;
	//std::cout << saucerOn << std::endl;
	// Hvornår skal saucerOn være true. saucerOn skal være false fra 
	// starten af spillet og sættes til true når pauseBeforeSaucer er
	// under 0. Altså som nedenstående:

	pauseBeforeSaucer -= 1.0f;
	if (pauseBeforeSaucer < 0) {
		saucerOn = true;
		pauseBeforeSaucer = 1000.0f;
		saucerVariables.x = -50;
		if (saucerVariables.nSize == 4) {
			saucerVariables.nSize = 6;
		}
		else
		{
			saucerVariables.nSize = 4;
			saucerVariables.y = 450.0f;
		}
		
		// Attention: Selv om saucer forsvinder når den rammes skal saucer sættes 
		// til venstre x = -50 hvilket der ikke sker rettes.
		//                        ^
		// ~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~
	}
	// saucer.x bliver 850 når der er colite mellem asteroids og player, så
	// saucerOn er false på et forkert tidspunkt. Når der er colite, 
	// svær at finde den bug.
	if (saucerOn || hit) {
		saucerVariables.x += 2.0f;
		takeCareOfShutFromSaucer(player, window, player.playerVariables, asteroid);
		
		float x = saucerVariables.nSize;
			// x skal laves om til variablen nSize der er 6 fra starten
		float mx[10] = { -0.5f * x, 0.5f * x, 1.0f * x,   2.0f * x, 4.0f * x, 2.0f * x,-2.0f * x,-4.0f * x, -2.0f * x, -1.0f * x };
		float my[10] = { -1.5f * x,-1.5f * x,-0.75f * x,-0.75f * x, 0.0f * x, 1.0f * x, 1.0f * x, 0.0f * x, -0.75f * x, -0.75f * x };

		//float sx[10], sy[10];

		// Translate
		for (int i = 0; i < 10; i++) {
			mx[i] = mx[i] + saucerVariables.x;
			my[i] = my[i] + saucerVariables.y;
		}
		if (hit) {
			saucerDestroyer(window, mx, my);
		}
		else {
			for (int i = 0; i < 9; i++) {
				int j = (i + 1);
				drawLinesToSaucer(window, mx[i], my[i], mx[j], my[j]);
			}
			drawLinesToSaucer(window, mx[9], my[9], mx[0], my[0]);
			drawLinesToSaucer(window, mx[9], my[9], mx[2], my[2]);
			drawLinesToSaucer(window, mx[7], my[7], mx[4], my[4]);
		}
	}
	else {
		sound.saucerBigSound.stop();
		saucerOnScreenSoundOn = true;
		
	}
	if (!allowedToShut) {
		sound.saucerBigSound.stop();
	}

	// kommer ikke hertil da saucerOn bliver falsk se ovenfor. Ande gang
		// saucer fremkommer er den ikke på skærmen. Her er hit true og
		// nedenstående else kode kører ikke
	

	if (saucerVariables.x >= 850.0f) {
		saucerVariables.x = -50;
		saucerOn = false;
		pauseBeforeSaucer = 1000;
		allowedToShut = true;
	}

	if (saucerOnScreenSoundOn && saucerOn) {
		sound.saucerBigSound.play();
		saucerOnScreenSoundOn = false;
	}
	
}

void Saucer::drawLinesToSaucer(sf::RenderWindow& window, float p0x, float p0y, float p1x, float p1y) {

	float m = 0.0f;
	if (p1x != p0x) {
		m = (p1y - p0y) / (p1x - p0x);
	}
	if (p1x != p0x && std::abs(m) <= 1.0f) {
		if (p0x > p1x) {
			std::swap(p0x, p1x);
			std::swap(p0y, p1y);
		}

		const float b = p0y - m * p0x;

		for (int x = (int)p0x; x < (int)p1x + 1; x++) {
			const float y = m * (float)x + b;
			draw.drawPixel2(window, x, (int)y);
		}
	}
	else {
		if (p0y > p1y) {
			std::swap(p0x, p1x);
			std::swap(p0y, p1y);
		}
		const float w = (p1x - p0x) / (p1y - p0y);
		const float p = p0x - w * p0y;

		for (int y = (int)p0y; y < (int)p1y + 1; y++) {
			const float x = w * (float)y + p;
			draw.drawPixel2(window, (int)x, y);
		}
	}
}

void Saucer::drawBullet(sf::RenderWindow& window, sSpaceObject player, Player &player1, Asteroids &asteroid) {
	
	for (auto& b : vecBulletSaucer) {
		b.x += b.dx * 0.3f;
		b.y += b.dy * 0.3f;
		draw.drawPixel(window, b.x, b.y);
	}
	bulletFromSaucerHitPlayer(player1);
	
}

void Saucer::removeBulletsOutOffScreen() {
	if (vecBulletSaucer.size() > 0) {
		auto i = remove_if(vecBulletSaucer.begin(), vecBulletSaucer.end(), [&](sSpaceObject o) {return (o.x < 1 || o.y < 1 || o.x >= 799 || o.y >= 599);});
		if (i != vecBulletSaucer.end())
			vecBulletSaucer.erase(i);
	}
}

float Saucer::calculateAngleToTheShipFromSaucer(sSpaceObject player) {
	float angle = 0.0f;
	float angleRight = 0.0f;
	// angle = atanf(rise/run). rise = (player.y - saucer.y). Run = player.x - 
	// saucer.x
	if (saucerVariables.x > player.x) {
		angleRight = 3.1415f;
	}

	angle = atanf((player.y - saucerVariables.y) / (player.x - saucerVariables.x)) + angleRight;
	
	return angle;
}

void Saucer::bulletFromSaucerHitPlayer(Player &player) {
	for (auto& a : vecBulletSaucer) {
		if (sqrt((player.playerVariables.x - a.x) * (player.playerVariables.x - a.x) + (player.playerVariables.y - a.y) * (player.playerVariables.y - a.y)) < 8) {
			player.bDead = true;
			player.pause = true;
			a.x = -100;
		}
		removeBulletsOutOffScreen();
	}
}

void Saucer::saucerDestroyer(sf::RenderWindow &window, float mx[], float my[])
{
	allowedToShut = false;
	counterSaucerDestroyed += 0.1f;
	float c = counterSaucerDestroyed;
	
	drawLinesToSaucer(window, mx[0], my[0]-c, mx[1], my[1]-c);
	drawLinesToSaucer(window, mx[1]+c, my[1], mx[2]+c, my[2]);
	drawLinesToSaucer(window, mx[2], my[2]-c, mx[3], my[3]-c);
	drawLinesToSaucer(window, mx[3]-c, my[3]+c, mx[4]-c, my[4]+c);
	drawLinesToSaucer(window, mx[4], my[4]+c, mx[5], my[5]+c);
	drawLinesToSaucer(window, mx[5]-c, my[5]+c, mx[6]-c, my[6]+c);
	drawLinesToSaucer(window, mx[6]-c, my[6], mx[7]-c, my[7]);
	drawLinesToSaucer(window, mx[7]-c, my[7]+c, mx[8]-c, my[8]+c);
	drawLinesToSaucer(window, mx[8]+c, my[8], mx[9]+c, my[9]);
	drawLinesToSaucer(window, mx[9], my[9]-c, mx[0], my[0]-c);
	drawLinesToSaucer(window, mx[7]+c, my[7]-c, mx[4]+c, my[4]-c);
	if (counterSaucerDestroyed > 10.0f) {
		hit = false;
		counterSaucerDestroyed = 0.0f;
		saucerVariables.x = 855.0f;
		allowedToShut = false;
	}
	
}
