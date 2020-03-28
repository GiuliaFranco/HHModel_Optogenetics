#include "Stoch_Integrator.h"
#include <iostream>
#include <thread>  
#include <future>
using namespace std;

Solver_Stoch :: Solver_Stoch(double I,double Periodicity){
	I0=I;
	Period=Periodicity;
	model=new Stoch_HH(I0,Period,T,4);
	t[0]=0;
	double start = 0;
	for(int i=0;i<=num;i++){ 
		start+=dt;
		t[i]=start; 
	};
	
	V[0]=V_0;
	m[0]=model->constants->A_m(V[0])/(model->constants->A_m(V[0])+model->constants->B_m(V[0]));
	n[0]=model->constants->A_n(V[0])/(model->constants->A_n(V[0])+model->constants->B_n(V[0]));
	h[0]=model->constants->A_h(V[0])/(model->constants->A_h(V[0])+model->constants->B_h(V[0]));
	q_Na[0] = 0;  
	q_K [0] = 0; 
	p_Na[0] = 0;  
	p_K [0] = 0; 
	for (int i = 0; i < num+1; i++){
		Chi[i] = new float[7];
		Chi_Orio[i] = new float[8];
	}
	for (int i = 0; i < num+1; i++){
		Psi[i] = new float[4];
		Psi_Orio[i] = new float[5];
	}
	for (int i = 0; i < 7; i++){
		Chi[0][i] = 0;
		Chi_Orio[0][i]=0;
	}
	Chi_Orio[0][7]=m[0]*m[0]*m[0]*h[0];
	for (int i = 0; i < 4; i++){
		Psi[0][i] =0;
		Psi_Orio[0][i] =0;
	}
	Psi_Orio[0][4] =n[0]*n[0]*n[0]*n[0];
	if(model->eps!=0 && model->mode!=3){
		s2[0]=model->constants->D_s2(V[0])/(model->constants->D_s2(V[0])+model->constants->G_s2(V[0]));
		s1[0]=model->constants->D_s1(V[0])/(model->constants->D_s1(V[0])+model->constants->G_s1(V[0]));

		model->s1_init=s1[0];
	}
	if(model->eps!=0 && model->mode==3){
		s2[0]=model->constants->G_s2(V[0])/(model->constants->G_s2(V[0])+model->constants->D_s2(V[0]));
		s1[0]=model->constants->D_s1(V[0])/(model->constants->D_s1(V[0])+model->constants->G_s1(V[0]));
	}
	if(model->eps==0){
		s1[0]=model->s1_const;
		s2[0]=model->s2_const;
	}

};


void Solver_Stoch :: Update_Chi(double dt,double V,int i){
	this->Chi[i][0]=model->Update_Chi_0(dt,V,this->Chi[i-1][0]);
	this->Chi[i][1]=model->Update_Chi_1(dt,V,this->Chi[i-1][1]);
	this->Chi[i][2]=model->Update_Chi_2(dt,V,this->Chi[i-1][2]);
	this->Chi[i][3]=model->Update_Chi_3(dt,V,this->Chi[i-1][3]);
	this->Chi[i][4]=model->Update_Chi_4(dt,V,this->Chi[i-1][4]);
	this->Chi[i][5]=model->Update_Chi_5(dt,V,this->Chi[i-1][5]);
	this->Chi[i][6]=model->Update_Chi_6(dt,V,this->Chi[i-1][6]);
	double Na=0;
	for(int j=0;j<7;j++){Na+=this->Chi[i][j];};
	model->Na_noise=Na;
};

void Solver_Stoch :: Update_Psi(double dt,double V,int i){
	this->Psi[i][0]=model->Update_Psi_0(dt,V,this->Psi[i-1][0]);
	this->Psi[i][1]=model->Update_Psi_1(dt,V,this->Psi[i-1][1]);
	this->Psi[i][2]=model->Update_Psi_2(dt,V,this->Psi[i-1][2]);
	this->Psi[i][3]=model->Update_Psi_3(dt,V,this->Psi[i-1][3]);
	double K=0;
	for(int j=0;j<4;j++){K+=this->Psi[i][j];};
	model->K_noise=K;
};

double * Solver_Stoch :: Calculator_aux(double y_1,double y_2,double y_3,double y_4,double y_5,double y_6,double t){
	double y[4] = {y_1,y_2,y_3,y_4};
	double s[2] = {y_5,y_6};
	return model->model_call(y,s,t);

};

double * Solver_Stoch :: Calculator_Guler(double y_1,double y_2,double y_3,double y_4,double y_5,double y_6,double y_7,double y_8,double y_9,double t){
	double y[4] = {y_1,y_2,y_3,y_4};
	double s[5] = {y_5,y_6,y_7,y_8,y_9};
	return model->model_call(y,s,t);

};

void Solver_Stoch :: Euler(){
	cout<<V[0]<<" "<<n[0]<<" "<<m[0]<<" "<<h[0]<<" "<<t[0]<<endl;
	for(int i=1;i<=num;i++){
		//this->Update_Chi(dt,this->V[i-1],i);
		//this->Update_Psi(dt,this->V[i-1],i);
		double * K_1=Calculator_aux(V[i-1],n[i-1],m[i-1],h[i-1],s1[i-1],s2[i-1],t[i-1]);
		V[i]=(V[i-1]+K_1[0]*dt);
		n[i]=(n[i-1] +K_1[1]*dt);
		//m[i]=(m[i-1] + K_1[2]*dt);
		m[i]=model->constants->A_m(V[i])/(model->constants->A_m(V[i])+model->constants->B_m(V[i]));
		h[i]=(h[i-1]+K_1[3]*dt);
		if(model->eps!=0){
			//s1[i]=model->constants->SimplifiedCBM_s1(t[i],model->s1_init);
			s1[i]=(s1[i-1]+K_1[4]*dt);
			s2[i]=(s2[i-1]+K_1[5]*dt);
		}
		else{
			s1[i]=model->s1_const;
			s2[i]=model->s2_const;
		}	
		cout<<V[i]<<" "<<n[i]<<" "<<m[i]<<" "<<h[i]<<" "<<t[i]<<endl;
	};


};


void Solver_Stoch :: Euler_Guller(){
	cout<<V[0]<<" "<<n[0]<<" "<<m[0]<<" "<<h[0]<<" "<<t[0]<<endl;
	for(int i=1;i<=num;i++){
		double * K_1=Calculator_Guler(V[i-1],n[i-1],m[i-1],h[i-1],s1[i-1],q_K[i-1],p_K[i-1],q_Na[i-1],p_Na[i-1],t[i-1]);
		V[i]=(V[i-1]+K_1[0]*dt);
		n[i]=(n[i-1] +K_1[1]*dt);
		//m[i]=(m[i-1] + K_1[2]*dt);
		m[i]=model->constants->A_m(V[i])/(model->constants->A_m(V[i])+model->constants->B_m(V[i]));
		h[i]=(h[i-1]+K_1[3]*dt);
		s1[i]=(s1[i-1]+K_1[4]*dt);
		q_K[i]=(q_K[i-1]+K_1[5]*dt);
		p_K[i]=(p_K[i-1]+K_1[6]*dt);
		q_Na[i]=(q_Na[i-1]+K_1[7]*dt);
		p_Na[i]=(p_Na[i-1]+K_1[8]*dt);
		cout<<V[i]<<" "<<n[i]<<" "<<m[i]<<" "<<h[i]<<" "<<t[i]<<endl;
	};


};

double * Solver_Stoch :: Calculator_Orio_Psi(double * Psi_up,double V){
	return model-> Update_Orio_Psi(Psi_up,V);
};

double * Solver_Stoch :: Calculator_Orio_Chi(double * Chi_up,double V){
	return model-> Update_Orio_Chi(Chi_up,V);
};

double * Solver_Stoch :: Calculator_Orio(double y_1,double y_2,double t,float  n,float  mh){
	return model->HHS_Orio(y_1,y_2, t,n,mh);
};

void Solver_Stoch :: Euler_Orio(){
	//cout<<V[0]<<" "<<t[0]<<endl;
	for(int i=1;i<=num;i++){
		double Psi_up[5] = {Psi_Orio[i-1][0],Psi_Orio[i-1][1],Psi_Orio[i-1][2],Psi_Orio[i-1][3],Psi_Orio[i-1][4]};
		double Chi_up[8] = {Chi_Orio[i-1][0],Chi_Orio[i-1][1],Chi_Orio[i-1][2],Chi_Orio[i-1][3],Chi_Orio[i-1][4],
			Chi_Orio[i-1][5],Chi_Orio[i-1][6],Chi_Orio[i-1][7]};
		double * K_2=Calculator_Orio_Psi(Psi_up,V[i-1]);
		double * K_3=Calculator_Orio_Chi(Chi_up,V[i-1]);
		double * K_1=Calculator_Orio(V[i-1],s1[i-1],t[i-1],Psi_Orio[i-1][4],Chi_Orio[i-1][7]);
		V[i]=(V[i-1]+K_1[0]*dt);
		s1[i]=(s1[i-1]+K_1[1]*dt);
		for(int j=0;j<5;j++){ Psi_Orio[i][j]=Psi_Orio[i-1][j]+K_2[j]*dt;}
		for(int j=0;j<8;j++){ Chi_Orio[i][j]=Chi_Orio[i-1][j]+K_3[j]*dt;}	
		//cout<<V[i]<<" "<<t[i]<<endl;
	};


};


