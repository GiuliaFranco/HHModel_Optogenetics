TITLE hh.mod   squid sodium, potassium, and leak channels
 
COMMENT
Stochastic Hodgkin and Huxley equations with diffusion aproximation (hhDA)
Equations as in Orio & Soudry (2012) PLoS One
Variables are unbound and real square roots are ensured by applying absolute values to variables, but only in random terms

Sodium channel states are:
mh0 = m0h0   mh1 = m1h0   mh2 = m2h0  mh3 = m3h0
mh4 = m0h1   mh5 = m1h1   mh6 = m2h1  mh7 = m3h1

Implemented for Pezo, Soudry and Orio (2014) Front Comp Neurosci 
ENDCOMMENT
 
UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
	(S) = (siemens)
}
 
NEURON {
	SUFFIX hhDA
	USEION na READ ena WRITE ina
	USEION k READ ek WRITE ik
	NONSPECIFIC_CURRENT il
	RANGE gnabar, gkbar, gl, el, NNa, NK, sumN, sumMH, se
}
 
PARAMETER {
	se=-1    : random seed. If se=-1, seed is not set
	gnabar = .12 (S/cm2)	<0,1e9>
	gkbar = .036 (S/cm2)	<0,1e9>
	gl = .0003 (S/cm2)	<0,1e9>
	el = -54.3 (mV)
	NNa = 5000
	NK = 1600 
}
 
ASSIGNED {
	v (mV)
	celsius (degC)
	ena (mV)
	ek (mV)
	dt (ms)
	ina (mA/cm2)
	ik (mA/cm2)
	il (mA/cm2)
	am	(/ms)
	ah	(/ms)
	an	(/ms)
	bm	(/ms)
	bh	(/ms)
	bn	(/ms)
	stsum
	M
	N
	H
	R[14]	(/ms)
	mh0   :mh0 and n0 are ASSIGNED because they don't follow a differential equation
	n0
	
}
 
STATE {	
	mh1
	mh2
	mh3
	mh4
	mh5
	mh6
	mh7
	n1
	n2
	n3
	n4
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	ina = gnabar*mh7*(v - ena)
	ik = gkbar*n4*(v - ek)
	il = gl*(v - el)
}
 
INITIAL {
	rates(v)	
	if (se>=0) {set_seed(se)} :set seed
	M=am/bm
	H=ah/bh
	N=an/bn
	stsum=(1+H)*(1+M)^3
	mh0=1/stsum
	mh1=3*M/stsum
	mh2=3*M^2/stsum
	mh3=M^3/stsum
	mh4=H/stsum
	mh5=H*3*M/stsum
	mh6=H*3*M^2/stsum
	mh7=H*M^3/stsum
	
	stsum=(1+N)^4
	n0=1/stsum
	n1=4*N/stsum
	n2=6*N^2/stsum
	n3=4*N^3/stsum
	n4=N^4/stsum
	rates(v)
}

DERIVATIVE states {  
	rates(v)
	mh1' = (-2*am-bm-ah)*mh1 + 3*am*mh0 + 2*bm*mh2 + bh*mh5 -R[0]+R[1]+R[4]	
	mh2' = (-am-2*bm-ah)*mh2 + 2*am*mh1 + 3*bm*mh3 + bh*mh6 -R[1]+R[2]+R[5]
	mh3' = (-3*bm-ah)*mh3 + am*mh2 + bh*mh7 -R[2]+R[6]
	mh4' = (-3*am-bh)*mh4 + bm*mh5 + ah*mh0 + R[7]-R[3]
    	mh5' = (-2*am-bm-bh)*mh5 + 3*am*mh4 + 2*bm*mh6 + ah*mh1 -R[7]+R[8]-R[4]
    	mh6' = (-am-2*bm-bh)*mh6 + 2*am*mh5 + 3*bm*mh7 + ah*mh2 -R[8]+R[9]-R[5]
   	mh7' = (-3*bm-bh)*mh7 + am*mh6 + ah*mh3 -R[9]-R[6]
    	mh0 = 1-mh1-mh2-mh3-mh4-mh5-mh6-mh7 :normalization
	
	n1' = (-3*an-bn)*n1 + 4*an*n0 + 2*bn*n2 - R[10] + R[11]
	n2' = (-2*an-2*bn)*n2 + 3*an*n1 + 3*bn*n3 -R[11] + R[12]
	n3' = (-an-3*bn)*n3 + 2*an*n2 + 4*bn*n4 -R[12] + R[13]
	n4' = -4*bn*n4 + an*n3 -R[13]
	n0 = 1-n1-n2-n3-n4		:normalization
}
 
LOCAL q10

PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
	LOCAL q10
	UNITSOFF
	q10 = 3^((celsius - 6.3)/10)
	am = q10*0.1*(v+40)/(1-exp(-(v+40)/10))
	bm = q10*4*exp(-(v+65)/18)
	ah = q10*0.07*exp(-(v+65)/20) 
	bh = q10/(1+exp(-(v+35)/10))
	an = q10*0.01*(v+55)/(1-exp(-(v+55)/10))
	bn = q10*0.125*exp(-(v+65)/80)
		
	FROM ii=0 TO 9 {R[ii]=normrand(0,1/sqrt(NNa*dt))}
	FROM ii=10 TO 13 {R[ii]=normrand(0,1/sqrt(NK*dt))}
	R[0] = R[0]*sqrt(fabs(3*am*mh0+bm*mh1))
	R[1] = R[1]*sqrt(fabs(2*am*mh1+2*bm*mh2))
	R[2] = R[2]*sqrt(fabs(am*mh2+3*bm*mh3))
	R[3] = R[3]*sqrt(fabs(ah*mh0+bh*mh4))
	R[4] = R[4]*sqrt(fabs(ah*mh1+bh*mh5))
	R[5] = R[5]*sqrt(fabs(ah*mh2+bh*mh6))
	R[6] = R[6]*sqrt(fabs(ah*mh3+bh*mh7))
	R[7] = R[7]*sqrt(fabs(3*am*mh4+bm*mh5))
	R[8] = R[8]*sqrt(fabs(2*am*mh5+2*bm*mh6))
	R[9] = R[9]*sqrt(fabs(am*mh6+3*bm*mh7))
	R[10] = R[10]*sqrt(fabs(4*an*n0+bn*n1)) 
	R[11] = R[11]*sqrt(fabs(3*an*n1+2*bn*n2))
	R[12] = R[12]*sqrt(fabs(2*an*n2+3*bn*n3))
	R[13] = R[13]*sqrt(fabs(an*n3+4*bn*n4))
	UNITSON 
}
