// to-the-moon.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Moon.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>


static const float VIEW_HEIGHT = 768.0f;
double angle = 2 * M_PI * 4 / 8.0;
float angleStepsize = 0.1f;
float x = 0.0f;
float y = 0.0f;
float radiusEMOrbit = 0.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1024.0f, VIEW_HEIGHT), "Serious Game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Vector2f moonPosition(-200.0f, 0.0f);
	sf::Vector2f moonPreviousPosition(-200.0f, 0.0f);
	sf::Vector2f deltaMoonPosition(0.0f, 0.0f);

	sf::RectangleShape moon(sf::Vector2f(60.0f, 85.0f));
	sf::RectangleShape earth(sf::Vector2f(60.0f, 85.0f));

	moon.setFillColor(sf::Color::White);
	earth.setFillColor(sf::Color::White);

	earth.setOrigin(0.5f, 0.5f);
	moon.setOrigin(0.5f, 0.5f);

	moon.setPosition(-200.0f, 0.0f);
	earth.setPosition(0, 0);

	sf::Texture moonTexture;
	sf::Texture earthTexture;
	sf::Texture playerTexture;

	if (!playerTexture.loadFromFile("spaceship.png") | !playerTexture.loadFromFile("moon.png") | !playerTexture.loadFromFile("earth.png")) {
	return EXIT_FAILURE;
	}

	moonTexture.loadFromFile("moon.png");
	earthTexture.loadFromFile("earth.png");
	playerTexture.loadFromFile("spaceship.png");

	moon.setTexture(&moonTexture);
	earth.setTexture(&earthTexture);

	Player player(&playerTexture, sf::Vector2u(1, 1), 0.3f, 100.0f);
	//Moon moon(&moonTexture, sf::Vector2u(1, 1), 0.3f, 100.0f);

	int counter = 0;
	float deltaTime = 0.0f;
	sf::Clock clock;


	//player.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 8, textureSize.x, textureSize.y));

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();

		sf::Event evnt;

		while (window.pollEvent(evnt)) {

			switch (evnt.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
		window.close();
		}


		radiusEMOrbit = sqrtf(powf(200.0f, 2.0f) + powf(200.0f, 2.0f));
		std::cout << "radius: " << radiusEMOrbit << '\n';

		angleStepsize = deltaTime;
		std::cout << "Angle: " << angle << '\n';
		std::cout << "X pos: " << x << "Y pos: " << y << '\n';
		std::cout << "cos(angle): "<< moonPosition.x << '\n';
		std::cout << "sin(angle): " << moonPosition.y << '\n';
		std::cout << "-----------------------------------------" << '\n';

		if (angle > 2 * M_PI)
			angle = 0.0f;


		if (counter > 1) {
			counter = 0;

			moonPreviousPosition.x = moonPosition.x;
			moonPreviousPosition.y = moonPosition.y;

			moonPosition.x = radiusEMOrbit * cos(angle);
			moonPosition.y = - radiusEMOrbit * sin(angle);

			deltaMoonPosition.x = moonPosition.x - moonPreviousPosition.x;
			deltaMoonPosition.y = moonPosition.y - moonPreviousPosition.y;

			moon.move(deltaMoonPosition);
			angle += angleStepsize;

		}

		
		counter++;


		player.Update(deltaTime);
		//moon.Update(deltaTime, radiusEMOrbit);

		window.clear(sf::Color::Black);
		window.setView(view);
		player.Draw(window);
		//moon.Draw(window);
		window.draw(moon);
		window.draw(earth);
		window.display();  
	}
	return 0;
}

