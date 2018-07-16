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
	void launchButtonToggled(bool);

public:
	String valueToBeChanged;
	void pushInput(double, string);
	double getOutputAngle();
	void endGamePopup(bool);
	void closeGamePopup();
	bool disableGamePopup;
	bool isEndGamePopupOpen;

private:

	const float VIEW_HEIGHT = 1080.0f;																				 // Define height of the window
	const float VIEW_WIDTH = 1800.0f;																				 // Define width of the window

	sf::Font font;
	int textSize = 18;

	string outputAngle;
	string outputAngleTxt = "Input launch angle: ";

	double outputAngleValue = 45.56;

	Text outputAngleText;
	Text outputAngleValueText;

	Color successColor = Color::Green;
	Color failureColor = Color::Red;
	Color textColor = Color::Red;
	Text::Style textStyle = Text::Style::Regular;

	// Equation textures
	RectangleShape rocketEquation;
	RectangleShape deltaVTransfer;
	RectangleShape thetaMoonEquation;
	RectangleShape gravityLaw;

	Texture rocketEquationTexture;
	Texture deltaVTransferTexture;
	Texture thetaMoonEquationTexture;
	Texture gravityLawTexture;

	Vector2f rocketEquationTexturePosition = Vector2f(-VIEW_WIDTH / 2 + 35.0f, 130.0f);
	Vector2f rocketEquationTextureSize = Vector2f(255.0f, 73.0f);

	Vector2f gravityLawTexturePosition = Vector2f(-VIEW_WIDTH / 2 + 35.0f, 40.0f);
	Vector2f gravityLawTextureSize = Vector2f(161.0f, 54.0f);

	Vector2f deltaVTransferTexturePosition = Vector2f(-VIEW_WIDTH / 2 + 35.0f, 340.0f);
	Vector2f deltaVTransferTextureSize = Vector2f(367.0f, 76.0f);

	Vector2f thetaMoonEquationTexturePosition = Vector2f(-VIEW_WIDTH / 2 + 35.0f, 234.0f);
	Vector2f thetaMoonEquationTextureSize = Vector2f(214.0f, 66.0f);



	// SC Wet Mass containers
	RectangleShape outputAngleTextContainer;
	RectangleShape outputAngleValueContainer;

	Vector2f outputAngleTextContainerPosition = Vector2f(-VIEW_WIDTH / 2 + 30.0f, -460.0f);
	Vector2f outputAngleTextContainerSize = Vector2f(300.0f, 60.0f);

	Vector2f outputAngleValueContainerPosition = Vector2f(-VIEW_WIDTH / 2 + 330.0f, -460.0f);
	Vector2f outputAngleValueContainerSize = Vector2f(140.0f, 60.0f);

	Vector2f outputAngleTextPosition = Vector2f(-VIEW_WIDTH / 2 + 46.0f, -444.0f);
	Vector2f outputAngleValuePosition = Vector2f(-VIEW_WIDTH / 2 + 352.0f, -444.0f);


	// Launch button 
	CircleShape launchButton;
	Text launchButtonText;
	Text::Style launchTextStyle = Text::Style::Bold;
	Color launchButtonTextColor = Color::Black;
	Color launchButtonToggledColor = Color::White;
	Color launchButtonNormalColor = Color::Red;
	

	int launchButtonTextSize = 27;

	Vector2f launchButtonPosition = Vector2f(-VIEW_WIDTH / 2 + 550.0f, -VIEW_HEIGHT / 2 + 60.0f);
	Vector2f launchButtonTextPosition = Vector2f(-VIEW_WIDTH / 2 + 568.0f, -VIEW_HEIGHT / 2 + 98.0f);
	float launchButtonRadius = 60.f;

	// End game text 
	Text endGameTxt;
	int endGameTextSize = 60;


	Vector2f endGameTextPosition = Vector2f(-130.0f, -40.0f);

	bool isLaunchButtonFocused = false;
	bool isOutputAngleValueContainerFocused = false;
	bool noFocus = true;

	void toggleFocusAllContainers(bool);
	void focusIfDashboardClicked(Vector2i);
};

