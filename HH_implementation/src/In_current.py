from numpy import linspace,where, abs


class I():

	def __init__(self,I_0,T_tot):
		self.I_0=I_0   
		self.T=6
		self.T_tot=T_tot
		self.k=int(float(T_tot)/float(self.T))
		self.delta_t=0.15

	def Rect(self,t):
		f=0
		for i in range(1,self.k):
			f+=self.I_0*where(abs(t-i*self.T)<=self.delta_t,1,0)
		return f

	def Dirac(self,t):
		f=0
		for i in range(1,self.k):
			f+=pow(self.I_0,3)*where(abs(t-i*self.T)==0, 1, 0)   
		return f