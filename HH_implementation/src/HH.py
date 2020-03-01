import numpy as np
from scipy.integrate import odeint
from scipy.integrate import solve_ivp
import Alpha_Beta
import In_current

######################################
#  Basic implementation of HH model  #
#  - 3 integration method.	         #
#  - 3 Impulse model				 #
#  - Extension to long dynamics      #
######################################

class HH():
	def __init__(self,Iin):
		self.Cm = 0.5  # Membrane Capacitance (uF/cm^2)
		self.Phi = 2.  # Temperture factor
		self.T = 100000.    # Total time of observations
		self.I = In_current.I(Iin,self.T)   # Injected current
		self.V_0=-60  # mV Initial value
		self.ENa = 50 # mV Na potential
		self.EK = -77 # mV K potential
		self.El = -54 # mV Leakage potential
		self.gbarNa = 120 # (cm^2/kΩ) Na conductance
		self.gbarK = 36 #(cm^2/kΩ) K conductance
		self.gbarl = 0.3 # (cm^2/kΩ) l conductance
		self.gbarm=0.01*self.gbarK
		self.A = Alpha_Beta.A_functions  # class with a_n,a_m,a_h functions
		self.B = Alpha_Beta.B_functions  # class with b_n,b_m,b_h functions
		self.D = Alpha_Beta.Delta_functions  # class with a_n,a_m,a_h functions
		self.G = Alpha_Beta.Gamma_functions  # class with b_n,b_m,b_h functions
		self.mode="hhsap"  # model selection
		self.eps = 1   # evolution of slow dynamics  (0 -> not evolving,1 -> evolving)
		self.s1_const = 1
		self.s2_const = 1

	def model_call(self,y,s,t):
		if(self.mode=="hh"): 
			return self.HH_basic(y,t)
		if(self.mode=="hhs"): 
			return self.HHS(y,s,t)
		if(self.mode=="hhsap"): 
			return self.HHSAP(y,s,t)
		if(self.mode=="hhsip"): 
			return self.HHSIP(y,s,t)

	def model_core(self,t,gNa,gK,y,s_1,s_2):
		V=y[0]
		n=y[1]
		m=y[2]
		h=y[3]
		gl=self.gbarl
		INa=gNa*(V-self.ENa)
		IK=gK*(V-self.EK)
		Il=gl*(V-self.El)
		I_in=self.I.Rect(t)
		return [((1/self.Cm)*(I_in-(INa+IK+Il))),self.Phi*(self.A.A_n(V)*(1-n)-self.B.B_n(V)*n),self.Phi*(self.A.A_m(V)*(1-m)-self.B.B_m(V)*m),self.Phi*(self.A.A_h(V)*(1-h)-self.B.B_h(V)*h),s_1,s_2]

	
	def HH_basic(self,y,t):
		V=y[0]
		n=y[1]
		m=y[2]
		h=y[3]
		gNa=self.gbarNa*pow(m,3)*h
		gK=self.gbarK*pow(n,4)
		return self.model_core(t,gNa,gK,y,0,0)

	def HHS(self,y,s,t):
		V=y[0]
		n=y[1]
		m=y[2]
		h=y[3]
		s_1=s[0]
		gNa=self.gbarNa*pow(m,3)*h*s_1
		gK=self.gbarK*pow(n,4)
		return self.model_core(t,gNa,gK,y,self.D.D_s1(V)*(1-s_1)-self.G.G_s1(V)*s_1,0)
		
	def HHSAP(self,y,s,t):
		V=y[0]
		n=y[1]
		m=y[2]
		h=y[3]
		s_1=s[0]
		s_2=s[1]
		gNa=self.gbarNa*pow(m,3)*h*s_1
		gK=(self.gbarK+self.gbarm*s_2)*pow(n,4)
		return self.model_core(t,gNa,gK,y,self.D.D_s1(V)*(1-s_1)-self.G.G_s1(V)*s_1,self.D.D_s2(V)*(1-s_2)-self.G.G_s2(V)*s_2)

	def HHSIP(self,y,s,t):
		V=y[0]
		n=y[1]
		m=y[2]
		h=y[3]
		s_1=s[0]
		s_2=s[1]
		gNa=self.gbarNa*pow(m,3)*h*s_1
		gK=(self.gbarK+self.gbarm*s_2)*pow(n,4)
		return self.model_core(t,gNa,gK,y,self.D.D_s1(V)*(1-s_1)-self.G.G_s1(V)*s_1,self.G.G_s2(V)*(1-s_2)-self.D.D_s2(V)*s_2)





