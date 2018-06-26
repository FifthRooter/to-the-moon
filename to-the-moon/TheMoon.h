#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class TheMoon
{
public:
	TheMoon(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~TheMoon();

	void Update(float deltaTime, float radiusEMOrbit);
	void Draw(sf::RenderWindow& window);

	float currentXPos = body.getPosition().x;
	float currentYPos = body.getPosition().y;

	//sf::Vector2f GetPositionX() { return body.getPosition().x; }
	//sf::Vector2f GetPositionY() { return body.getPosition().y; }


private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	float angle;
	float angleStepsize;
};

