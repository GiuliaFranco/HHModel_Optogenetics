from math import exp,fabs

###############################
# Evolution of Ions density   #
# 			                  #
#   - m,h ---> Na	          #
#   - n ---> K		          #
###############################



def  vtrap(x,y):
	res=0
	if (fabs(x/y) < 1e-6):
		res = y*(1 - x/y/2)
	else:
		res = x/(exp(x/y) - 1)
	return res


class Gamma_functions():
	def G_s1(V):
		#Hz
		return 0.51/(exp(-0.3*(V+17.))+1)

	def G_s2(V):
		#HZ
		sigma=1./15.  #mV
		return (3.3*exp((V+35)*sigma) + exp(-(V+35)*0.05))/(1+ exp((V+35)*0.1))

class Delta_functions():
	def D_s1(V):
		#HZ
		return .05*exp(-0.033*(V+85))

	def D_s2(V):
		#HZ
		sigma=1./15.  #mV
		return (3.3*exp((V+35)*sigma) + exp(-(V+35)*0.05))/(1+ exp(-(V+35)*0.1))	

class Gamma_functions_WB():
	def G_s1(V):
		#HZ
		return 0.0077 / (1. + exp( -(47.+V)/9.  ) )

class Delta_functions_WB():
	def D_s1(V):
		#HZ
		return 0.0077 / (1. + exp( (47.+V)/9. ) )

class A_functions_WB():
# KHz
	def A_n(V):
		return .01*vtrap(-(V+55),10) 
	
	def A_m(V):
		return .1 * vtrap(-(V+40),10)

	def A_h(V):
		return .07 * exp(-(V+65)/20)


class B_functions_WB():
# KHz
	def B_n(V):
		return .125*exp(-(V+65)/80)  
	
	def B_m(V):
		return 4. * exp(-(V+65)/18)

	def B_h(V):
		return 1. / (exp(-(V+35)/10) + 1)


class A_functions():
# KHz
	def A_n(V):
		return 0.01*(V+55.)/(1-exp(-(V+55.)/10.))  
	
	def A_m(V):
		return 0.1*(V+40.)/(1-exp(-(V+40.)/10.))

	def A_h(V):
		return 0.07*exp(-0.05*(V+65.))



class B_functions():
# KHz
	def B_n(V):
		return 0.125*exp(-(V+65.)/80.) 

	def B_m(V):
		return 4.0*exp(-0.0556*(V+65.))

	def B_h(V):
		return 1./(1+exp(-(0.1)*(V+35.)))


