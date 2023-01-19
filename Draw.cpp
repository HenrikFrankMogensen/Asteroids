#include "Draw.h"



void Draw::wrapCoordinates(float ix, float iy, float& ox, float& oy) {
    ox = ix;
    oy = iy;
    if (ix < 0.0f) ox = ix + 800.0f;
    if (ix >= 800.0f) ox = ix - 800.0f;
    if (iy < 0.0f) oy = iy + 600.0f;
    if (iy >= 600.0f) oy = iy - 600.0f;
}

void Draw::drawPixel2(sf::RenderWindow& window, float x, float y) {
    sf::RectangleShape rect;
    sf::Vector2f position(x, y);
    rect.setPosition(position);
    rect.setSize(sf::Vector2f(1, 1));
    window.draw(rect);
}

void Draw::drawPixel(sf::RenderWindow& window, float x, float y) {
    float fx, fy;
    wrapCoordinates(x, y, fx, fy);
    drawPixel2(window, fx, fy);
}

void Draw::drawLine(sf::RenderWindow& window, float p0x, float p0y, float p1x, float p1y) {

	float m = 0.0f; // Rice or - rice is slope of the line. m = slope
	if (p1x != p0x) { // Be sure we not divide by zero
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
			drawPixel(window, (float)x, y);
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
			drawPixel(window, x, (float)y);
		}
	}
}

void Draw::drawWireFrameModel(sf::RenderWindow& window, const std::vector<std::pair<float, float>>& vecModelCoordinates, float x, float y, float r, float s) {
    // pair.first = x coordinate
    // pair.second = y coordinate

    // Create translated model vector of coordinate pairs
    std::vector<std::pair<float, float>> vecTransformedCoordinates;
    int verts = vecModelCoordinates.size();
    vecTransformedCoordinates.resize(verts);

    // Rotate
    for (int i = 0; i < verts; i++) {
        vecTransformedCoordinates[i].first = vecModelCoordinates[i].first * cosf(r) - vecModelCoordinates[i].second * sinf(r);
        vecTransformedCoordinates[i].second = vecModelCoordinates[i].first * sinf(r) + vecModelCoordinates[i].second * cosf(r);
    }

    // Scale
    for (int i = 0; i < verts; i++) {
        vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * s;
        vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * s;
    }

    // Translate
    for (int i = 0; i < verts; i++) {
        vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
        vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
    }

    // Draw Closed Polygon
    for (int i = 0; i < verts + 1; i++) {
        int j = (i + 1);
        drawLine(window, vecTransformedCoordinates[i % verts].first, vecTransformedCoordinates[i % verts].second,
            vecTransformedCoordinates[j % verts].first, vecTransformedCoordinates[j % verts].second);
    }
}

