#include "stdafx.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <boost/numeric/odeint.hpp>
#include <vector>
#include <boost/array.hpp>

using namespace std;
using namespace boost::numeric::odeint;

const size_t dims = 8;						// Number of variables in the state

typedef array<double, dims> state_type;		// Array of size dims to store state

const double G = 2.95912208286e-4;			// Gravitational constant in km^3 solar_mass^-1 day^-1
const double m_E = 3.0035e-6;				// Earth mass in solar masses
const double m_M = 3.6923e-8;				// Moon mass in solar masses
const double m_SC = 1.1064e-27;				// Spacecraft total mass in solar masses
const double v = 0.007093217471;			// Spacecraft launch velocity in AU/day
extern bool success;						// To indicate whether the moon was reached

class System {

	double m_G;		// Gravitational constant
	double m_M_E;	// Earth mass
	double m_M_M;	// Moon mass
	double m_M_SC;	// Spacecraft mass

public:
	System(double G, double m_E, double m_M, double m_SC) : m_G(G), m_M_E(m_E), m_M_M(m_M), m_M_SC(m_SC) { }

	void operator() (const state_type &x, state_type &dxdt, const double /* t */)
	{
		dxdt[0] = x[1];
		dxdt[1] = -m_G * m_M_E * x[0] / pow((pow(x[0], 2) + pow(x[2], 2)), 1.5);
		dxdt[2] = x[3];
		dxdt[3] = -m_G * m_M_E * x[2] / pow((pow(x[0], 2) + pow(x[2], 2)), 1.5);
		dxdt[4] = x[5];
		dxdt[5] = -m_G * m_M_E * x[4] / pow((pow(x[4], 2) + pow(x[6], 2)), 1.5) - m_G * m_M_M * (x[4] - x[0]) / pow(pow(x[4] - x[0], 2) + pow(x[6] - x[4], 2), 1.5);
		dxdt[6] = x[7];
		dxdt[7] = -m_G * m_M_E * x[6] / pow((pow(x[4], 2) + pow(x[6], 2)), 1.5) - m_G * m_M_M * (x[6] - x[2]) / pow(pow(x[4] - x[0], 2) + pow(x[6] - x[4], 2), 1.5);
	}
};

// Observer
struct push_back_state_and_time
{
	vector< state_type >& m_states;
	vector< double >& m_times;

	push_back_state_and_time(vector< state_type > &states, vector< double > &times)
		: m_states(states), m_times(times) { }

	void operator()(const state_type &x, double t)
	{
		m_states.push_back(x);
		m_times.push_back(t);
	}
};

vector< state_type> do_physics( double );
