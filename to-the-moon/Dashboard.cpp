#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dashboard.h"


using namespace std;
using namespace sf;

Dashboard::Dashboard()
{

	if (!font.loadFromFile("fonts/Inconsolata/Inconsolata-Regular.ttf")) {
		cout << "Could not load the font!" << '\n';
	}
	font.loadFromFile("fonts/Inconsolata/Inconsolata-Regular.ttf");

	rocketEquationTexture.loadFromFile("images/rocket_equation.png");
	deltaVTransferTexture.loadFromFile("images/transfer_delta_v.png");
	thetaMoonEquationTexture.loadFromFile("images/moon_angle.png");
	gravityLawTexture.loadFromFile("images/law_of_gravity.png");



	// Equation textures

	rocketEquation.setTexture(&rocketEquationTexture);
	deltaVTransfer.setTexture(&deltaVTransferTexture);
	gravityLaw.setTexture(&gravityLawTexture);
	thetaMoonEquation.setTexture(&thetaMoonEquationTexture);

	rocketEquation.setPosition(rocketEquationTexturePosition);
	deltaVTransfer.setPosition(deltaVTransferTexturePosition);
	gravityLaw.setPosition(gravityLawTexturePosition);
	thetaMoonEquation.setPosition(thetaMoonEquationTexturePosition);


	rocketEquation.setSize(rocketEquationTextureSize);
	deltaVTransfer.setSize(deltaVTransferTextureSize);
	gravityLaw.setSize(gravityLawTextureSize);
	thetaMoonEquation.setSize(thetaMoonEquationTextureSize);


	// Output angle text setup
	outputAngleText.setFont(font);
	outputAngleText.setString(outputAngleTxt);
	outputAngleText.setPosition(outputAngleTextPosition);

	outputAngleText.setCharacterSize(textSize);
	outputAngleText.setStyle(textStyle);
	outputAngleText.setFillColor(textColor);

	// Output angle value setup
	outputAngleValueText.setFont(font);
	outputAngleValueText.setString(to_string(outputAngleValue) + "deg");
	outputAngleValueText.setPosition(outputAngleValuePosition);

	outputAngleValueText.setCharacterSize(textSize);
	outputAngleValueText.setStyle(textStyle);
	outputAngleValueText.setFillColor(textColor);



	// Output angle container setup
	outputAngleTextContainer.setPosition(outputAngleTextContainerPosition);
	outputAngleTextContainer.setSize(outputAngleTextContainerSize);
	outputAngleTextContainer.setOutlineColor(Color::White);
	outputAngleTextContainer.setOutlineThickness(2.0f);

	outputAngleValueContainer.setPosition(outputAngleValueContainerPosition);
	outputAngleValueContainer.setSize(outputAngleValueContainerSize);
	outputAngleValueContainer.setOutlineColor(Color::White);
	outputAngleValueContainer.setOutlineThickness(2.0f);

	outputAngleTextContainer.setFillColor(sf::Color::Transparent);
	outputAngleValueContainer.setFillColor(sf::Color::Transparent);


	// Launch button
	launchButton.setRadius(launchButtonRadius);
	launchButton.setPosition(launchButtonPosition);
	launchButton.setFillColor(Color::Red);

	launchButtonText.setColor(launchButtonTextColor);
	launchButtonText.setCharacterSize(launchButtonTextSize);
	launchButtonText.setStyle(textStyle);
	launchButtonText.setFillColor(launchButtonTextColor);
	launchButtonText.setPosition(launchButtonTextPosition);
	launchButtonText.setString("Launch");


	// End game text setup
	endGameTxt.setFont(font);
	endGameTxt.setCharacterSize(endGameTextSize);
	endGameTxt.setString("Yo");
	endGameTxt.setStyle(textStyle);
	endGameTxt.setColor(successColor);
	endGameTxt.setPosition(endGameTextPosition);

	// Is container focused booleans
	isOutputAngleValueContainerFocused = false;
	noFocus = true;
}


Dashboard::~Dashboard()
{
}

String Dashboard::Update(Vector2i& mousePosition, RenderWindow& window)
{
	focusIfDashboardClicked(mousePosition);
	cout << "Mouse X position" << mousePosition.x << endl;
	cout << "Mouse Y position" << mousePosition.y << endl;
	if (isOutputAngleValueContainerFocused) {
		valueToBeChanged = "OutputAngle";
		outputAngleValueText.setString(outputAngle + "deg");
		toggleFocusAllContainers(false);
	}
	else if (noFocus) {
		valueToBeChanged = "noFocus";
		toggleFocusAllContainers(false);
	}

	return valueToBeChanged;
}

void Dashboard::Draw(RenderWindow & window)
{
	if (!disableGamePopup && isEndGamePopupOpen) {
		window.draw(endGameTxt);
	}
	window.draw(launchButton);
	window.draw(thetaMoonEquation);
	window.draw(gravityLaw);
	window.draw(deltaVTransfer);
	window.draw(rocketEquation);
	window.draw(outputAngleText);
	window.draw(outputAngleValueText);
	window.draw(outputAngleTextContainer);
	window.draw(outputAngleValueContainer);
}

void Dashboard::toggleFocusAllContainers(bool isFocused)
{
	isOutputAngleValueContainerFocused = isFocused;
	noFocus = !isFocused;
}

void Dashboard::focusIfDashboardClicked(Vector2i mousePosition)
{
	sf::IntRect outPutAngleContainer(outputAngleValueContainer.getPosition().x, outputAngleValueContainer.getPosition().y, outputAngleValueContainer.getGlobalBounds().width, outputAngleValueContainer.getGlobalBounds().height);
	sf::IntRect launchButtonContainer(launchButton.getPosition().x, launchButton.getPosition().y, launchButton.getGlobalBounds().width, launchButton.getGlobalBounds().height);

	if (outPutAngleContainer.contains(mousePosition)) {
		toggleFocusAllContainers(false);
		isOutputAngleValueContainerFocused = true;
	}
	else if (launchButtonContainer.contains(mousePosition)) {
		cout << "Launch button toggled!" << endl;
		toggleFocusAllContainers(false);
		isLaunchButtonFocused = true;
	}
	else {
		toggleFocusAllContainers(false);
		noFocus = true;
	}
}

void Dashboard::pushInput(double parameterValue, string parameter)
{
	if (parameter == "OutputAngle") {
		cout << "Dashboard Output angle: " << parameterValue << endl;
		outputAngleValue = parameterValue;
		outputAngleValueText.setString(to_string(parameterValue) + "deg");
		valueToBeChanged = "noFocus";
	}
}

double Dashboard::getOutputAngle()
{
	return outputAngleValue;
}

void Dashboard::endGamePopup(bool isSuccess)
{
	disableGamePopup = false;
	isEndGamePopupOpen = true;
	if (isSuccess) {
		endGameTxt.setColor(successColor);
		endGameTxt.setString("Success!");
	}
	else {
		endGameTxt.setString("Launch failed :(");
		endGameTxt.setColor(successColor);
	}
}

void Dashboard::closeGamePopup() {
	isEndGamePopupOpen = false;
	disableGamePopup = true;
}


