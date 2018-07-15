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
	sf::IntRect scWetMassContainer(outputAngleValueContainer.getPosition().x, outputAngleValueContainer.getPosition().y, outputAngleValueContainer.getGlobalBounds().width, outputAngleValueContainer.getGlobalBounds().height);

	if (scWetMassContainer.contains(mousePosition)) {
		toggleFocusAllContainers(false);
		isOutputAngleValueContainerFocused = true;
	}
	else {
		toggleFocusAllContainers(false);
		noFocus = true;
	}
}

void Dashboard::pushInput(int parameterValue, string parameter)
{
	if (parameter == "OutputAngle") {
		outputAngleValue = parameterValue;
		outputAngleValueText.setString(to_string(parameterValue) + "deg");
		valueToBeChanged = "noFocus";
	}
}

int Dashboard::getOutputAngle()
{
	return outputAngleValue;
}


