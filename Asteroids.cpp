#include "Asteroids.h"


Asteroids::Asteroids() {
	vecAsteroids.push_back({ 20.0f, 200.0f, 8.0f, -6.0f, (int)100, 0.0f });

	int verts = 20;
	for (int i = 0; i < verts; i++) {
		float radius = (float)rand() / (float)RAND_MAX * 0.4f + 0.8f;
		float a = ((float)i / (float)verts) * 6.28318f;
		vecModelAsteroid.push_back(std::make_pair(radius * sinf(a), radius * cosf(a)));
	}
}

void Asteroids::drawAsteroids(sf::RenderWindow& window)
{
	for (auto& a : vecAsteroids) {
		a.x += a.dx * 0.2f;
		a.y += a.dy * 0.2f;
		a.angle += 0.01f;
        draw.wrapCoordinates(a.x, a.y, a.x, a.y);

		draw.drawWireFrameModel(window, vecModelAsteroid, a.x, a.y, a.angle, a.nSize);
	}
}

bool Asteroids::isPointInsidéCircle(float cx, float cy, float radius, float x, float y)
{
	return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
}

void Asteroids::checkForNoMoreAsteroids(Player &player) {
	if (vecAsteroids.empty()) {
		//std::cout << "Was here" << std::endl;
		player.nScore += 1000;
		player.drawScore();
		vecAsteroids.push_back({ 30.0f * sinf(player.playerVariables.angle - 3.14159 / 2.0f),
										30.0f * cosf(player.playerVariables.angle - 3.14159f / 2.0f),
										10.0f * sinf(player.playerVariables.angle),
										10.0f * cosf(player.playerVariables.angle),
										(int)100, 0.0f });

		vecAsteroids.push_back({ 30.0f * sinf(player.playerVariables.angle + 3.14159 / 2.0f),
										30.0f * cosf(player.playerVariables.angle + 3.14159f / 2.0f),
										10.0f * sinf(-player.playerVariables.angle),
										10.0f * cosf(-player.playerVariables.angle),
										(int)100, 0.0f });
	}
}

void Asteroids::drawDustPoints(sf::RenderWindow &window)
{
	for (auto& a : dustPoints) {
		a.x += a.dx * 0.5f;
		a.y += a.dy * 0.5f;
		draw.wrapCoordinates(a.x, a.y, a.x, a.y);
		a.delay -= 2.5f;
		if (a.delay > 0) {
			draw.drawPixel(window, a.x, a.y);
		}
		else {
			dustPoints.clear();
		}
	}
}

