#pragma once
#include <SFML/Graphics.hpp>

class Physics
{
public:
	Physics(sf::Vector2i scPosition, sf::Vector2i moonPosition);
	~Physics();

private:
	int gValue = 9.80665; // gravitational acceleration

};

