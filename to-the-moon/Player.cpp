#include "stdafx.h"
#include "Player.h"
#include "Animation.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(80.0f, 80.0f));
	body.setOrigin(body.getSize() / 2.0f);
	//body.setFillColor(sf::Color::Red);
	//body.setOrigin(50.0f, 50.0f);
	body.setPosition(70.0f, 120.0f);
	body.setTexture(texture);
}


Player::~Player()
{
}

void Player::Update(float deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);

	if (movement.x == 0.0f) {
		row = 0;
	}
	else {
		row = 1;

		if (movement.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	if (scFixedInOrbit) {
		updateOrbitCoordinates(deltaTime);
	}
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void Player::updateOrbitCoordinates(float deltaTime) {
	radiusESCOrbit = sqrtf(powf(70.0f, 2.0f) + powf(70, 2.0f));
	angleStep = deltaTime;

	/*if (angle > 2 * M_PI)
		angle = 0.00f;*/
}
