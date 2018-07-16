// to-the-moon.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Physics.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Dashboard.h"
#include <thread>
#include <cmath>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>
#include <fstream>

using namespace std;
using namespace sf;


static const float VIEW_HEIGHT = 1080.0f;																				 // Define height of the window
static const float VIEW_WIDTH = 1800.0f;																				 // Define width of the window 1400.0f
static const float ANIMATION_SCREEN_SIZE = 980.0f;																		 // Size of the part of the screen that's occupied by the Earth-Moon-SC system and their corresponding animations

double angle = M_PI;																									 // Define angle at which the Moon starts to orbit

float angleStepsize = 0.1f;																								 // Define the angle step size by which the rotation will occur (sketchy phrasing)
float x = 0.0f;																											 // x coordinate of the Moon
float y = 0.0f;																											 // y coordintate of the Moon
float radiusEMOrbit;																									 // initialize Moon orbit radius 
float radiusESCOrbit = 100.f;																							 // Define the distance at which the spacecraft is going to be positioned (LEO)
float deltaTime;																										 // Initialize delta Time float to measure time passed between frames
float deltaTimeMillis;
float kmPerPixel;

bool startAnimation;
bool scFixedInOrbit = true;
bool isMousePressed = false;																							 // Initialize boolean for checking is the left mouse button has been pressed

string valueToBeChanged = "noFocus";																					 // Initialize string that's going to contain the name of the focused container
string parameterValueUnparsed;																							 // String that gets updated every time TextEvent is active and keys are pressed

float lloSC = 300.0f; // km
float realEarthMoonDistance = 384400.0f; // In km
double parameterValue;																										 // New value of the focused container's parameter
double outputAngle;
double outputAngleRad;
vector<state_type> coordinates;
float rawSCPositionData[1480][2];
float rawMoonPositionData[1480][2];
float filteredSCPositionData[1480][2];
float filteredMoonPositionData[1480][2];

float deltaSCCoordinates[1500][2];
float deltaMoonCoordinates[1500][2];

float deltaFilteredSCCoordinates[1427][2];
float deltaFilteredMoonCoordinates[1427][2];

bool isAnimationOn = false;
bool animateSC = false;
int scCounter = 0;
Vector2f scDeltaPosition;


				
void calculateSCTrajectory(double angle, int kmPerPx, CircleShape &spacecraft) {
	coordinates = do_physics(angle);																		// Contains coordinates and velocities of moon and rocket as result of the simulation
	int coordinatesLength;
	float auToKmConversionFactor = 149597871.0f;
	

	for (int i = 0; i < coordinates.size() -1; i++) {
		deltaSCCoordinates[i][0] = (coordinates[i + 1][4] - coordinates[i][4]) * auToKmConversionFactor;
		deltaSCCoordinates[i][1] = (coordinates[i + 1][6] - coordinates[i][6]) * auToKmConversionFactor;
		
		deltaMoonCoordinates[i][0] = coordinates[i + 1][0] - coordinates[i][0] * auToKmConversionFactor / kmPerPx;
		deltaMoonCoordinates[i][1] = coordinates[i + 1][2] - coordinates[i][2] * auToKmConversionFactor / kmPerPx;

		deltaFilteredSCCoordinates[i][0] = deltaSCCoordinates[i][0] / kmPerPx;
		deltaFilteredSCCoordinates[i][1] = deltaSCCoordinates[i][1] / kmPerPx;
	}
	animateSC = true;
}


																										 // Function for resizing the view in case the window is resized (will be removed in near future as there's no need for resizing anything - better to deal with fixed size window)
void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main(int argc, char **argv) {

	

	RenderWindow window(VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "To the Moon!", Style::Close | Style::Resize);				 // Renders the window with pre-set dimensions and enables re-sizing and closing buttons on top right corner of window
	window.setKeyRepeatEnabled(false);
	View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_WIDTH, VIEW_HEIGHT));													 // Set the size of the game view; important to know: game view can be larger than the size of the window, but isn't the case at the moment

	Dashboard dashboard;																								 // Initialize an instance of the Dashboard class

	Vector2f moonPosition(-40.0f, -30.0f);																				 // Define the position vector of the Moon (coordinate system 0,0 point located in the center of the window - not universally true for all coordinates in the game, as you'll see)
	Vector2f moonPreviousPosition(-40.0f, -30.0f);																		 // Initialize the previous position vector of the Moon
	Vector2f deltaMoonPosition(0.0f, 0.0f);																				 // Initialize the deltaPosition vector of the Moon 
	
	Vector2i mousePosition;																								 // Initialize the mouse position vector
	Vector2i transformedMousePosition;																					 // Initialize transformed mouse position vector

	Vector2f distanceMoonEarth;
	Vector2f distanceEarthSC;
	Vector2f distanceMoonSC;

	CircleShape moon(10.0f);
	CircleShape earth(30.0f);																							 // Initialize instance of RectangleShape class to create Earth - will be moved to a separate Earth class
	CircleShape spacecraft(30.0f);

	moon.setFillColor(Color::White);																					 // Define the background color of the RectangleShape of the Moon
	earth.setFillColor(Color::White);																					 // Define the background color of the RectangleShape of the Earth
	spacecraft.setFillColor(Color::White);



	earth.setOrigin(0.5f, 0.5f);																						 // Set the origin of the Earth to be the center instead of the top-left corner of the Rectangle shape
	moon.setOrigin(0.5f, 0.5f);																							 // Set the origin of the Moon to be the center instead of the top-left corner of the Rectangle shape
	spacecraft.setOrigin(0.5f, 0.5f);

	radiusEMOrbit = sqrtf(powf(340.0f, 2.0f) + powf(340.0f, 2.0f));														 // Calculate the Moon orbit radius 
	earth.setPosition(320.0f, -20.0f);																					 // Set the position of the Earth inside the game view
	

	moonPosition.x = earth.getPosition().x -radiusEMOrbit;
	moonPreviousPosition.x = earth.getPosition().x -radiusEMOrbit;
	moon.setPosition(moonPosition);																						 // Set the position of the Moon inside the game view
	earth.setPosition(230.0f, -20.0f);

	scDeltaPosition.x = earth.getPosition().x + radiusESCOrbit * cos(M_PI / 2.0f);
	scDeltaPosition.y = earth.getPosition().y - radiusESCOrbit * sin(M_PI / 2.0f);
	spacecraft.setPosition(scDeltaPosition);

	Texture moonTexture;																								 // Initialize texture class for the Moon to be able to display an image of the Moon
	Texture earthTexture;																								 // Initialize texture class for the Earth to be able to display an image of the Earth
	Texture spacecraftTexture;																								 // Initialize texture class for the Player(SC) to be able to display an image of the Player(SC)

	if (!spacecraftTexture.loadFromFile("images/spaceship.png") | !spacecraftTexture.loadFromFile("images/moon.png") | !spacecraftTexture.loadFromFile("images/earth.png")) {
	return EXIT_FAILURE;																								 // Check if the files actually exist in the project folder - if not, exit the program
	}

	moonTexture.loadFromFile("images/moon.png"); 
	earthTexture.loadFromFile("images/earth.png");
	spacecraftTexture.loadFromFile("images/spaceship.png");

	moon.setTexture(&moonTexture);																						 // Set the above loaded Moon image file as the Moon RectangleShape texture
	earth.setTexture(&earthTexture);																					 // Set the above loaded Earth image file as the Earth RectangleShape texture
	spacecraft.setTexture(&spacecraftTexture);

	bool success = false;

	Clock clock;																										 // Initialize and instance of the class Clock for keeping time
	chrono::milliseconds timespan(16);

	while (window.isOpen()) {																							 // this part of code works while the window is open
		
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
					
					if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {
						parameterValue = stod(parameterValueUnparsed);
						dashboard.pushInput(parameterValue, valueToBeChanged);
						outputAngle = dashboard.getOutputAngle();
						outputAngleRad = 2 * M_PI * outputAngle / 360.0 + M_PI / 2.0;
						valueToBeChanged = "noFocus";
						parameterValueUnparsed = " ";
						
						scDeltaPosition.x = earth.getPosition().x + radiusESCOrbit * cos(outputAngleRad);
						scDeltaPosition.y = earth.getPosition().y - radiusESCOrbit * sin(outputAngleRad);

						
						spacecraft.setPosition(scDeltaPosition);
					}
				}
				break;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
			window.close();																								 // If "X" key is pressed, close the program
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMousePressed) {
			if (dashboard.isEndGamePopupOpen) {
				dashboard.closeGamePopup();
			}
			isMousePressed = true;																						 // Sets the boolean as true to indicate that the mouse button was pressed 
			mousePosition = Mouse::getPosition(window);																	 // Identify the position on the window where the mouse was clicked; the window parameter is needed to get the coordinates relative to the game window, not the whole screen; These coordinates have a coordinate system where the (0,0) point is in the top-left corner, hence the two following coordinate transformations
			transformedMousePosition.x = mousePosition.x - VIEW_WIDTH / 2;												 // Transform x coordinate from top-left-corner-based coord. system to center-based coord. system
			transformedMousePosition.y = mousePosition.y - VIEW_HEIGHT / 2;												 // Transform y coordinate from top-left-corner-based coord. system to center-based coord. system
			valueToBeChanged = dashboard.Update(transformedMousePosition, window);										 // Feed the transformed mouse click coordinates in the Dashboard class's Update function for further actions
			if (valueToBeChanged == "LaunchButton") {
				dashboard.launchButtonToggled(true);
				dashboard.disableGamePopup = false;
				dashboard.isEndGamePopupOpen = true;
				kmPerPixel = realEarthMoonDistance / ANIMATION_SCREEN_SIZE;
				calculateSCTrajectory(outputAngle, kmPerPixel, spacecraft);
				animateSC = true;
			}
		}

		if (Event::MouseButtonReleased) {
			dashboard.launchButtonToggled(false);
			isMousePressed = false;																						 // Set the boolean to false when the mouse button is released
		}


		// -----------------------------------------------------------------------------//
		//            HERE ANIMATION STUFF HAPPENS, AT A DEFINED FRAME RATE				//
		// -----------------------------------------------------------------------------//


		// Check this for success/failure

		deltaTimeMillis = clock.getElapsedTime().asMilliseconds() / 1000.0f;

		deltaTime = clock.restart().asSeconds();

		//distanceMoonEarth.x = moon.getPosition().x - earth.getPosition().x;
		//distanceMoonEarth.y = moon.getPosition().y - earth.getPosition().y;

		
		angleStepsize = 0.006f;																						 // Set the angle step size as the time passed between frames - will be changes in the future as part of implementing a physics-based orbital speed manipulation functions
		float totalNrSteps = 360.0f / angleStepsize;
		float orbitalPeriod;

		if (angle > 2 * M_PI)
			angle = 0.00f;																							// If 2*Pi radians have been traveled, set the angle to 0 rad

		// Here coordinate mapping happens

		
		if (!isAnimationOn && animateSC) {
			scCounter = 0;
			isAnimationOn = true;
		}

		if (isAnimationOn && animateSC && scCounter != 1059076933) {
			moonPreviousPosition.x = moonPosition.x;																	 // Set the Moon's current x coordinate as the previous Moon x coordinate
			moonPreviousPosition.y = moonPosition.y;																	 // Set the Moon's current y coordinate as the previous Moon y coordinate

			moonPosition.x = radiusEMOrbit * cos(angle) + radiusEMOrbit / 2;											 // Calculate the Moon's new x coordinate using quick MATHS
			moonPosition.y = -radiusEMOrbit * sin(angle);																 // Calculate the Moon's new y coordinate using quick MATHS

			deltaMoonPosition.x = moonPosition.x - moonPreviousPosition.x;												 // Calculate the Moon x position offset
			deltaMoonPosition.y = moonPosition.y - moonPreviousPosition.y;												 // Calculate the Moon y position offset

			moon.move(deltaMoonPosition);
			spacecraft.move(deltaFilteredSCCoordinates[scCounter][0], deltaFilteredSCCoordinates[scCounter][1]);
			scCounter++;
			if (scCounter == 1425) dashboard.endGamePopup(success);
		} 
		if (scCounter >= 1426) {
			scCounter = 0;
			animateSC = false;
		}

																			 // Move the Moon to a new position where the above-calculated position offsets are added to the current Moon position 
		angle += angleStepsize;																						 // Increment the angle at which Moon is going to be located in the next frame

		
		window.clear(sf::Color::Black);																					 // Clear the window screen and set it to black; otherwise, the previous frame will still be present and everything will become a big blur at some point - try commenting this line out to see how it'll look if you don't call this function
		window.setView(view);																							 // Set the game view needed to be displayed - in a static view, like ours, it doesn't do anything interesting, but if the game moves around a bigger landscape, this needs to be updated to show the new landscape
		dashboard.Draw(window);																							 // Draw the dashboard at every frame to make it consistent and fluid, calling the Dashboard class's Draw function 

		window.draw(spacecraft);
		window.draw(moon);																								 // Draw the Moon texture every frame for fluid and consistent animation and gameplay
		window.draw(earth);																								 // Draw the Earth texture every frame for fluid and consistent animation and gameplay
		window.display();																								 // DISPLAY EVERYTHING WE'VE WORKED FOR SO HARD TO SET UP
		scCounter++;
		this_thread::sleep_for(timespan);
	}
	return 0;
}

