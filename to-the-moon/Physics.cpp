#include "stdafx.h"
#include "Physics.h"
#include "Dashboard.h"
#include <fstream>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

bool success = 0;

vector< state_type> do_physics( double angle) {

	// Write output to file
	ofstream outfile;
	outfile.open("file.txt", ofstream::out);

	// State initialization
	state_type x;
	x[0] = -0.0017295;			// Moon initial x-position, in AU
	x[1] = 0.00043495;			// Moon initial x-velocity, in AU/day
	x[2] = -0.0018849;			// Moon initial y-position, in AU
	x[3] = -0.0003173;			// Moon initial y-velocity, in AU/day
	x[4] = -3.0144939e-5;		// Spacecraft initial x-position, in AU
	x[5] = -v * sin(angle);		// Spacecraft initial x-velocity, in AU/day
	x[6] = -3.2851355e-5;		// Spacecraft initial y-position, in AU
	x[7] = -v * cos(angle);		// Spacecraft initial y-velocity, in AU/day


	System sys(G, m_E, m_M, m_SC);
	vector< state_type > x_vec;
	vector< double > times;

	// Do the simulation
	runge_kutta4< state_type > stepper;
	size_t steps = integrate_const(stepper, sys, x, 0.0, 1.0, 0.0007, push_back_state_and_time(x_vec, times));

	// Desired distance from moon
	double range = 1.29480452e-5;

	// Write the results of the simulation to the external file, and check whether the spacecraft reached the moon
	for (size_t i = 0; i <= steps; i++)
	{
		if (sqrt(pow(x_vec[i][0] - x_vec[i][4], 2) + pow(x_vec[i][2] - x_vec[i][6], 2)) <= range)
		{
			bool success = 1;
			break;
		}
		outfile << to_string(times[i]);
		for (size_t j = 0; j < dims; j++)
		{
			outfile << ',' << to_string(x_vec[i][j]);
		}
		outfile << ',' << to_string(sqrt(pow(x_vec[i][0] - x_vec[i][4], 2) + pow(x_vec[i][2] - x_vec[i][6], 2))) << '\n';

	}

	// Return the Moon and spacecraft coordinates from the simulation
	return x_vec;
}
