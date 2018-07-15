#include "stdafx.h"
#include "Physics.h"

Physics::Physics()
{
}

Physics::~Physics()
{
}

float Physics::getEarthMoonDistance()
{
	return distanceEarthSC;
}

Vector2f Physics::getSCCoordinates() {
	return scCoordinates;
}
