from math import exp

###############################
# Evolution of Ions density   #
# 			                  #
#   - m,h ---> Na	          #
#   - n ---> K		          #
###############################

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
