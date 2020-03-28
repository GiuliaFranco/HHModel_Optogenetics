#include "In_current.h"
#include <cmath>


In_current :: In_current(double I,int tot,double Periodicity){
	I_0=I;  
	T=Periodicity;   
	T_tot=tot;  
	k=T_tot/T; 

};

double In_current :: Get_current(double t){
	for(int i=1;i<=k;i++){
		if(fabs(t-i*T)<=delta_t){
			return I_0;
		}
	}
	return 0;
};
