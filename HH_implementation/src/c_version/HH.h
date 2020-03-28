#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>


double In_current(double t,double I,int tot,double Periodicity){
	double I_0=I;  //Amplitude of impulse
	double T=Periodicity;     //Periodicity
	int T_tot=tot;      //Total time of observation
	int k=T_tot/T;   //number of positive impulses on the train
	float delta_t=0.25; // duration of impulse
	for(int i=1;i<=k;i++){
		if(fabs(t-i*T)<=delta_t){
			return I_0;
		}
	}
	return 0;
};



float  vtrap( float x,float y){
	float res;
	if (fabs(x/y) < 1e-6){
		res = y*(1 - x/y/2);
	}
	else{
		res = x/(exp(x/y) - 1);
	}
	return res;
};

float G_s1(float V){return 0.51/(exp(-0.3*(V+17.))+1);};	//Hz

float G_s2(float V){
	//HZ
	float	sigma=1./15.;  //mV
	return (3.3*exp((V+35)*sigma) + exp(-(V+35)*0.05))/(1+ exp((V+35)*0.1));
};

float D_s1(float V){return .05*exp(-0.033*(V+85.));};	//Hz

float D_s2(float V){
	//HZ
	double	sigma=1./15.;  //mV
	return (3.3*exp((V+35)*sigma) + exp(-(V+35)*0.05))/(1+ exp(-(V+35)*0.1));
};

//WB
float A_n( float V){ return .01*vtrap(-(V+55.),10.); };  //kHz
float A_m(float V){ return .1 * vtrap(-(V+40.),10.);  };  //kHz


//HH
//float A_n( float V){ return .01*(V+55.)/(1-exp(-(V+55.)/10.)); };  //kHz
//float A_m(float V){ return .1 * (V+40.)/(1-exp(-(V+40.)/10.));  };  //kHz


float A_h(float V){ return .07 * exp(-(V+65.)/20.); };   //kHz

float B_n(float V){ return .125*exp(-(V+65.)/80.);  }; 
	
float B_m(float V){ return 4. * exp(-(V+65.)/18.);  };

float B_h(float V){ return 1. / (exp(-(V+35.)/10.) + 1);  };



double * HH_core(double I,double *y,double *s,double t,double Periodicity,double Tot){
	double Cm = 0.5;  // Membrane Capacitance (uF/cm^2)
	double Phi = 2.;  // Temperture factor
	double V_0=-60;  // mV Initial value
	double ENa = 50; // mV Na potential
	double EK = -77; // mV K potential
	double El = -54; // mV Leakage potential
	double gbarNa = 120; // (cm^2/kΩ) Na conductance
	double gbarK = 36; //(cm^2/kΩ) K conductance
	double gbarl = 0.3; // (cm^2/kΩ) l conductance
	double gbarm=0.01*gbarK;  


	double V=y[0];
	double 	n=y[1];
	double	m=y[2];
	double	h=y[3];
	double	s_1=s[0];
	double	s_2=s[1];
	double gNa=gbarNa*pow(m,3)*h*s_1;
	double	gK=(gbarK+gbarm*s_2)*pow(n,4);
	double gl=gbarl;
	double	INa=gNa*(V-ENa);
	double	IK=gK*(V-EK);
	double	Il=gl*(V-El);
	double	I_in=In_current(t,I,Tot,Periodicity);

	double res[6]={((1/Cm)*(I_in-(INa+IK+Il))),Phi*(A_n(V)*(1-n)-B_n(V)*n),
		Phi*(A_m(V)*(1-m)-B_m(V)*m),Phi*(A_h(V)*(1-h)-B_h(V)*h),
		D_s1(V)*(1-s_1)-G_s1(V)*s_1,D_s2(V)*(1-s_2)-G_s2(V)*s_2};
	return res;
};






