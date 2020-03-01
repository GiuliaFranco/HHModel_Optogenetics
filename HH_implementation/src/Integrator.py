import numpy as np
import HH


class Solver():

	def __init__(self,model):
		self.model=model   # Model of the system
		self.dt = 0.01  # Time steps (ms)
		self.T = model.T    # Total time of observations
		self.T_start=0
		self.t = np.arange(self.T_start, self.T,self.dt).tolist()  # Range Time for the stimulation (ms)
		self.V = []  # Membrane potential list
		self.n = []  # n potential list
		self.m = []  # m potential list
		self.h = []  # h potential list
		self.s1 = [] # Slow sodium activation
		self.s2 = []

	def Clearer(self):
		self.V=[]
		self.m=[]
		self.n=[]
		self.h=[]
		self.s1=[]
		self.s2=[]
	
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

	def Latency(self):
		#differenza tra quando dò l'impulso ed il primo picco di voltaggio
		max_V = max(self.V)
		max_V_index = self.V.index(max_V)
		max_V_t = self.t[max_V_index]
		fI=self.model.I.Rect( np.asarray(self.t, dtype=np.float32))
		max_I = np.amax(fI)
		max_I_index = np.where(fI == max_I)[0][0]
		max_I_t = self.t[max_I_index]
		if(max_V>=-10):
			return (max_V_t-max_I_t)
		else:
			return 0


	def Initialization_aux(self):
		if(self.model.mode=="hhsip"):
			self.s2[0]=self.model.G.G_s2(self.V[0])/(self.model.G.G_s2(self.V[0])+self.model.D.D_s2(self.V[0]))

	def Initialization(self):
		self.V.append(self.model.V_0)
		self.m.append(self.model.A.A_m(self.V[0])/(self.model.A.A_m(self.V[0])+self.model.B.B_m(self.V[0])))
		self.n.append(self.model.A.A_n(self.V[0])/(self.model.A.A_n(self.V[0])+self.model.B.B_n(self.V[0])))
		self.h.append(self.model.A.A_h(self.V[0])/(self.model.A.A_h(self.V[0])+self.model.B.B_h(self.V[0])))
		if(self.model.eps!=0):
			self.s1.append(self.model.D.D_s1(self.V[0])/(self.model.D.D_s1(self.V[0])+self.model.G.G_s1(self.V[0])))
			self.s2.append(self.model.D.D_s2(self.V[0])/(self.model.D.D_s2(self.V[0])+self.model.G.G_s2(self.V[0])))
			self.Initialization_aux()
		else:
			self.s1.append(self.model.s1_const)
			self.s2.append(self.model.s2_const)

	def Calculator_aux(self,y_1,y_2,y_3,y_4,y_5,y_6,t):
		res=self.model.model_call([y_1,y_2,y_3,y_4],[y_5,y_6],t)
		return self.dt*res[0],self.dt*res[1],self.dt*res[2],self.dt*res[3],self.dt*res[4],self.dt*res[5]

	def Forward_Euler(self):
		self.Initialization()
		for i in range(1,len(self.t)):
			K_1=self.Calculator_aux(self.V[i-1],self.n[i-1],self.m[i-1],self.h[i-1],self.s1[i-1],self.s2[i-1],self.t[i-1])
			self.V.append(self.V[i-1]+K_1[0])
			self.n.append(self.n[i-1] +K_1[1])
			self.m.append(self.m[i-1] + K_1[2])
			self.h.append(self.h[i-1]+K_1[3])
			#if(self.model.eps!=0):
			self.s1.append(self.s1[i-1]+K_1[4])
			self.s2.append(self.s2[i-1]+K_1[5])
			#else:
			#	self.s1.append(self.model.s1_const)
			#	self.s2.append(self.model.s2_const)

	def Runge_Kutta(self,lenT):
		self.Initialization()
		for i in range(1,lenT):
			K_1=self.Calculator_aux(self.V[i-1],self.n[i-1],self.m[i-1],self.h[i-1],self.s1[i-1],self.s2[i-1],self.t[i-1])
			K_2=self.Calculator_aux(self.V[i-1]+(0.5*K_1[0]),self.n[i-1]+(0.5*K_1[1]),self.m[i-1]+(0.5*K_1[2]),self.h[i-1]+(0.5*K_1[3]),self.s1[i-1]+(0.5*K_1[4]),self.s2[i-1]+(0.5*K_1[5]),self.t[i-1])
			K_3=self.Calculator_aux(self.V[i-1]+(0.5*K_2[0]),self.n[i-1]+(0.5*K_2[1]),self.m[i-1]+(0.5*K_2[2]),self.h[i-1]+(0.5*K_2[3]),self.s1[i-1]+(0.5*K_2[4]),self.s2[i-1]+(0.5*K_1[5]),self.t[i-1])
			K_4=self.Calculator_aux(self.V[i-1]+K_3[0],self.n[i-1]+K_3[1],self.m[i-1]+K_3[2],self.h[i-1]+K_3[3],self.s1[i-1]+K_3[4],self.s2[i-1]+K_3[5],self.t[i-1])
			self.V.append(self.V[i-1]+(K_1[0]+2*K_2[0]+2*K_3[0]+K_4[0])/6)
			self.n.append(self.n[i-1]+(K_1[1]+2*K_2[1]+2*K_3[1]+K_4[1])/6)
			self.m.append(self.m[i-1]+(K_1[2]+2*K_2[2]+2*K_3[2]+K_4[2])/6)
			self.h.append(self.h[i-1]+(K_1[3]+2*K_2[3]+2*K_3[3]+K_4[3])/6)
			if(self.model.eps!=0):
				self.s1.append(self.s1[i-1]+(K_1[4]+2*K_2[4]+2*K_3[4]+K_4[4])/6)
				self.s2.append(self.s2[i-1]+(K_1[5]+2*K_2[5]+2*K_3[5]+K_4[5])/6)
			else:
				self.s1.append(self.model.s1_const)
				self.s2.append(self.model.s2_const)	

	def Predictor_aux(self,K_1,K_2,K_3,K_4,i):
		Vp=self.V[i-1]+(self.dt/24)*(55.*K_1[0]-59.*K_2[0]+37.*K_3[0]-9*K_4[0])
		npp=self.n[i-1]+(self.dt/24)*(55.*K_1[1]-59.*K_2[1]+37.*K_3[1]-9*K_4[1])
		mp=self.m[i-1]+(self.dt/24)*(55.*K_1[2]-59.*K_2[2]+37.*K_3[2]-9*K_4[2])
		hp=self.h[i-1]+(self.dt/24)*(55.*K_1[3]-59.*K_2[3]+37.*K_3[3]-9*K_4[3])
		s1p=self.s1[i-1]+(self.dt/24)*(55.*K_1[4]-59.*K_2[4]+37.*K_3[4]-9*K_4[4])
		s2p=self.s2[i-1]+(self.dt/24)*(55.*K_1[5]-59.*K_2[5]+37.*K_3[5]-9*K_4[5])
		return [Vp,npp,mp,hp,s1p,s2p]				

	def Corrector_aux(self,K_1,K_2,K_3,i,pred):
		K_5=self.model.model_call([pred[0],pred[1],pred[2],pred[3]],[pred[4],pred[5]],self.t[i-1])
		Vc=self.V[i-1]+(self.dt/24)*(9.*K_5[0]+19.*K_1[0]-5.*K_2[0]+K_3[0])
		nc=self.n[i-1]+(self.dt/24)*(9.*K_5[1]+19.*K_1[1]-5.*K_2[1]+K_3[1])
		mc=self.m[i-1]+(self.dt/24)*(9.*K_5[2]+19.*K_1[2]-5.*K_2[2]+K_3[2])
		hc=self.h[i-1]+(self.dt/24)*(9.*K_5[3]+19.*K_1[3]-5.*K_2[3]+K_3[3])
		s1c=self.s1[i-1]+(self.dt/24)*(9.*K_5[4]+19.*K_1[4]-5.*K_2[4]+K_3[4])
		s2c=self.s2[i-1]+(self.dt/24)*(9.*K_5[5]+19.*K_1[5]-5.*K_2[5]+K_3[5])
		val=(19/270)
		return [Vc+val*(pred[0]-Vc),nc+val*(pred[1]-nc),mc+val*(pred[2]-mc),hc+val*(pred[3]-hc),s1c+val*(pred[4]-s1c),s2c+val*(pred[5]-s2c)]

	def Predictor_Corrector(self):
		self.Runge_Kutta(4)
		for i in range(4,len(self.t)):
			K_1=self.model.model_call([self.V[i-1],self.n[i-1],self.m[i-1],self.h[i-1]],[self.s1[i-1],self.s2[i-1]],self.t[i-1])
			K_2=self.model.model_call([self.V[i-2],self.n[i-2],self.m[i-2],self.h[i-2]],[self.s1[i-2],self.s2[i-2]],self.t[i-2])
			K_3=self.model.model_call([self.V[i-3],self.n[i-3],self.m[i-3],self.h[i-3]],[self.s1[i-3],self.s2[i-3]],self.t[i-3])
			K_4=self.model.model_call([self.V[i-4],self.n[i-4],self.m[i-4],self.h[i-4]],[self.s1[i-4],self.s2[i-4]],self.t[i-4])
			pred=self.Predictor_aux(K_1,K_2,K_3,K_4,i)
			corr=self.Corrector_aux(K_1,K_2,K_3,i,pred)
			self.V.append(corr[0])
			self.n.append(corr[1])
			self.m.append(corr[2])
			self.h.append(corr[3])
			if(self.model.eps!=0):
				self.s1.append(corr[4])
				self.s2.append(corr[5])
			else:
				self.s1.append(self.model.s1_const)
				self.s2.append(self.model.s2_const)	


#### BAD one ######
	def ODE(self):
		self.Initialization()
		sol=odeint(self.model.model_call,[self.V[0],self.n[0],self.m[0],self.h[0]],[self.s1[0],self.s2[0]],self.t)
		self.V=sol[:,0]
		self.n=sol[:,1]
		self.m=sol[:,2]
		self.h=sol[:,3]
		if(self.model.eps!=0):
			self.s1=sol[:,4]
			self.s2=sol[:,5]
		else:
			self.s1.append(self.model.s1_const)
			self.s2.append(self.model.s2_const)	


	