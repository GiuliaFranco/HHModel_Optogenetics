#ifndef __In_current_H__
#define __In_current_H__

class In_current{

public:
	double I_0;  //Amplitude of impulse
	double T;     //Periodicity
	int T_tot;      //Total time of observation
	int k;   //number of positive impulses on the train
	float delta_t=0.26303; // duration of impulse HHS
	//float delta_t=0.26303; // duration of impulse Stoc HHS
	//float delta_t=0.50303; // duration of impulse 
	In_current(double I,int tot,double Periodicity);
	double Get_current(double t);
};
#endif