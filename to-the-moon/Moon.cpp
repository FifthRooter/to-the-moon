#include "stdafx.h"
#include "Moon.h"
#include "Animation.h"


Moon::Moon(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = false;

	body.setSize(sf::Vector2f(60.0f, 85.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(-200.0f, -200.0f);
	body.setTexture(texture);


}

Moon::~Moon()
{
}

void Moon::Update(float deltaTime, float radiusEMOrbit) {
	sf::Vector2f movement(0.0f, 0.0f);

	angleStepsize = deltaTime;
	movement.x = radiusEMOrbit * cos(angle);
	movement.y = radiusEMOrbit * sin(angle);

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);

	angle += angleStepsize;
}

void Moon::Draw(sf::RenderWindow& window) {
	window.draw(body);
}
