// to-the-moon.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {

	sf::RenderWindow window(sf::VideoMode(512, 512), "Serious Game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	//sf::RectangleShape player(sf::Vector2f(100.0f, 150.0f));
	//player.setFillColor(sf::Color::Red);
	//player.setOrigin(50.0f, 50.0f);
	//player.setPosition(206.0f, 206.0f);
	sf::Texture playerTexture;

	if (!playerTexture.loadFromFile("spaceship.png")) {
	return EXIT_FAILURE;
	}

	playerTexture.loadFromFile("spaceship.png");
	//player.setTexture(&playerTexture);

	Player player(&playerTexture, sf::Vector2u(1, 1), 0.3f, 100.0f);

	Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	Platform platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));


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
			/*case sf::Event::TextEntered:
			if (evnt.text.unicode < 128) {
			printf("%c", evnt.text.unicode);
			}
			break;*/
			}
		}
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		player.move(0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		player.move(0.0f, 0.1f);
		}*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
		window.close();
		}

		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		player.setPosition((float)mousePos.x, (float)(mousePos.y));
		}*/

		player.Update(deltaTime);

		//platform1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
		//platform2.GetCollider().CheckCollision(player.GetCollider(), 1.0f);


		//view.setCenter(player.GetPosition());

		window.clear(sf::Color(150, 150, 150));
		window.setView(view);
		player.Draw(window);
		//platform1.Draw(window);
		//platform2.Draw(window);
		window.display();  
	}
	return 0;
}

