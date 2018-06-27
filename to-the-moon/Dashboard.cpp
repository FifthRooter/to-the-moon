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

	// Container setup
	container.setSize(containerSize);
	container.setPosition(containerPosition);
	container.setFillColor(sf::Color::Transparent);



	// Wet Mass text setup
	scWetMassText.setFont(font);
	scWetMassText.setString(scWetMassTxt);
	scWetMassText.setPosition(scWetMassTextPosition);

	scWetMassText.setCharacterSize(textSize);
	scWetMassText.setStyle(textStyle);
	scWetMassText.setFillColor(textColor);

	// Wet Mass value setup
	scWetMassValueText.setFont(font);
	scWetMassValueText.setString(scWetMassValue);
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

	// SC-Lunar Surface Distance text setup
	scLunarSurfaceDistanceValueText.setFont(font);
	scLunarSurfaceDistanceValueText.setString(scLunarSurfaceDistanceValue);
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

	// LLO Height text setup
	lloHeightValueText.setFont(font);
	lloHeightValueText.setString(lloHeightValue);
	lloHeightValueText.setPosition(lloHeightValuePosition);

	lloHeightValueText.setCharacterSize(textSize);
	lloHeightValueText.setStyle(textStyle);
	lloHeightValueText.setFillColor(textColor);



	// SC Wet Mass container setup
	scWetMassTextContainer.setPosition(scWetMassTextContainerPosition);
	scWetMassTextContainer.setSize(scWetMassTextContainerSize);

	scWetMassValueContainer.setPosition(scWetMassValueContainerPosition);
	scWetMassValueContainer.setSize(scWetMassValueContainerSize);

	scWetMassTextContainer.setFillColor(sf::Color::Transparent);
	scWetMassValueContainer.setFillColor(sf::Color::Transparent);


	// SC-Lunar surface distance container setup
	scLunarSurfaceDistanceTextContainer.setPosition(scLunarSurfaceDistanceTextContainerPosition);
	scLunarSurfaceDistanceTextContainer.setSize(scLunarSurfaceDistanceTextContainerSize);

	scLunarSurfaceDistanceValueContainer.setPosition(scLunarSurfaceDistanceTextContainerPosition);
	scLunarSurfaceDistanceValueContainer.setSize(scLunarSurfaceDistanceTextContainerSize);

	scLunarSurfaceDistanceTextContainer.setFillColor(sf::Color::Transparent);
	scLunarSurfaceDistanceValueContainer.setFillColor(sf::Color::Transparent);


	// LLO Height container setup
	lloHeightTextContainer.setPosition(lloHeightTextContainerPosition);
	lloHeightTextContainer.setSize(lloHeightTextContainerSize);

	lloHeightValueContainer.setPosition(lloHeightValueContainerPosition);
	lloHeightValueContainer.setSize(lloHeightValueContainerSize);

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

void Dashboard::Update(Vector2i& mousePosition)
{
	focusIfDashboardClicked(mousePosition);
	cout << "Mouse X position" << mousePosition.x << endl;
	cout << "Mouse Y position" << mousePosition.y << endl;
	if (isSCWetMassValueContainerFocused) {
		cout << "Wet mass value container clicked!" << endl;
		scWetMassValueText.setString(dummyText);
		toggleFocusAllContainers(false);
	}
	else if (isSCLunarSurfaceDistanceValueContainerFocused) {
		cout << "SC-Lunar surface distance value container clicked!" << endl;
		scLunarSurfaceDistanceValueText.setString(dummyText);
		toggleFocusAllContainers(false);
	}
	else if (isLLOHeightValueContainerFocused) {
		cout << "LLO Height value container clicked!" << endl;
		lloHeightValueText.setString(dummyText);
		toggleFocusAllContainers(false);
	}
	else if (noFocus) {
		cout << "No container focused!" << endl;
		toggleFocusAllContainers(false);
	}

}

void Dashboard::Draw(RenderWindow & window, sf::Text& textOther)
{
	//window.draw(container);
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

