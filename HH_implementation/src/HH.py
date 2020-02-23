import numpy as np
from scipy.integrate import odeint
from scipy.integrate import solve_ivp
import Alpha_Beta
import In_current

######################################
#  Basic implementation of HH model  #
#  - Expand to ODE exact	         #
#  - I(t) for train current          #
#  - Extension to long dynamics      #
######################################

class HH():
	def __init__(self,I):
		self.Cm = 0.5  # Membrane Capacitance (uF/cm^2)
		self.Phi = 2.  # Temperture factor
		self.dt = 0.005  # Time steps (ms)
		self.T = 200.    # Total time of observations
		self.t = np.arange(0, self.T,self.dt).tolist()  # Range Time for the stimulation (ms)
		self.I = In_current.I(I,self.T)   # Injected current
		#self.I=I
		self.ENa = 50 # mV Na potential
		self.EK = -77 # mV K potential
		self.El = -54 # mV Leakage potential
		self.gbarNa = 120 # (cm^2/kΩ) Na conductance
		self.gbarK = 36 #(cm^2/kΩ) K conductance
		self.gbarl = 0.3 # (cm^2/kΩ) l conductance
		self.V = []  # Membrane potential list
		self.n = []  # n potential list
		self.m = []  # m potential list
		self.h = []  # h potential list
		self.A = Alpha_Beta.A_functions  # class with a_n,a_m,a_h functions
		self.B = Alpha_Beta.B_functions  # class with b_n,b_m,b_h functions
				
	def Clearer(self):
		self.V=[]
		self.m=[]
		self.n=[]
		self.h=[]
	
	def Peak_Detection(self):
		count=0
		#Npeak=0
		Npeak=[]
		for i in self.V:
			if(count==0 and i>-10): 
				count=1		
				Npeak.append(1)
			elif(count==1 and i<-10):
				count=0
				Npeak.append(0)
			else:
				Npeak.append(0)

		return Npeak
		#return 1000.*Npeak/self.T

	def Initialization(self):
		self.V.append(-60)
		self.m.append(self.A.A_m(self.V[0])/(self.A.A_m(self.V[0])+self.B.B_m(self.V[0])))
		self.n.append(self.A.A_n(self.V[0])/(self.A.A_n(self.V[0])+self.B.B_n(self.V[0])))
		self.h.append(self.A.A_h(self.V[0])/(self.A.A_h(self.V[0])+self.B.B_h(self.V[0])))

	def model(self,y,t):
		V=y[0]
		n=y[1]
		m=y[2]
		h=y[3]
		gNa=self.gbarNa*pow(m,3)*h
		gK=self.gbarK*pow(n,4)
		gl=self.gbarl
		INa=gNa*(V-self.ENa)
		IK=gK*(V-self.EK)
		Il=gl*(V-self.El)
		I=self.I.Rect(t)
		return [((1/self.Cm)*(I-(INa+IK+Il))),self.Phi*(self.A.A_n(V)*(1-n)-self.B.B_n(V)*n),self.Phi*(self.A.A_m(V)*(1-m)-self.B.B_m(V)*m),self.Phi*(self.A.A_h(V)*(1-h)-self.B.B_h(V)*h)]

	
	def Calculator_aux(self,y_1,y_2,y_3,y_4,t):
		res=self.model([y_1,y_2,y_3,y_4],t)
		return self.dt*res[0],self.dt*res[1],self.dt*res[2],self.dt*res[3]

	def Forward_Euler(self):
		self.Initialization()
		for i in range(1,len(self.t)):
			K_1=self.Calculator_aux(self.V[i-1],self.n[i-1],self.m[i-1],self.h[i-1],self.t[i])
			self.V.append(self.V[i-1]+K_1[0])
			self.n.append(self.n[i-1] +K_1[1])
			self.m.append(self.m[i-1] + K_1[2])
			self.h.append(self.h[i-1]+K_1[3])

	def Runge_Kutta(self):
		self.Initialization()
		for i in range(1,len(self.t)):
			K_1=self.Calculator_aux(self.V[i-1],self.n[i-1],self.m[i-1],self.h[i-1],self.t[i])
			K_2=self.Calculator_aux(self.V[i-1]+(0.5*K_1[0]),self.n[i-1]+(0.5*K_1[1]),self.m[i-1]+(0.5*K_1[2]),self.h[i-1]+(0.5*K_1[3]),self.t[i])
			K_3=self.Calculator_aux(self.V[i-1]+(0.5*K_2[0]),self.n[i-1]+(0.5*K_2[1]),self.m[i-1]+(0.5*K_2[2]),self.h[i-1]+(0.5*K_2[3]),self.t[i])
			K_4=self.Calculator_aux(self.V[i-1]+K_3[0],self.n[i-1]+K_3[1],self.m[i-1]+K_3[2],self.h[i-1]+K_3[3],self.t[i])
			self.V.append(self.V[i-1]+(K_1[0]+2*K_2[0]+2*K_3[0]+K_4[0])/6)
			self.n.append(self.n[i-1]+(K_1[1]+2*K_2[1]+2*K_3[1]+K_4[1])/6)
			self.m.append(self.m[i-1]+(K_1[2]+2*K_2[2]+2*K_3[2]+K_4[2])/6)
			self.h.append(self.h[i-1]+(K_1[3]+2*K_2[3]+2*K_3[3]+K_4[3])/6)

	def ODE(self):
		self.Initialization()
		sol=odeint(self.model,[self.V[0],self.n[0],self.m[0],self.h[0]],self.t)
		self.V=sol[:,0]
		self.n=sol[:,1]
		self.m=sol[:,2]
		self.h=sol[:,3]

