// to-the-moon.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "TheMoon.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Dashboard.h"
#include <thread>


using namespace std;
using namespace sf;


static const float VIEW_HEIGHT = 980.0f;
static const float VIEW_WIDTH = 1400.0f;
double angle = 2 * M_PI * 4 / 8.0;
float angleStepsize = 0.1f;
float x = 0.0f;
float y = 0.0f;
float radiusEMOrbit = 0.0f;
bool isMousePressed = false;

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

//void dashboardThread(sf::RenderWindow& window) {
//	Dashboard dashboard;
//	sf::Vector2i mousePosition;
//
//	while (window.isOpen()) {
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//			mousePosition = sf::Mouse::getPosition();
//			dashboard.Draw(mousePosition);
//
//		}
//	}
//}

int main() {
	sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Serious Game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Vector2f moonPosition(-200.0f, 0.0f);
	sf::Vector2f moonPreviousPosition(-200.0f, 0.0f);
	sf::Vector2f deltaMoonPosition(0.0f, 0.0f);

	Dashboard dashboard;
	sf::Vector2i mousePosition;
	sf::Vector2i transformedMousePosition;

	/*sf::Thread t1(&dashboardThread, &window);
	t1.launch();*/



	sf::Font font;
	if (!font.loadFromFile("fonts/Inconsolata/Inconsolata-Regular.ttf")) {
		return EXIT_FAILURE;
	}
	font.loadFromFile("fonts/Inconsolata/Inconsolata-Regular.ttf");
	sf::Text textOther("Hello", font);
	textOther.setCharacterSize(30);
	textOther.setStyle(Text::Regular);
	textOther.setFillColor(Color::Red);
	textOther.setPosition(-450.0f, -440.0f);


	sf::RectangleShape moon(sf::Vector2f(42.4f, 60.0f));
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

	if (!playerTexture.loadFromFile("images/spaceship.png") | !playerTexture.loadFromFile("images/moon.png") | !playerTexture.loadFromFile("images/earth.png")) {
	return EXIT_FAILURE;
	}

	moonTexture.loadFromFile("images/moon.png");
	earthTexture.loadFromFile("images/earth.png");
	playerTexture.loadFromFile("images/spaceship.png");

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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) & !isMousePressed) {
			isMousePressed = true;
			//cout << "Container area clicked!" << '\n';
			mousePosition = Mouse::getPosition(window);
			transformedMousePosition.x = mousePosition.x - VIEW_WIDTH / 2;
			transformedMousePosition.y = mousePosition.y - VIEW_HEIGHT / 2;
			dashboard.Update(transformedMousePosition);
		}
		if (Event::MouseButtonReleased) {
			isMousePressed = false;
		}

		radiusEMOrbit = sqrtf(powf(200.0f, 2.0f) + powf(200.0f, 2.0f));
		angleStepsize = deltaTime;

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

		window.clear(sf::Color::Black);
		window.setView(view);
		player.Draw(window);
		dashboard.Draw(window, textOther);

		//dashboard.Update(mousePosition);
		//moon.Draw(window);
		window.draw(moon);
		window.draw(earth);
		//window.draw(text);
		window.display();  
	}
	return 0;
}

