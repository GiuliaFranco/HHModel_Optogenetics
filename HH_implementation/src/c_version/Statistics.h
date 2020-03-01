#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>


void Mean(float * t, float * s,int T){
	int tot_sec=T/1000.;
	int tot_val=T*100/tot_sec;    
	printf("%f\t  %d\n",s[0],0);
	for(int i=0;i<tot_sec;i++){
		float sum=0;
		for(int k=0;k<tot_val;k++){
			sum+=s[k+i*tot_val];
		}
		printf("%f\t  %d\n",sum/tot_val,i+1);
	};

};