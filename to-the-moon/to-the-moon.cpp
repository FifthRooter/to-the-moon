// to-the-moon.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Physics.h"
#define _USE_MATH_DEFINES
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
float kmPerPixel;																										 // Conversion factor to scale from kilometers to pixels (calculated by dividing the real distance between the Moon and the Earth by half the animation screen size)

bool startAnimation = false;																									 // Boolean for identifying if the animation should be initiated
bool isMousePressed = false;																							 // Initialize boolean for checking if the left mouse button has been pressed
bool animateSC = false;																									 // Boolean for initiating functions that animate the movement of the SC
bool* isAnimationOn = new bool(false);																								 // Boolean for knowing if the animation is on at the moment

string valueToBeChanged = "noFocus";																					 // Initialize string that's going to contain the name of the focused container
string parameterValueUnparsed;																							 // String that gets updated every time TextEvent is active and keys are pressed

float realEarthMoonDistance = 384400.0f;																				 // Real life value for the dist. between Earth and Moon
double parameterValue;																									 // New value of the focused container's parameter
double outputAngle;																										 // The angle used to position the sc for launching, in deg
double outputAngleRad;																								     // The same as above only in radians

float deltaSCCoordinates[1427][2];																						 // 1427x2 array containing the difference between consequent position vectors for Spacecraft
float deltaMoonCoordinates[1427][2];																					 // 1427x2 array containing the difference between consequent position vectors for Moon

float deltaFilteredSCCoordinates[1427][2];																				 // 1427x2 array containing converted SC coordinates
float deltaFilteredMoonCoordinates[1427][2];																			 // 1427x2 array containing converted SC coordinates

int* scCounter = new int(0);																							 // Counter for counting

Vector2f scDeltaPosition;																								 
vector<state_type> coordinates;																							 // Contains an array of different vectors for SC & Moon (position, velocity)


				
void calculateSCTrajectory(double angle, int kmPerPx, CircleShape &spacecraft) {										 // Function for calculating spacecraft&Moon's trajectories
	coordinates = do_physics(angle);																					 // Contains coordinates and velocities of moon and rocket as a result of the simulation
	float auToKmConversionFactor = 149597871.0f;																		 // Factor to convert between AU (astronomical units) and km
	
	for (int i = 0; i < coordinates.size() -1; i++) {
		deltaSCCoordinates[i][0] = (coordinates[i + 1][4] - coordinates[i][4]) * auToKmConversionFactor / kmPerPx;		 // Calculate the difference in positions between consequent time steps for spacecraft's x coordinates
		deltaSCCoordinates[i][1] = (coordinates[i + 1][6] - coordinates[i][6]) * auToKmConversionFactor / kmPerPx;		 // Calculate the difference in positions between consequent time steps for spacecraft' y coordinates
		
		deltaMoonCoordinates[i][0] = coordinates[i + 1][0] - coordinates[i][0] * auToKmConversionFactor / kmPerPx;		 // Calculate the difference in positions between consequent time steps for Moon's x coordinates
		deltaMoonCoordinates[i][1] = coordinates[i + 1][2] - coordinates[i][2] * auToKmConversionFactor / kmPerPx;		 // Calculate the difference in positions between consequent time steps for Moon's y coordinates
	}
	animateSC = true;																									 // Set the boolean to true so that a relevant if statement picks it up and starts animating the spacecraft's movement
	cout << "Launch angle used in calculations: " << angle << endl;

}


// Function for resizing the view in case the window is resized (will be removed in near future as there's no need for resizing anything - better to deal with fixed size window)
void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main(int argc, char **argv) {
	cout << "scCounter memory location: " << &scCounter << endl;
	RenderWindow window(VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "To the Moon!", Style::Close | Style::Resize);				 // Renders the window with pre-set dimensions and enables re-sizing and closing buttons on top right corner of window
	window.setKeyRepeatEnabled(false);
	View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_WIDTH, VIEW_HEIGHT));													 // Set the size of the game view; important to know: game view can be larger than the size of the window, but isn't the case at the moment

	Dashboard dashboard;																								 // Initialize an instance of the Dashboard class

	Vector2i mousePosition;																								 // Initialize the mouse position vector
	Vector2i transformedMousePosition;																					 // Initialize transformed mouse position vector

	CircleShape moon(10.0f);																							 // Initialize instance of CircleShape for the Moon using the SFML lib's class
	CircleShape earth(30.0f);																							 // Initialize instance of CircleShape for the Earth using the SFML lib's class
	CircleShape spacecraft(30.0f);																						 // Initialize instance of CircleShape for the Spacecraft using the SFML lib's class

	moon.setFillColor(Color::White);																					 // Define the background color of the CircleShape of the Moon
	earth.setFillColor(Color::White);																					 // Define the background color of the CircleShape of the Earth
	spacecraft.setFillColor(Color::White);																			     // Define the background color of the CircleShape of the Spacecraft


	earth.setOrigin(0.5f, 0.5f);																						 // Set the origin of the Earth to be the center instead of the top-left corner of the CircleShape
	moon.setOrigin(0.5f, 0.5f);																							 // Set the origin of the Moon to be the center instead of the top-left corner of the CircleShape
	spacecraft.setOrigin(0.5f, 0.5f);																					 // Set the origin of the Spacecraft to be the center instead of the top-left corner of the CircleShape

	radiusEMOrbit = sqrt(pow(340.0f, 2.0f) + pow(340.0f, 2.0f));														 // Calculate the Moon orbit radius 
	earth.setPosition(230.0f, -20.0f);																					 // Set the position of the Earth

	Vector2f moonPosition(earth.getPosition().x + radiusEMOrbit * cos(3.884), earth.getPosition().y - radiusEMOrbit * sin(3.884));																				 // Define the position vector of the Moon (coordinate system 0,0 point located in the center of the window - not universally true for all coordinates in the game, as you'll see)
	Vector2f moonPreviousPosition(earth.getPosition().x + radiusEMOrbit * cos(3.884), earth.getPosition().y - radiusEMOrbit * sin(3.884));																		 // Initialize the previous position vector of the Moon
	Vector2f deltaMoonPosition(0.0f, 0.0f);																				 // Initialize the deltaPosition vector of the Moon 

	moon.setPosition(moonPosition);																						 // Set the position of the Moon inside the game view

	scDeltaPosition.x = earth.getPosition().x + radiusESCOrbit * cos(M_PI / 2.0f);		 								 // Calculate the spacecraft's initial x position, which is at 100px distance a Pi/2 counterclockwise turn
	scDeltaPosition.y = earth.getPosition().y - radiusESCOrbit * sin(M_PI / 2.0f);										 // Calculate the spacecraft's initial y position
	spacecraft.setPosition(scDeltaPosition);

	Texture moonTexture;																								 // Initialize texture class for the Moon to be able to display an image of the Moon
	Texture earthTexture;																								 // Initialize texture class for the Earth to be able to display an image of the Earth
	Texture spacecraftTexture;																							 // Initialize texture class for the Player(SC) to be able to display an image of the Player(SC)

	if (!spacecraftTexture.loadFromFile("images/spaceship.png") | !spacecraftTexture.loadFromFile("images/moon.png") | !spacecraftTexture.loadFromFile("images/earth.png")) {
	return EXIT_FAILURE;																								 // Check if the files actually exist in the project folder - if not, exit the program
	}

	moonTexture.loadFromFile("images/moon.png");																		 // Load images for Moon, Earth and the spacecraft
	earthTexture.loadFromFile("images/earth.png");
	spacecraftTexture.loadFromFile("images/spaceship.png");

	moon.setTexture(&moonTexture);																						 // Set the above loaded Moon image file as the Moon CircleShape texture
	earth.setTexture(&earthTexture);																					 // Set the above loaded Earth image file as the Earth CircleShape texture
	spacecraft.setTexture(&spacecraftTexture);																		     // Set the above loaded Spacecraft image file as the Earth CircleShape texture

	bool success = false;																								 // Boolean from the Physics class - shows whether the SC has reached the Moon or not

	Clock clock;																										 // Initialize and instance of the class Clock for keeping time
	chrono::milliseconds timespan(15);																					 // Set up time in milliseconds for controlling the frame rate of the game

	while (window.isOpen()) {																							 // this part of code works while the window is open
		
		Event evnt;																										 // Initialize an instance of the class Event - used for detecting if the windows is closed, resized, or if any keyboard keys or mouse buttons are pressed

		while (window.pollEvent(evnt)) {																				 // While loop that deals with window events like Closing and Resizing

			switch (evnt.type) {

			case sf::Event::Closed:																						 // If X on window pressed, exit program
				window.close();
				break;
			case sf::Event::Resized:																					 // If Resize button pressed on the window, utilize the ResizeView func to properly resize while maintaining the aspect ratio
				ResizeView(window, view);
				break;
			case sf::Event::TextEntered:																				 // Text event - registers all keypresses pressed by the user
				if ( evnt.text.unicode < 128 && valueToBeChanged != "noFocus") {										 // Check if input fits the unicode character table (UTF-8) and whether the variable string does not equal this string
					parameterValueUnparsed += evnt.text.unicode;														 // Add the corresponding character with the key pressed by the user to an unparsed string
					
					if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {													 // If during this TextEntered event the Return key is pressed, then...
						parameterValue = stod(parameterValueUnparsed);													 // Convert the string parameter to a double...
						dashboard.pushInput(parameterValue, valueToBeChanged);											 // and pass it into the dashboard's class
						outputAngle = parameterValue;
						outputAngleRad = (outputAngle) * 2 * M_PI / 360.0 + M_PI / 2.0;									 // Convert output angle from degrees to radians
						valueToBeChanged = "noFocus";																	 // Renaming the variable string
						parameterValueUnparsed = " ";
						
						scDeltaPosition.x = earth.getPosition().x + radiusESCOrbit * cos(outputAngleRad);				 // Calculate the position of the spacecraft using geometry
						scDeltaPosition.y = earth.getPosition().y - radiusESCOrbit * sin(outputAngleRad);

						spacecraft.setPosition(scDeltaPosition);														 // Set the position of the spacecraft
					}
				}
				break;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
			window.close();																								 // If "X" key is pressed, close the program
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMousePressed) {
			if (dashboard.isEndGamePopupOpen) {																			 // If the end game popup/announcement is open...
				dashboard.closeGamePopup();																				 // close the popup by clicking anywhere on the screen
				scDeltaPosition.x = earth.getPosition().x + radiusESCOrbit * cos(34.53 * 2 * M_PI / 360.0 + M_PI / 2.0);				 // Calculate the position of the spacecraft using geometry
				scDeltaPosition.y = earth.getPosition().y - radiusESCOrbit * sin(34.53 * 2 * M_PI / 360.0 + M_PI / 2.0);
				angle = 3.884;
				moonPosition.x = earth.getPosition().x + radiusEMOrbit * cos(angle) / 2;											 // Calculate the Moon's new x coordinate using quick MATHS
				moonPosition.y = earth.getPosition().y - radiusEMOrbit * sin(angle) / 2;
				//moonPosition.x = earth.getPosition().x - radiusEMOrbit / 2;
				//moonPosition.y = -30.0f;
				moon.setPosition(moonPosition);
				spacecraft.setPosition(scDeltaPosition);														 // Set the position of the spacecraft
			}
			isMousePressed = true;																						 // Sets the boolean as true to indicate that the mouse button was pressed 
			mousePosition = Mouse::getPosition(window);																	 // Identify the position on the window where the mouse was clicked; the window parameter is needed to get the coordinates relative to the game window, not the whole screen; These coordinates have a coordinate system where the (0,0) point is in the top-left corner, hence the two following coordinate transformations
			transformedMousePosition.x = mousePosition.x - VIEW_WIDTH / 2;												 // Transform x coordinate from top-left-corner-based coord. system to center-based coord. system
			transformedMousePosition.y = mousePosition.y - VIEW_HEIGHT / 2;												 // Transform y coordinate from top-left-corner-based coord. system to center-based coord. system
			valueToBeChanged = dashboard.Update(transformedMousePosition, window);										 // Feed the transformed mouse click coordinates in the Dashboard class's Update function for further actions
			if (valueToBeChanged == "LaunchButton") {																	 // If the variable string meets the criteria, perform these tasks
				dashboard.launchButtonToggled(true);																	 // Indicate that the Launch button is toggled so that it turns a bit darker red to indicate that it's been pressed; doesn't work 100%
				dashboard.disableGamePopup = false;																	     // Don't disable the game popup
				dashboard.isEndGamePopupOpen = true;																	 // Indicate that the popup is indeed open
				kmPerPixel = realEarthMoonDistance / ANIMATION_SCREEN_SIZE;												 // Calculate km/px
				calculateSCTrajectory(outputAngle, kmPerPixel, spacecraft);											     // Calculate trajectories by passing in parameters output angle, kmPerPx
				animateSC = true;																						 // Yes, animate the spacecraft
			}
		}

		if (Event::MouseButtonReleased) {
			dashboard.launchButtonToggled(false);
			isMousePressed = false;																						 // Set the boolean to false when the mouse button is released
		}


		// -----------------------------------------------------------------------------//
		//            HERE ANIMATION STUFF HAPPENS, AT A DEFINED FRAME RATE				//
		// -----------------------------------------------------------------------------//

		angleStepsize = 0.006f;																							 // Set the angle step size as the time passed between frames - will be changes in the future as part of implementing a physics-based orbital speed manipulation functions
		float totalNrSteps = 360.0f / angleStepsize;

		if (angle > 2 * M_PI)	
			angle = 0.00f;																								 // If 2*Pi radians have been traveled, set the angle to 0 rad

		// Here coordinate mapping happens

		
		if (!*isAnimationOn && animateSC) {																				 // Needed for making sure that the animation runs exactly when needed
			*scCounter = 0;
			*isAnimationOn = true;
			cout << "All systems go" << endl;
		}

		if (*isAnimationOn && animateSC) {													 // The last parameter is kind of a mistery - After running the trajectory calculation function, the counter just overflows and starts counting from a ridiculously high number
			moonPreviousPosition.x = moonPosition.x;																	 // Set the Moon's current x coordinate as the previous Moon x coordinate
			moonPreviousPosition.y = moonPosition.y;																	 // Set the Moon's current y coordinate as the previous Moon y coordinate
	
			moonPosition.x = earth.getPosition().x + radiusEMOrbit * cos(angle)/2;											 // Calculate the Moon's new x coordinate using quick MATHS
			moonPosition.y = earth.getPosition().y - radiusEMOrbit * sin(angle)/2;																 // Calculate the Moon's new y coordinate using quick MATHS

			deltaMoonPosition.x = moonPosition.x - moonPreviousPosition.x;												 // Calculate the Moon x position offset
			deltaMoonPosition.y = moonPosition.y - moonPreviousPosition.y;												 // Calculate the Moon y position offset

			moon.move(deltaMoonPosition);																				 // Move the Moon
			cout << "scCounter: " << *scCounter << endl;
			spacecraft.move(deltaSCCoordinates[*scCounter][0], deltaSCCoordinates[*scCounter][1]);					     // Move the spacecraft
			(*scCounter)++;																								 // Count
			if (*scCounter == 1425) {
				*isAnimationOn = false;
				animateSC = false;
				dashboard.endGamePopup(success);														 // After all of the simulation data points have been used for animation, display the end of game popup, which isn't fully working though
			}
		}	
		if (*scCounter >= 1426) {																						 // If the counter reaches this amount, reset, otherwise won't be able to get coordinates from most vectors
			*scCounter = 0;
			animateSC = false;
		}

																														 // Move the Moon to a new position where the above-calculated position offsets are added to the current Moon position 
		angle += angleStepsize;																						     // Increment the angle at which Moon is going to be located in the next frame

		
		window.clear(sf::Color::Black);																					 // Clear the window screen and set it to black; otherwise, the previous frame will still be present and everything will become a big blur at some point - try commenting this line out to see how it'll look if you don't call this function
		window.setView(view);																							 // Set the game view needed to be displayed - in a static view, like ours, it doesn't do anything interesting, but if the game moves around a bigger landscape, this needs to be updated to show the new landscape
		dashboard.Draw(window);																							 // Draw the dashboard at every frame to make it consistent and fluid, calling the Dashboard class's Draw function 

		window.draw(spacecraft);
		window.draw(moon);																								 // Draw the Moon texture every frame for fluid and consistent animation and gameplay
		window.draw(earth);																								 // Draw the Earth texture every frame for fluid and consistent animation and gameplay
		window.display();																								 // DISPLAY EVERYTHING WE'VE WORKED FOR SO HARD TO SET UP
		(*scCounter)++;																									 // Increment counter
		this_thread::sleep_for(timespan);																				 // Delay jumping to the next loop by this amount (for controlling frame rate)
	}
	return 0;
}

