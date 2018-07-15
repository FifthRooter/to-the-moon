#pragma once
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

using namespace sf;

class Physics
{
public:
	Physics();
	~Physics();
	float getEarthMoonDistance();
	Vector2f getSCCoordinates();

private:

	double angle = M_PI;
	int R_PERIGEE; // Or SC_LEO_ALT
	int R_APOGEE; // Or MOON_EARTH_DISTANCE
	int GRAVIT_ACCEL = 9.80665; // gravitational acceleration
	int I_Sp; // Specific impulse

	float eccentricity = (R_PERIGEE - R_APOGEE) / (R_PERIGEE + R_APOGEE);
	float velocityCp = sqrtf(MU_EARTH / R_PERIGEE);
	float deltaVp = velocityCp * (sqrtf(1+eccentricity) - 1) ; // to enter E-M Hohmann transfer orbit, this change in velocity required
	float MU_EARTH = 3.98600441*1e+14; 
	float MU_MOON = 4.9048695*1e+12; 
	float distanceEarthSC = 384400; //km

	float massDry;
	float massProp;
	float massTotal = massDry + massProp;
	float deltaV = I_Sp * GRAVIT_ACCEL * log(massTotal / massDry);

	Vector2f forceEarthOnSC;
	Vector2f forceMoonOnSC;

	Vector2i earthCoordinates;

	float thetaMoon;
	float thetaMoonPrevious;
	Vector2i moonCoordinates;
	Vector2i moonCoordinatePrevious;
	Vector2i deltaMoonCoordinates;

	Vector2f scCoordinates;
	Vector2f scCoordinatesPrevious;
	Vector2i deltaSCCoordinates;
};

