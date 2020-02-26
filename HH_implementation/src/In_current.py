from numpy import linspace,where, abs


class I():

	def __init__(self,I_0,T_tot):
		self.I_0=I_0   # Amplitude of impulse
		self.T=6.     # Periodicity
		self.T_tot=T_tot      # Total time of observation
		self.k=int(float(T_tot)/float(self.T))   #number of positive impulses on the train
		self.delta_t=0.15 # duration of impulse

	def Const(self):
		return self.I_0

	def Rect(self,t):
		#self.delta_t=1/self.I_0
		f=0
		for i in range(1,self.k+1):
			f+=self.I_0*where(abs(t-i*self.T)<=self.delta_t,1,0)
		return f

	def Dirac(self,t):
		f=0
		factor=self.delta_t
		for i in range(1,self.k+1):
			f+=factor*self.I_0*where(abs(t-i*self.T)==0, 1, 0)   
		return f