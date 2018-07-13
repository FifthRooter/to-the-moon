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


static const float VIEW_HEIGHT = 1080.0f;																				 // Define height of the window
static const float VIEW_WIDTH = 1800.0f;																				 // Define width of the window 1400.0f
double angle = M_PI;																									 // Define angle at which the Moon starts to orbit
float angleStepsize = 0.1f;																								 // Define the angle step size by which the rotation will occur (sketchy phrasing)
float x = 0.0f;																											 // x coordinate of the Moon
float y = 0.0f;																											 // y coordintate of the Moon
float radiusEMOrbit;																									 // initialize Moon orbit radius 
bool isMousePressed = false;																							 // Initialize boolean for checking is the left mouse button has been pressed
string valueToBeChanged = "noFocus";																					 // Initialize string that's going to contain the name of the focused container
string parameterValueUnparsed;																							 // String that gets updated every time TextEvent is active and keys are pressed
int parameterValue;																										 // New value of the focused container's parameter

																														 // Function for resizing the view in case the window is resized (will be removed in near future as there's no need for resizing anything - better to deal with fixed size window)
void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main() {
	RenderWindow window(VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "To the Moon!", Style::Close | Style::Resize);				 // Renders the window with pre-set dimensions and enables re-sizing and closing buttons on top right corner of window
	View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_WIDTH, VIEW_HEIGHT));													 // Set the size of the game view; important to know: game view can be larger than the size of the window, but isn't the case at the moment
	Vector2f moonPosition(-40.0f, -30.0f);																				 // Define the position vector of the Moon (coordinate system 0,0 point located in the center of the window - not universally true for all coordinates in the game, as you'll see)
	Vector2f moonPreviousPosition(-40.0f, -30.0f);																		 // Initialize the previous position vector of the Moon
	Vector2f deltaMoonPosition(0.0f, 0.0f);																				 // Initialize the deltaPosition vector of the Moon 

	Dashboard dashboard;																								 // Initialize an instance of the Dashboard class
	Vector2i mousePosition;																								 // Initialize the mouse position vector
	Vector2i transformedMousePosition;																					 // Initialize transformed mouse position vector


	window.setKeyRepeatEnabled(false);
	string::size_type sz;

	CircleShape moon(10.0f);
	CircleShape earth(30.0f);																							 // Initialize instance of RectangleShape class to create Earth - will be moved to a separate Earth class

	moon.setFillColor(Color::White);																					 // Define the background color of the RectangleShape of the Moon
	earth.setFillColor(Color::White);																					 // Define the background color of the RectangleShape of the Earth

	earth.setOrigin(0.5f, 0.5f);																						 // Set the origin of the Earth to be the center instead of the top-left corner of the Rectangle shape
	moon.setOrigin(0.5f, 0.5f);																							 // Set the origin of the Moon to be the center instead of the top-left corner of the Rectangle shape

	radiusEMOrbit = sqrtf(powf(350.0f, 2.0f) + powf(350.0f, 2.0f));													 // Calculate the Moon orbit radius 
	earth.setPosition(320.0f, -20.0f);																					 // Set the position of the Earth inside the game view

	moonPosition.x = earth.getPosition().x -radiusEMOrbit;
	moonPreviousPosition.x = earth.getPosition().x -radiusEMOrbit;
	moon.setPosition(moonPosition);																						 // Set the position of the Moon inside the game view
	earth.setPosition(230.0f, -20.0f);

	Texture moonTexture;																								 // Initialize texture class for the Moon to be able to display an image of the Moon
	Texture earthTexture;																								 // Initialize texture class for the Earth to be able to display an image of the Earth
	Texture playerTexture;																								 // Initialize texture class for the Player(SC) to be able to display an image of the Player(SC)

	if (!playerTexture.loadFromFile("images/spaceship.png") | !playerTexture.loadFromFile("images/moon.png") | !playerTexture.loadFromFile("images/earth.png")) {
	return EXIT_FAILURE;																								 // Check if the files actually exist in the project folder - if not, exit the program
	}

	moonTexture.loadFromFile("images/moon.png"); 
	earthTexture.loadFromFile("images/earth.png");
	playerTexture.loadFromFile("images/spaceship.png");

	moon.setTexture(&moonTexture);																						 // Set the above loaded Moon image file as the Moon RectangleShape texture

	earth.setTexture(&earthTexture);																					 // Set the above loaded Earth image file as the Earth RectangleShape texture

	Player player(&playerTexture, sf::Vector2u(1, 1), 0.3f, 100.0f);													 // Initialize an instance of the Player class, where the 1st parameter is the Player texture with an address-of operator that is pointer for the specific memory address, 2nd parameter indicates the amount of parts of image to parse through for animated player movement (currently not used, so set to one image - 1,1), 3rd parameter sets the rate at which the aniamtion images need to be changes, 4th parameter sets the rate at which the player moves


	int counter = 0;																									 // Counter currently used to influence the orbital speed; will be changed into a function that allows easy tweaking of the orbital speed in a realistic way
	float deltaTime;																									 // Initialize delta Time float to measure time passed between frames
	float deltaTimeMillis;
	Clock clock;																										 // Initialize and instance of the class Clock for keeping time


	//player.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 8, textureSize.x, textureSize.y));

	while (window.isOpen()) {																							 // this part of code works while the window is open
		deltaTime = clock.restart().asSeconds();
		deltaTimeMillis = deltaTime * 3000;																		 // Puts the time counter to zero and returns the time passed since the last time the clock was started, in seconds
		//cout << "Frame length: " << deltaTimeMillis << "ms"<< endl;
		cout << "Frame rate: " << 1000 * deltaTime << "Hz" << endl;
		Event evnt;																										 // Initialize an instance of the class Event - used for detecting if the windows is closed, resized, or if any keyboard keys or mouse buttons are pressed

		while (window.pollEvent(evnt)) {																				 // While loop that deals with window events like Closing and Resizing

			switch (evnt.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			case sf::Event::TextEntered:
				if ( evnt.text.unicode < 128 && valueToBeChanged != "noFocus") {
					parameterValueUnparsed += evnt.text.unicode;
					cout << "Parameter value (press Enter to submit): " << parameterValueUnparsed << endl; // isdigit(evnt.text.unicode)
					parameterValue = stoi(parameterValueUnparsed, &sz);
					if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {
						dashboard.pushInput(parameterValue, valueToBeChanged);
						valueToBeChanged = "noFocus";
						parameterValueUnparsed = " ";
					}
				}
				break;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
			window.close();																								 // If "X" key is pressed, close the program
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMousePressed) {
			isMousePressed = true;																						 // Sets the boolean as true to indicate that the mouse button was pressed 
			mousePosition = Mouse::getPosition(window);																	 // Identify the position on the window where the mouse was clicked; the window parameter is needed to get the coordinates relative to the game window, not the whole screen; These coordinates have a coordinate system where the (0,0) point is in the top-left corner, hence the two following coordinate transformations
			transformedMousePosition.x = mousePosition.x - VIEW_WIDTH / 2;												 // Transform x coordinate from top-left-corner-based coord. system to center-based coord. system
			transformedMousePosition.y = mousePosition.y - VIEW_HEIGHT / 2;												 // Transform y coordinate from top-left-corner-based coord. system to center-based coord. system
			valueToBeChanged = dashboard.Update(transformedMousePosition, window);										 // Feed the transformed mouse click coordinates in the Dashboard class's Update function for further actions
		}


		if (Event::MouseButtonReleased) {
			isMousePressed = false;																						 // Set the boolean to false when the mouse button is released
		}


		float xMoonEarth = moon.getPosition().x - earth.getPosition().x;
		float yMoonEarth = moon.getPosition().y - earth.getPosition().y;

		
		angleStepsize = deltaTime;																						 // Set the angle step size as the time passed between frames - will be changes in the future as part of implementing a physics-based orbital speed manipulation functions
		float totalNrSteps = 360.0f / deltaTime;
		float orbitalPeriod;

		if (angle > 2 * M_PI)
			angle = 0.00f;																								 // If 2*Pi radians have been traveled, set the angle to 0 rad


		if (counter > 1) {
			counter = 0;																								 // Set the counter to zero

			moonPreviousPosition.x = moonPosition.x;																	 // Set the Moon's current x coordinate as the previous Moon x coordinate
			moonPreviousPosition.y = moonPosition.y;																	 // Set the Moon's current y coordinate as the previous Moon y coordinate

			moonPosition.x = radiusEMOrbit * cos(angle) + radiusEMOrbit / 2;																 // Calculate the Moon's new x coordinate using quick MATHS
			moonPosition.y = -radiusEMOrbit * sin(angle);																 // Calculate the Moon's new y coordinate using quick MATHS

			deltaMoonPosition.x = moonPosition.x - moonPreviousPosition.x;												 // Calculate the Moon x position offset
			deltaMoonPosition.y = moonPosition.y - moonPreviousPosition.y;												 // Calculate the Moon y position offset

			moon.move(deltaMoonPosition);																				 // Move the Moon to a new position where the above-calculated position offsets are added to the current Moon position 
			angle += angleStepsize;																						 // Increment the angle at which Moon is going to be located in the next frame

		}

		
		counter++;																										 // Increment the counter 

		player.Update(deltaTime);																						 // Update the Player animation

		window.clear(sf::Color::Black);																					 // Clear the window screen and set it to black; otherwise, the previous frame will still be present and everything will become a big blur at some point - try commenting this line out to see how it'll look if you don't call this function
		window.setView(view);																							 // Set the game view needed to be displayed - in a static view, like ours, it doesn't do anything interesting, but if the game moves around a bigger landscape, this needs to be updated to show the new landscape
		player.Draw(window);																							 // Draw the player texture according to the animation functions inside the Player-Animation class interactions, and to just make the game animation consistent and fluid, calling the Player class's Draw function 
		dashboard.Draw(window);																							 // Draw the dashboard at every frame to make it consistent and fluid, calling the Dashboard class's Draw function 

		window.draw(moon);																								 // Draw the Moon texture every frame for fluid and consistent animation and gameplay
		window.draw(earth);																								 // Draw the Earth texture every frame for fluid and consistent animation and gameplay
		window.display();																								 // DISPLAY EVERYTHING WE'VE WORKED FOR SO HARD TO SET UP
	}
	return 0;
}

