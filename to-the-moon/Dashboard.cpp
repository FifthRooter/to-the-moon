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

	dummyRect.setPosition(dummyRectPosition);
	dummyRect.setSize(dummyRectSize);
	dummyRect.setOutlineColor(Color::Green);
	dummyRect.setFillColor(Color::Black);
	dummyRect.setOutlineThickness(1.0f);

	// Wet Mass text setup
	scWetMassText.setFont(font);
	scWetMassText.setString(scWetMassTxt);
	scWetMassText.setPosition(scWetMassTextPosition);

	scWetMassText.setCharacterSize(textSize);
	scWetMassText.setStyle(textStyle);
	scWetMassText.setFillColor(textColor);

	// Wet Mass value setup
	scWetMassValueText.setFont(font);
	scWetMassValueText.setString(to_string(scWetMassValue) + "kg");
	scWetMassValueText.setPosition(scWetMassValuePosition);

	scWetMassValueText.setCharacterSize(textSize);
	scWetMassValueText.setStyle(textStyle);
	scWetMassValueText.setFillColor(textColor);



	// SC-Lunar Surface Distance text setup
	scLunarSurfaceDistanceText.setFont(font);
	scLunarSurfaceDistanceText.setString(scLunarSurfaceDistanceTxt);
	scLunarSurfaceDistanceText.setPosition(scLunarSurfaceDistanceTextPosition);

	scLunarSurfaceDistanceText.setCharacterSize(textSize);
	scLunarSurfaceDistanceText.setStyle(textStyle);
	scLunarSurfaceDistanceText.setFillColor(textColor);

	// SC-Lunar Surface Distance value setup
	scLunarSurfaceDistanceValueText.setFont(font);
	scLunarSurfaceDistanceValueText.setString(to_string(scLunarSurfaceDistanceValue) + "km");
	scLunarSurfaceDistanceValueText.setPosition(scLunarSurfaceDistanceValuePosition);

	scLunarSurfaceDistanceValueText.setCharacterSize(textSize);
	scLunarSurfaceDistanceValueText.setStyle(textStyle);
	scLunarSurfaceDistanceValueText.setFillColor(textColor);



	// LLO Height text setup
	lloHeightText.setFont(font);
	lloHeightText.setString(lloHeightTxt);
	lloHeightText.setPosition(lloHeightTextPosition);

	lloHeightText.setCharacterSize(textSize);
	lloHeightText.setStyle(textStyle);
	lloHeightText.setFillColor(textColor);

	// LLO Height value setup
	lloHeightValueText.setFont(font);
	lloHeightValueText.setString(to_string(lloHeightValue) + "km");
	lloHeightValueText.setPosition(lloHeightValuePosition);

	lloHeightValueText.setCharacterSize(textSize);
	lloHeightValueText.setStyle(textStyle);
	lloHeightValueText.setFillColor(textColor);



	// SC Wet Mass container setup
	scWetMassTextContainer.setPosition(scWetMassTextContainerPosition);
	scWetMassTextContainer.setSize(scWetMassTextContainerSize);
	scWetMassTextContainer.setOutlineColor(Color::White);
	scWetMassTextContainer.setOutlineThickness(2.0f);

	scWetMassValueContainer.setPosition(scWetMassValueContainerPosition);
	scWetMassValueContainer.setSize(scWetMassValueContainerSize);
	scWetMassValueContainer.setOutlineColor(Color::White);
	scWetMassValueContainer.setOutlineThickness(2.0f);

	scWetMassTextContainer.setFillColor(sf::Color::Transparent);
	scWetMassValueContainer.setFillColor(sf::Color::Transparent);


	// SC-Lunar surface distance container setup
	scLunarSurfaceDistanceTextContainer.setPosition(scLunarSurfaceDistanceTextContainerPosition);
	scLunarSurfaceDistanceTextContainer.setSize(scLunarSurfaceDistanceTextContainerSize);
	scLunarSurfaceDistanceTextContainer.setOutlineColor(Color::White);
	scLunarSurfaceDistanceTextContainer.setOutlineThickness(2.0f);

	scLunarSurfaceDistanceValueContainer.setPosition(scLunarSurfaceDistanceValueContainerPosition);
	scLunarSurfaceDistanceValueContainer.setSize(scLunarSurfaceDistanceValueContainerSize);
	scLunarSurfaceDistanceValueContainer.setOutlineColor(Color::White);
	scLunarSurfaceDistanceValueContainer.setOutlineThickness(2.0f);

	scLunarSurfaceDistanceTextContainer.setFillColor(sf::Color::Transparent);
	scLunarSurfaceDistanceValueContainer.setFillColor(sf::Color::Transparent);


	// LLO Height container setup
	lloHeightTextContainer.setPosition(lloHeightTextContainerPosition);
	lloHeightTextContainer.setSize(lloHeightTextContainerSize);
	lloHeightTextContainer.setOutlineColor(Color::White);
	lloHeightTextContainer.setOutlineThickness(2.0f);

	lloHeightValueContainer.setPosition(lloHeightValueContainerPosition);
	lloHeightValueContainer.setSize(lloHeightValueContainerSize);
	lloHeightValueContainer.setOutlineColor(Color::White);
	lloHeightValueContainer.setOutlineThickness(2.0f);

	lloHeightTextContainer.setFillColor(sf::Color::Transparent);
	lloHeightValueContainer.setFillColor(sf::Color::Transparent);



	// Is container focused booleans
	isSCLunarSurfaceDistanceValueContainerFocused = false;
	isSCWetMassValueContainerFocused = false;
	isLLOHeightValueContainerFocused = false;
	noFocus = true;
}


Dashboard::~Dashboard()
{
}

String Dashboard::Update(Vector2i& mousePosition, RenderWindow& window)
{
	focusIfDashboardClicked(mousePosition);
	//cout << "Mouse X position" << mousePosition.x << endl;
	//cout << "Mouse Y position" << mousePosition.y << endl;
	if (isSCWetMassValueContainerFocused) {
		valueToBeChanged = "SCWetMass";
		scWetMassValueText.setString(scWetMass + "kg");
		toggleFocusAllContainers(false);
	}
	else if (isSCLunarSurfaceDistanceValueContainerFocused) {
		valueToBeChanged = "SCLunarSurfaceDistance";
		scLunarSurfaceDistanceValueText.setString(scLunarSurfaceDistance + "km");
		toggleFocusAllContainers(false);
	}
	else if (isLLOHeightValueContainerFocused) {
		valueToBeChanged = "LLOHeight";
		lloHeightValueText.setString(lloHeight + "km");
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
	//window.draw(dummyRect);
	window.draw(thetaMoonEquation);
	window.draw(gravityLaw);
	window.draw(deltaVTransfer);
	window.draw(rocketEquation);
	window.draw(scWetMassText);
	window.draw(scLunarSurfaceDistanceText);
	window.draw(lloHeightText);
	window.draw(scWetMassValueText);
	window.draw(scLunarSurfaceDistanceValueText);
	window.draw(lloHeightValueText);
	window.draw(scLunarSurfaceDistanceTextContainer);
	window.draw(scLunarSurfaceDistanceValueContainer);
	window.draw(lloHeightTextContainer);
	window.draw(lloHeightValueContainer);
	window.draw(scWetMassTextContainer);
	window.draw(scWetMassValueContainer);
}

void Dashboard::updatePositions(Vector2u & resizedWindowDimensions)
{
	VIEW_HEIGHT = resizedWindowDimensions.y;																				 // Define height of the window
	VIEW_WIDTH = resizedWindowDimensions.x;																					// Define width of the window

	rocketEquationTexturePosition.x = -VIEW_WIDTH / 2 + 212.0f;
	rocketEquationTexturePosition.y = VIEW_HEIGHT / 2 - 257.0f;

	gravityLawTexturePosition.x = -VIEW_WIDTH / 2 + 35.0f;
	gravityLawTexturePosition.y = VIEW_HEIGHT / 2 - 307.0f;

	deltaVTransferTexturePosition.x = -VIEW_WIDTH / 2 + 100.0f;
	deltaVTransferTexturePosition.y = VIEW_HEIGHT / 2 - 100.0f; 

	thetaMoonEquationTexturePosition.x = -VIEW_WIDTH / 2 + 35.0f;
	thetaMoonEquationTexturePosition.y = VIEW_HEIGHT / 2 - 186.0f;



	scWetMassTextContainerPosition.x = -VIEW_WIDTH / 2 + 30.0f;
	scWetMassTextContainerPosition.y = -VIEW_HEIGHT / 2 + 30.0f;

	scWetMassValueContainerPosition.x = -VIEW_WIDTH / 2 + 330.0f;
	scWetMassValueContainerPosition.y = -VIEW_HEIGHT / 2 + 30.0f;

	scWetMassTextPosition.x = -VIEW_WIDTH / 2 + 46.0f;
	scWetMassTextPosition.y = -VIEW_HEIGHT / 2 + 46.0f;

	scWetMassValuePosition.x = -VIEW_WIDTH / 2 + 355.0f;
	scWetMassValuePosition.y = -VIEW_HEIGHT / 2 + 46.0f;




	scLunarSurfaceDistanceTextContainerPosition.x = -VIEW_WIDTH / 2 + 30.0f;
	scLunarSurfaceDistanceTextContainerPosition.y = -VIEW_HEIGHT / 2 + 90.0f;

	scLunarSurfaceDistanceValueContainerPosition.x = -VIEW_WIDTH / 2 + 330.0f;
	scLunarSurfaceDistanceValueContainerPosition.y = -VIEW_HEIGHT / 2 + 90.0f;

	scLunarSurfaceDistanceTextPosition.x = -VIEW_WIDTH / 2 + 46.0f;
	scLunarSurfaceDistanceTextPosition.y = -VIEW_HEIGHT / 2 + 106.0f;

	scLunarSurfaceDistanceValuePosition.x = -VIEW_WIDTH / 2 + 355.0f;
	scLunarSurfaceDistanceValuePosition.y = -VIEW_HEIGHT / 2 + 106.0f;




	lloHeightTextContainerPosition.x = -VIEW_WIDTH / 2 + 30.0f;
	lloHeightTextContainerPosition.y = -VIEW_HEIGHT / 2 + 150.0f;

	lloHeightValueContainerPosition.x = -VIEW_WIDTH / 2 + 330.0f;
	lloHeightValueContainerPosition.y = -VIEW_HEIGHT / 2 + 150.0f;

	lloHeightTextPosition.x = -VIEW_WIDTH / 2 + 46.0f;
	lloHeightTextPosition.y = -VIEW_HEIGHT / 2 + 166.0f;

	lloHeightValuePosition.x = -VIEW_WIDTH / 2 + 355.0f;
	lloHeightValuePosition.y = -VIEW_HEIGHT / 2 + 166.0f;

	rocketEquation.setPosition(rocketEquationTexturePosition);
	deltaVTransfer.setPosition(deltaVTransferTexturePosition);
	gravityLaw.setPosition(gravityLawTexturePosition);
	thetaMoonEquation.setPosition(thetaMoonEquationTexturePosition);

	scWetMassText.setPosition(scWetMassTextPosition);
	scWetMassValueText.setPosition(scWetMassValuePosition);
	scWetMassTextContainer.setPosition(scWetMassTextContainerPosition);
	scWetMassValueContainer.setPosition(scWetMassValueContainerPosition);


	scLunarSurfaceDistanceText.setPosition(scLunarSurfaceDistanceTextPosition);
	scLunarSurfaceDistanceValueText.setPosition(scLunarSurfaceDistanceValuePosition);
	scLunarSurfaceDistanceTextContainer.setPosition(scLunarSurfaceDistanceTextContainerPosition);
	scLunarSurfaceDistanceValueContainer.setPosition(scLunarSurfaceDistanceValueContainerPosition);

	lloHeightText.setPosition(lloHeightTextPosition);
	lloHeightValueText.setPosition(lloHeightValuePosition);
	lloHeightTextContainer.setPosition(lloHeightTextContainerPosition);
	lloHeightValueContainer.setPosition(lloHeightValueContainerPosition);

}

void Dashboard::toggleFocusAllContainers(bool isFocused)
{
	isSCWetMassValueContainerFocused = isFocused;
	isSCLunarSurfaceDistanceValueContainerFocused = isFocused;
	isLLOHeightValueContainerFocused = isFocused;
	noFocus = !isFocused;
}

void Dashboard::focusIfDashboardClicked(Vector2i mousePosition)
{
	sf::IntRect scWetMassContainer(scWetMassValueContainer.getPosition().x, scWetMassValueContainer.getPosition().y, scWetMassValueContainer.getGlobalBounds().width, scWetMassValueContainer.getGlobalBounds().height);
	sf::IntRect scLunarSurfaceDistanceContainer(scLunarSurfaceDistanceValueContainer.getPosition().x, scLunarSurfaceDistanceValueContainer.getPosition().y, scLunarSurfaceDistanceValueContainer.getGlobalBounds().width, scLunarSurfaceDistanceValueContainer.getGlobalBounds().height);
	sf::IntRect lloHeightContainer(lloHeightValueContainer.getPosition().x, lloHeightValueContainer.getPosition().y, lloHeightValueContainer.getGlobalBounds().width, lloHeightValueContainer.getGlobalBounds().height);

	if (scWetMassContainer.contains(mousePosition)) {
		toggleFocusAllContainers(false);
		isSCWetMassValueContainerFocused = true;
	}
	else if (scLunarSurfaceDistanceContainer.contains(mousePosition)) {
		toggleFocusAllContainers(false);
		isSCLunarSurfaceDistanceValueContainerFocused = true;
	}
	else if (lloHeightContainer.contains(mousePosition)) {
		toggleFocusAllContainers(false);
		isLLOHeightValueContainerFocused = true;
	}
	else {
		toggleFocusAllContainers(false);
		noFocus = true;
	}
}

void Dashboard::pushInput(int parameterValue, string parameter)
{
	if (parameter == "SCWetMass") {
		scWetMassValue = parameterValue;
		scWetMassValueText.setString(to_string(parameterValue) + "kg");
		valueToBeChanged = "noFocus";
	}
	else if (parameter == "SCLunarSurfaceDistance") {
		scLunarSurfaceDistanceValue = parameterValue;
		scLunarSurfaceDistanceValueText.setString(to_string(parameterValue) + "km");
		valueToBeChanged = "noFocus";
	}
	else if (parameter == "LLOHeight") {
		lloHeightValue = parameterValue;
		lloHeightValueText.setString(to_string(parameterValue) + "km");
		valueToBeChanged = "noFocus";
	}
}


