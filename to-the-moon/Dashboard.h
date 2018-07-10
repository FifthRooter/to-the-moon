#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class Dashboard
{
public:
	Dashboard();
	~Dashboard();

	void Update(Vector2i& mousePosition);
	void Draw(sf::RenderWindow& window);

private:
	sf::Font font;
	int textSize = 20;
	string dummyText = "000km";

	string scWetMassTxt = "SC Wet Mass: ";
	string scLunarSurfaceDistanceTxt = "SC-Lunar Surface Distance: ";
	string lloHeightTxt = "LLO Height: ";

	string scWetMassValue = "2200kg";
	string scLunarSurfaceDistanceValue = "100km";
	string lloHeightValue = "20km";

	Text scWetMassText;
	Text scLunarSurfaceDistanceText;
	Text lloHeightText;

	Text scWetMassValueText;
	Text scLunarSurfaceDistanceValueText;
	Text lloHeightValueText;
	

	Color textColor = sf::Color::Red;
	Text::Style textStyle = sf::Text::Style::Regular;

	// Dashboard container
	RectangleShape container;
	Vector2f containerPosition = sf::Vector2f(-450.0f, -420.0f);
	Vector2f containerSize = sf::Vector2f(400.0f, 180.0f);

	// SC Wet Mass containers
	RectangleShape scWetMassTextContainer;
	RectangleShape scWetMassValueContainer;

	Vector2f scWetMassTextContainerPosition = sf::Vector2f(-670.0f, -420.0f);
	Vector2f scWetMassTextContainerSize = sf::Vector2f(300.0f, 60.0f);

	Vector2f scWetMassValueContainerPosition = sf::Vector2f(-370.0f, -420.0f);
	Vector2f scWetMassValueContainerSize = sf::Vector2f(100.0f, 60.0f);

	Vector2f scWetMassTextPosition = sf::Vector2f(-664.0f, -409.0f);
	Vector2f scWetMassValuePosition = sf::Vector2f(-345.0f, -409.0f);


	// SC-Lunar Surface Distance containers
	RectangleShape scLunarSurfaceDistanceTextContainer;
	RectangleShape scLunarSurfaceDistanceValueContainer;

	Vector2f scLunarSurfaceDistanceTextContainerPosition = sf::Vector2f(-670.0f, -360.0f);
	Vector2f scLunarSurfaceDistanceTextContainerSize = sf::Vector2f(300.0f, 60.0f);

	Vector2f scLunarSurfaceDistanceValueContainerPosition = sf::Vector2f(-370.0f, -360.0f);
	Vector2f scLunarSurfaceDistanceValueContainerSize = sf::Vector2f(100.0f, 60.0f);

	Vector2f scLunarSurfaceDistanceTextPosition = sf::Vector2f(-664.0f, -349.0f);
	Vector2f scLunarSurfaceDistanceValuePosition = sf::Vector2f(-345.0f, -349.0f);

	// LLO Height containers
	RectangleShape lloHeightTextContainer;
	RectangleShape lloHeightValueContainer;

	Vector2f lloHeightTextContainerPosition = sf::Vector2f(-670.0f, -300.0f);
	Vector2f lloHeightTextContainerSize = sf::Vector2f(300.0f, 60.0f);

	Vector2f lloHeightValueContainerPosition = sf::Vector2f(-370.0f, -300.0f);
	Vector2f lloHeightValueContainerSize = sf::Vector2f(100.0f, 60.0f);

	Vector2f lloHeightTextPosition = sf::Vector2f(-664.0f, -289.0f);
	Vector2f lloHeightValuePosition = sf::Vector2f(-345.0f, -289.0f);


	int containerBorderThickness;

	bool isSCWetMassValueContainerFocused = false;
	bool isSCLunarSurfaceDistanceValueContainerFocused = false;
	bool isLLOHeightValueContainerFocused = false;
	bool noFocus = true;

	void toggleFocusAllContainers(bool);
	void focusIfDashboardClicked(Vector2i);
};

