#include "Integrator.h"
#include "Stoch_Integrator.h"
#include "Statistics.h"
#include <iostream>
#include <thread> 
#include <cstdlib> 
#include <random>

using namespace std;
void GetnumSpikes(double T,double I){
	for(int i=0;i<10;i++){
	Solver * solv=new Solver(I,T);
	solv->Euler();
	Stat * calc=new Stat(I,solv->T,solv->num,solv->t,solv->Period,solv->V,solv->s1);
	cout<<calc->Peak()<<endl;
	}
};



int main(int argc,char* argv[]){
	double T=atof(argv[1]);   //ms periodicity
	double I=atof(argv[2]);
	/*thread th1(GetnumSpikes, T,I); 
	thread th2(GetnumSpikes, T,I); 
	thread th3(GetnumSpikes, T,I); 
	thread th4(GetnumSpikes, T,I); 
	th1.join();
	th2.join();
	th3.join();
	th4.join();*/
	Solver_Stoch * solv=new Solver_Stoch(I,T);

	solv->Euler_Guller();
	//solv->Predictor_Corrector();
	//solv->Runge_Kutta();
	Stat * calc=new Stat(I,solv->T,solv->num,solv->t,solv->Period,solv->V,solv->s1);
	//calc->Mean_Firing_rate();
	/*for(int s=1;s<=42;s+=5){
	//	solv->Period=1000/s;
		Solver * solv=new Solver(I,1000/s);
		solv->Euler();
		Stat * calc=new Stat(I,solv->T,solv->num,solv->t,solv->Period,solv->V,solv->s1);
		cout<<calc->Mean_Firing_rate()<<" "<<s<<endl;
		//calc->Latency();
		//cout<<" "<<s<<endl;
		//free(calc);
	}*/
	//calc->I_vect();
	//calc->Mean_s();
	//calc->Latency();
	//calc->Peak();
	
	/*for(int s=0;s<=15;s++){
		solv->model->s1_const=1;
		solv->Euler();
		solv->Temporal_Integral("gamma",1);
	}*/
	//free(solv);

};