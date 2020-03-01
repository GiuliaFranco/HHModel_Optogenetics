#include "HH.h"
#include "Statistics.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

/*
void I_vect(int I0,int tot,int num,float * t){
	float * current=(float*) calloc(num, sizeof(float));
	for(int i=0;i<num;i++){
		current[i]=In_current(t[i],I0,tot);
		printf("%f\t  %f\n",current[i],t[i]);
	};
};


void Latency(float * V,float * t,int tot,int delta,int num){
	int k=0;
	int i=0;
	int periodicity=1;
	int ktot=tot/periodicity;
	for(int k=1;k<=ktot;k++){
		for(int i=0;i<num;i++){
			if(t[i]<fabs(delta+k*periodicity) && t[i]=>fabs(delta-k*periodicity))
		}
	};
	

};*/



double * Calculator_aux(double I,double y_1,double y_2,double y_3,double y_4,double y_5,double y_6,double t,double Periodicity,double T){
	double y[4] = {y_1,y_2,y_3,y_4};
	double s[2] = {y_5,y_6};
	return HH_core(I,y,s,t,Periodicity,T);
};

void Euler(double I,double Periodicity){
	double I0=I;
	double dt = 0.01;  // Time steps (ms)
	double  T = 20000.;    // Total time of observations
	double V_0= -60;
	//double t = np.arange(self.T_start, self.T,self.dt).tolist()  # Range Time for the stimulation (ms)
	int num=(T/dt);
	float * t =  (float*) calloc(num, sizeof(float)); 
	t[0]=0;
	double start = 0;
	for(int i=0;i<=num;i++){ 
		start+=dt;
		t[i]=start; 
	};

	//Latency(I0,T,num,t);
	float * V =  (float*) calloc(num, sizeof(float)); // Membrane potential list
	float * n = (float*) calloc(num, sizeof(float)); // n potential list
	float * m =  (float*) calloc(num, sizeof(float));  // m potential list
	float * h = (float*) calloc(num, sizeof(float));  // h potential list
	float * s1 =  (float*) calloc(num, sizeof(float)); // Slow sodium activation
	float * s2 =  (float*) calloc(num, sizeof(float));


	//Initialization 
	V[0]=V_0;
	m[0]=A_m(V[0])/(A_m(V[0])+B_m(V[0]));
	n[0]=A_n(V[0])/(A_n(V[0])+B_n(V[0]));
	h[0]=A_h(V[0])/(A_h(V[0])+B_h(V[0]));
	//s1[0]=1;
	s2[0]=0;
	s1[0]=D_s1(V[0])/(D_s1(V[0])+G_s1(V[0]));
	//s2[0]=D_s2(V[0])/(D_s2(V[0])+G_s2(V[0]));
	
	//Euler Forward

	printf("%f\t %f\t %f\t %f\t %f\t %f\t %f\n",V[0],n[0],m[0],h[0],s1[0],s2[0],t[0]);
	//printf("%f\t  %f\n",s1[0],t[0]);
	for(int i=1;i<=num;i++){
		double * K_1=Calculator_aux(I0,V[i-1],n[i-1],m[i-1],h[i-1],s1[i-1],s2[i-1],t[i-1],Periodicity,T);
		V[i]=(V[i-1]+K_1[0]*dt);
		n[i]=(n[i-1] +K_1[1]*dt);
		m[i]=(m[i-1] + K_1[2]*dt);
		h[i]=(h[i-1]+K_1[3]*dt);
		//s1[i]=1;
		s2[i]=0;
		//printf("%f\t  %f\n",V[i],t[i]);
		s1[i]=(s1[i-1]+K_1[4]*dt);
		//s2[i]=(s2[i-1]+K_1[5]*dt);
		printf("%f\t %f\t %f\t %f\t %f\t %f\t %f\n",V[i],n[i],m[i],h[i],s1[i],s2[i],t[i]);
		//printf("%f\t  %f\n",s1[i],t[i]);
		//free(K_1);
	};

	Mean(t,s1,(int) T);

	free(t);
	free(V);
	free(m);
	free(n);
	free(h);
	free(s1);
	free(s2);
		
	//return V;	*/
};