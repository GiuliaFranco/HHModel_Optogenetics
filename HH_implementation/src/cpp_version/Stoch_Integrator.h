#ifndef __Stoch_Integrator_H__
#define __Stoch_Integrator_H__
#include "HH.h"
#include "Stoch.h"

class Solver_Stoch{
public:
	double I0;
	double Period;
	const double dt = 0.01;  // Time steps (ms)
	const double  T = 100.;    // Total time of observations
	const double V_0= -60;
	const int num=(T/dt);
	float * V =  new float[num]; // Membrane potential list
	float * n = new float[num]; // n potential list
	float * m = new float[num];  // m potential list
	float * h = new float[num]; // h potential list
	float * s1 = new float[num];  // Slow sodium activation
	float * s2 = new float[num];  // Slow potassium activation
	float * q_Na = new float[num];  // Slow sodium activation
	float * q_K = new float[num];  // Slow potassium activation
	float * p_Na = new float[num];  // Slow sodium activation
	float * p_K = new float[num];  // Slow potassium activation
	float * t = new float[num];
	float** Chi=new float*[num+1];
	float** Psi=new float*[num+1];
	float** Chi_Orio=new float*[num+1];
	float** Psi_Orio=new float*[num+1];
	Stoch_HH * model;
	Solver_Stoch(double I,double Periodicity);
	void Update_Chi(double dt,double V,int i);
	void Update_Psi(double dt,double V,int i);
	double * Calculator_aux(double y_1,double y_2,double y_3,double y_4,double y_5,double y_6,double t);
	double * Calculator_Guler(double y_1,double y_2,double y_3,double y_4,double y_5,double y_6,double y_7,double y_8,double y_9,double t);
	double * Calculator_Orio(double y_1,double y_2,double t,float  n,float  mh);
	double * Calculator_Orio_Chi(double * Chi_up,double V);
	double * Calculator_Orio_Psi(double * Psi_up,double V);
	void Euler();
	void Euler_Orio();
	void Euler_Guller();
};

#endif