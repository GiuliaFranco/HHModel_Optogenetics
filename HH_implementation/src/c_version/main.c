#include "Integrator.h"



int main(int argc,char* argv[]){
	char * ptr;
	double T=strtod(argv[1], &ptr);   //ms periodicity
	Euler(7.9,T);

};