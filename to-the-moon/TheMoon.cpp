#include "stdafx.h"
#include "TheMoon.h"
#include "Animation.h"


TheMoon::TheMoon(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = false;
	angle = 0.0f;
	angleStepsize = 0.1f;

	body.setSize(sf::Vector2f(60.0f, 85.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(-200.0f, -200.0f);
	body.setTexture(texture);


}

TheMoon::~TheMoon()
{
}

void TheMoon::Update(float deltaTime, float radiusEMOrbit) {
	sf::Vector2f movement(0.0f, 0.0f);

	angleStepsize = deltaTime;
	movement.x = radiusEMOrbit * cos(angle);
	movement.y = radiusEMOrbit * sin(angle);

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);

	angle += angleStepsize;
}

void TheMoon::Draw(sf::RenderWindow& window) {
	window.draw(body);
}
