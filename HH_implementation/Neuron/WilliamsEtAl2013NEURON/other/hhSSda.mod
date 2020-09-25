TITLE hh.mod   squid sodium, potassium, and leak channels
 
COMMENT

Stochastic Hodgkin and Huxley equations with diffusion aproximation and Stochastic Shielding approximation (hhSSda)
Equations as in Orio & Soudry (2012) PLoS One with the approximation proposed by Schmandt & Galan (2012) Phys Rev Lett 109:118101
Stochastic terms for transitions that do not connect the conducting states are neglected. Thus the only transitions that keep random terms are
mh3 <--> mh7,  mh6<-->mh7 and n3<--> n4
Variables are unbound and real square roots are ensured by applying absolute values to variables, but only in random terms
Implemented for Pezo, Soudry and Orio (2014) Front Comp Neurosci 
 
ENDCOMMENT
 
UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
	(S) = (siemens)
}
 
NEURON {
	SUFFIX hhSSda
	USEION na READ ena WRITE ina
	USEION k READ ek WRITE ik
	NONSPECIFIC_CURRENT il
	RANGE gnabar, gkbar, gl, el, NNa, NK, se
}
 
PARAMETER {
	se = -1
	gnabar = .12 (S/cm2)	<0,1e9>
	gkbar = .036 (S/cm2)	<0,1e9>
	gl = .0003 (S/cm2)	<0,1e9>
	el = -54.3 (mV)
	NNa = 5000
	NK = 1500 
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
	R[3]	(/ms)
	mh0    :mh0 and n0 are treated as ASSIGNED because they are always expressed
	n0     :as 1-(sum of other states) to keep normalization
	
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
	if (se>0) {set_seed(se)}
	rates(v)	
	M=am/bm
	H=ah/bh
	N=an/bn
    
    :solve initial state occupancies
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
	 
	mh1' = (-2*am-bm-ah)*mh1 + 3*am*mh0 + 2*bm*mh2 + bh*mh5 
	mh2' = (-am-2*bm-ah)*mh2 + 2*am*mh1 + 3*bm*mh3 + bh*mh6 
	mh3' = (-3*bm-ah)*mh3 + am*mh2 + bh*mh7 + R[0] 
	mh4' = (-3*am-bh)*mh4 + bm*mh5 + ah*mh0 
   	mh5' = (-2*am-bm-bh)*mh5 + 3*am*mh4 + 2*bm*mh6 + ah*mh1 
   	mh6' = (-am-2*bm-bh)*mh6 + 2*am*mh5 + 3*bm*mh7 + ah*mh2 + R[1] 
    mh7' = (-3*bm-bh)*mh7 + am*mh6 + ah*mh3 -R[1]-R[0]
	mh0 = 1-mh1-mh2-mh3-mh4-mh5-mh6-mh7
		 
	n1' = (-3*an-bn)*n1 + 4*an*n0 + 2*bn*n2 
	n2' = (-2*an-2*bn)*n2 + 3*an*n1 + 3*bn*n3 
	n3' = (-an-3*bn)*n3 + 2*an*n2 + 4*bn*n4 + R[2] 
	n4' = -4*bn*n4 + an*n3 -R[2]		
	n0 = 1-n1-n2-n3-n4
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
		
	FROM ii=0 TO 1 {R[ii]=normrand(0,1/sqrt(NNa*dt))}
	R[2]=normrand(0,1/sqrt(NK*dt))

	R[0] = R[0]*sqrt(fabs(ah*mh3+bh*mh7))
	R[1] = R[1]*sqrt(fabs(am*mh6+3*bm*mh7))
	R[2] = R[2]*sqrt(fabs(an*n3+4*bn*n4))
	UNITSON 
}
