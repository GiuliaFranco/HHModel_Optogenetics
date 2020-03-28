#include "Integrator.h"



int main(int argc,char* argv[]){
	char * ptr;
	char * ptr1;
	double T=strtod(argv[1], &ptr);   //ms periodicity
	double I=strtod(argv[2], &ptr1);
	Euler(I,T);

};