TITLE hh.mod   squid sodium, potassium, and leak channels
 
COMMENT
Stochastic Hodgkin and Huxley model using Markov Chain modeling with Stochastic Shielding as proposed by 
Schmandt & Galan (2012) Phys Rev Lett 109:118101

Sodium channel states are:
mh0 = m0h0   mh1 = m1h0   mh2 = m2h0  mh3 = m3h0
mh4 = m0h1   mh5 = m1h1   mh6 = m2h1  mh7 = m3h1

Stochastic transitions are solved with Gillespie's method with a modification for low channel numbers (or few transitions).
Deterministic transitions are left to Neuron's numerical method (note that we obtained comparable results with Euler method in Python)
Written for Pezo, Soudry and Orio (2014) Front. Comp Neurosci
                                       
ENDCOMMENT
 
UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
	(S) = (siemens)
}
 
NEURON {
	SUFFIX hhSSmc
	USEION na READ ena WRITE ina
	USEION k READ ek WRITE ik
	NONSPECIFIC_CURRENT il
	RANGE gnabar, gkbar, gl, el, NNa, NK, se
  RANGE nextRNa, nextRK, prev_evNa, prev_evK, next_evNa, next_evK,NaT, K_3_4, K_4_3
  RANGE sumrtNa, sumrtK, mh0, n0, N
  RANGE an, bn, am, bm
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
	NaT[4]	(/ms)
	K_4_3	(/ms)
	K_3_4	(/ms)
	cumsumNa[4]	(/ms)
	prev_evNa	(ms)
	next_evNa	(ms)
	prev_evK	(ms)
	next_evK	(ms)
	nextRNa
	sumrtNa  	(/ms)
	nextRK
	sumrtK		(/ms)
	ev
	mh0    :mh0 and n0 are ASSIGNED because they are solved from normalization,
            : not a diff equation
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
	ina = gnabar*mh7*(v - ena)/NNa
	ik = gkbar*n4*(v - ek)/NK
	il = gl*(v - el)
}
 
INITIAL {
	if (se>0) {set_seed(se)}
	ratesNa(v)
	ratesK(v)
	M=am/bm
	H=ah/bh
	N=an/bn
    
    :Solve steady state occupancy (at v_init) as initial condition
	stsum=(1+H)*(1+M)^3
	mh0=NNa/stsum
	mh1=NNa*3*M/stsum
	mh2=NNa*3*M^2/stsum
	mh3=NNa*M^3/stsum
	mh4=NNa*H/stsum
	mh5=NNa*H*3*M/stsum
	mh6=NNa*H*3*M^2/stsum
	mh7=NNa*H*M^3/stsum
	
	stsum=(1+N)^4
	n0=NK/stsum
	n1=NK*4*N/stsum
	n2=NK*6*N^2/stsum
	n3=NK*4*N^3/stsum
	n4=NK*N^4/stsum
	ratesNa(v)
	ratesK(v)
    
    :calculate a random numbre (log) for the first transitions
    :also set the time of previous transition to 0
  nextRNa=log(scop_random())
  nextRK=log(scop_random())
	prev_evK=0
	prev_evNa=0
  
}

DERIVATIVE states {  
	ratesNa(v)
	:Deterministic transitions 
	mh1' = (-2*am-bm-ah)*mh1 + 3*am*mh0 + 2*bm*mh2 + bh*mh5 
	mh2' = (-am-2*bm-ah)*mh2 + 2*am*mh1 + 3*bm*mh3 + bh*mh6 
	mh3' = (-3*bm)*mh3 + am*mh2  			:mh3 only transitions to/from mh2
	mh4' = (-3*am-bh)*mh4 + bm*mh5 + ah*mh0 
    mh5' = (-2*am-bm-bh)*mh5 + 3*am*mh4 + 2*bm*mh6 + ah*mh1 
   	mh6' = (-2*bm-bh)*mh6 + 2*am*mh5 + ah*mh2    	:mh6 only transitions to/from mh5 and mh2
    :	all  transitions involving mh7 are stochastic
    
    :check if it's time for a Na transition
	next_evNa = prev_evNa - nextRNa/sumrtNa  
	while (t>= next_evNa){
		transNa()                 :Do transitions
		prev_evNa = next_evNa     :immediately check if there is another transition within the current time step
		next_evNa = prev_evNa - nextRNa/sumrtNa  
	}
    :finally, apply normalization
	mh0 = NNa-mh1-mh2-mh3-mh4-mh5-mh6-mh7
	
	ratesK(v)		
	:Deterministic K transitions
	n1' = (-3*an-bn)*n1 + 4*an*n0 + 2*bn*n2 
	n2' = (-2*an-2*bn)*n2 + 3*an*n1 + 3*bn*n3 
	n3' = (-3*bn)*n3 + 2*an*n2
    : transitions with n4 are stochastic
	next_evK = prev_evK - nextRK/sumrtK
	while (t>= next_evK){
		transK()
        prev_evK = next_evK
		next_evK = prev_evK - nextRK/sumrtK
	}
	n0 = NK-n1-n2-n3-n4
}
 
LOCAL q10

PROCEDURE ratesNa(v(mV)) {  :Computes rate and other constants at current v.

	UNITSOFF
	q10 = 3^((celsius - 6.3)/10)
	am = q10*0.1*(v+40)/(1-exp(-(v+40)/10))
	bm = q10*4*exp(-(v+65)/18)
	ah = q10*0.07*exp(-(v+65)/20) 
	bh = q10/(1+exp(-(v+35)/10))

    : NaT[i] contains the effective transition rate for the ith transition, as follows:
	NaT[0]=ah*mh3  :mh3 --> mh7
	NaT[1]=bh*mh7	:mh7 --> mh3
	NaT[2]=am*mh6	:mh6 -->mh7
	NaT[3]=3*bm*mh7	:mh7 --> mh6
	sumrtNa=NaT[0] + NaT[1] + NaT[2] + NaT[3]
}
		
PROCEDURE ratesK(v(mV)) {  :Computes rate and other constants at current v.
	q10 = 3^((celsius - 6.3)/10)
	an = q10*0.01*(v+55)/(1-exp(-(v+55)/10))
	bn = q10*0.125*exp(-(v+65)/80)
	K_3_4 = an*n3     : n3 --> n4 transition
	K_4_3 = 4*bn*n4   : n4 --> n3 transition
	sumrtK = K_3_4 + K_4_3

	UNITSON 
}


PROCEDURE transNa() {
	ratesNa(v)
	UNITSOFF
	sumrtNa=0
    :Build a cummulative sum of rates
	FROM ii=0 TO 3 {
		sumrtNa = sumrtNa + NaT[ii]
		cumsumNa[ii] = sumrtNa
	}
    : Normalize the cumm sum
	FROM ii=0 TO 3 {cumsumNa[ii] = cumsumNa[ii] / sumrtNa}

    : Draw a random number Uniform [0,1] to select a transition
	ev = scop_random()
	if (ev <= cumsumNa[0]) { :mh3 --> mh7
		mh3=mh3-1
		mh7=mh7+1
	}
	if (cumsumNa[0] < ev && ev <= cumsumNa[1]) {  :mh7 --> mh3
		mh3=mh3+1
		mh7=mh7-1
	}	
	if (cumsumNa[1] < ev && ev <= cumsumNa[2]) {  : mh6 --> mh7
		mh6=mh6-1
		mh7=mh7+1
	}
	if (cumsumNa[2] < ev && ev <= cumsumNa[3]) {  : mh7 --> mh6
		mh6=mh6+1
		mh7=mh7-1
	}
	UNITSON
    
    : Correct possible off bounds values (this should happen only once)
	if (mh3>NNa){mh3=NNa}
	if (mh6>NNa){mh6=NNa}
	if (mh7>NNa){mh7=NNa}
	if (mh3<0){mh3=0}
	if (mh6<0){mh6=0}
	if (mh7<0){mh7=0}

	nextRNa=log(scop_random())
}

PROCEDURE transK() {
	ratesK(v)
   	sumrtK=0
	sumrtK = K_3_4 + K_4_3
	ev = scop_random()
    
    : There are only two possible transitions
	if (ev <= (K_3_4 / sumrtK)) {
		n3=n3-1
		n4=n4+1
	} else {
		n3=n3+1
		n4=n4-1
	}
    :Correct off bounds values	
	if (n3>NK){n3=NK}
	if (n4>NK){n4=NK}
	if (n3<0){n3=0}
	if (n4<0){n4=0}
	nextRK = log(scop_random())
}
