#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iostream>


using namespace std;
using namespace sf;

class Dashboard
{
public:
	Dashboard();
	~Dashboard();

	String Update(Vector2i& mousePosition, RenderWindow& window);
	void Draw(sf::RenderWindow& window);

public:
	String valueToBeChanged;
	void pushInput(int, string);

private:

	sf::Font font;
	int textSize = 20;

	string scWetMass;
	string scLunarSurfaceDistance;
	string lloHeight;

	string scWetMassTxt = "SC Wet Mass: ";
	string scLunarSurfaceDistanceTxt = "SC-Lunar Surface Distance: ";
	string lloHeightTxt = "LLO Height: ";

	int scWetMassValue = 1234;
	int scLunarSurfaceDistanceValue = 1111;
	int lloHeightValue = 4321;

	Text scWetMassText;
	Text scLunarSurfaceDistanceText;
	Text lloHeightText;

	Text scWetMassValueText;
	Text scLunarSurfaceDistanceValueText;
	Text lloHeightValueText;
	

	Color textColor = sf::Color::Red;
	Text::Style textStyle = sf::Text::Style::Regular;

	// Equation textures
	RectangleShape rocketEquation;
	RectangleShape deltaVTransfer;
	RectangleShape thetaMoonEquation;
	RectangleShape gravityLaw;

	RectangleShape dummyRect;
	Vector2f dummyRectPosition = Vector2f(-200.0f, -200.0f);
	Vector2f dummyRectSize = Vector2f(70.0f, 70.0f);

	Texture rocketEquationTexture;
	Texture deltaVTransferTexture;
	Texture thetaMoonEquationTexture;
	Texture gravityLawTexture;

	Vector2f rocketEquationTexturePosition = Vector2f(-200.0f, -440.0f);
	Vector2f rocketEquationTextureSize = Vector2f(255.0f, 73.0f);

	Vector2f gravityLawTexturePosition = Vector2f(-156.0f, -298.0f);
	Vector2f gravityLawTextureSize = Vector2f(161.0f, 54.0f);

	Vector2f deltaVTransferTexturePosition = Vector2f(115.0f, -440.0f);
	Vector2f deltaVTransferTextureSize = Vector2f(367.0f, 76.0f);

	Vector2f thetaMoonEquationTexturePosition = Vector2f(190.0f, -304.0f);
	Vector2f thetaMoonEquationTextureSize = Vector2f(214.0f, 66.0f);



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


	bool isSCWetMassValueContainerFocused = false;
	bool isSCLunarSurfaceDistanceValueContainerFocused = false;
	bool isLLOHeightValueContainerFocused = false;
	bool noFocus = true;

	void toggleFocusAllContainers(bool);
	void focusIfDashboardClicked(Vector2i);
};

