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

float * I_vect(double I0,int tot,int num,float * t,double Periodicity){
	float * current=(float*) calloc(num, sizeof(float));
	for(int i=0;i<num;i++){
		current[i]=In_current(t[i],I0,tot,Periodicity);
		//printf("%f\t  %f\n",current[i],t[i]);
	};
	return current;
};

int max_index(int n,int k,float * V){
	float * sub_V=(float*) calloc(n, sizeof(float));
	for(int j=0;j<n;j++){
		sub_V[j]=V[k+j];
	}
    if(n <= 0) return -1;
    int i, max_i = 0;
    float max = sub_V[0];
    for(i = 1; i < n; ++i){
        if(sub_V[i] > max){
            max = sub_V[i];
            max_i = i;
            }
        }
    if(max>=10) return max_i+k;
    else return 0;
    };


void Latency(double I0,int tot,int num,float * t,double Periodicity,float * V){
	float * current=I_vect(I0,tot,num,t,Periodicity);
	double delta=0.25;
	int k=tot/Periodicity;
	int sub=(Periodicity-delta)*100;
	int sub1=(Periodicity-delta)*100;
	for(int i=1;i<=k;i++){
		float current_time=t[sub1-1];
		int V_indx=max_index(sub,sub1,V);
		if(V_indx!=0){
			float V_time=t[V_indx];
			printf("%f\t %f\n",fabs(V_time-current_time),t[sub1-1]/1000);
		}
		sub1+=Periodicity*100;
	};
};