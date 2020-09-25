TITLE hh.mod   squid sodium, potassium, and leak channels

COMMENT
Stochastic Hodgkin and Huxley model using Markov Chain modeling.
Gillespie's method with a modification for low channel numbers (or few transitions)
Written for Pezo, Soudry and Orio (2014) Front. Comp Neurosci

Sodium channel states are:
Nast[0] = m0h0   Nast[1] = m1h0   Nast[2] = m2h0  Nast[3] = m3h0
Nast[4] = m0h1   Nast[5] = m1h1   Nast[6] = m2h1  Nast[7] = m3h1

Potassium states are:
Kst[0] =  n0   Kst[1] = n1   Kst[2] = n2  Kst[3] = n3  Kst[4] = n4

conducting states are m3h1 and n4, respectively

Possible Sodium channel transitions are indexed as follows:
First row trasitions (m particles)
    Forward            Backward
  0: Nast[0] --> Nast[1]   1: Nast[1] --> Nast[0]
  2: Nast[1] --> Nast[2]   3: Nast[2] --> Nast[1]
  4: Nast[2] --> Nast[3]   5: Nast[3] --> Nast[2]
Vertical transitions (h particle)
  6: Nast[0] --> Nast[4]   7: Nast[4] --> Nast[0]
  8: Nast[1] --> Nast[5]   9: Nast[5] --> Nast[1]
 10: Nast[2] --> Nast[6]  11: Nast[6] --> Nast[2]
 12: Nast[3] --> Nast[7]  13: Nast[7] --> Nast[3]
First row trasitions (m particles)
 14: Nast[4] --> Nast[5]  15: Nast[5] --> Nast[4]
 16: Nast[5] --> Nast[6]  17: Nast[6] --> Nast[5]
 18: Nast[6] --> Nast[7]  19: Nast[7] --> Nast[6]

Possible Potassium channel transitions are indexed as follows:
    Forward            Backward
 0: Kst[0] --> Kst[1]   1: Kst[1] --> Kst[0]
 2: Kst[1] --> Kst[2]   3: Kst[2] --> Kst[1]
 4: Kst[2] --> Kst[3]   5: Kst[3] --> Kst[2]
 6: Kst[3] --> Kst[4]   7: Kst[4] --> Kst[3]

ENDCOMMENT
 
UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
	(S) = (siemens)
}
 
NEURON {
	SUFFIX hhMC 
	USEION na READ ena WRITE ina
	USEION k READ ek WRITE ik
	NONSPECIFIC_CURRENT il
	RANGE gnabar, gkbar, gl, el, NNa, NK, next_evK, next_evNa, Nast, Kst, se
	RANGE nextRK, nextRNa
}
 
PARAMETER {
	se = -1  : seed to be used. se=-1 means no seed is set
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

	ina (mA/cm2)
	ik (mA/cm2)
	il (mA/cm2)
	alpha_m	(/ms)
	alpha_h	(/ms)
	alpha_n	(/ms)
	beta_m	(/ms)
	beta_h	(/ms)
	beta_n	(/ms)
	Nast[8]
	Kst[5]
	Nart[20]	(/ms)
	Krt[8]		(/ms)
	sumrtNa		(/ms)
	sumrtK		(/ms)
	cumsumNa[20](/ms)
	cumsumK[8]	(/ms)
	next_evNa	(ms)
	next_evK	(ms)
	prev_evNa	(ms)
	prev_evK	(ms)
    	nextRK
    	nextRNa
	ev			(/ms)
	M
	N
	H
}
 
STATE {mock}

BREAKPOINT {
	SOLVE mula METHOD cnexp
	ina = gnabar*Nast[7]*(v - ena)/NNa
	ik = gkbar*Kst[4]*(v - ek)/NK      
	il = gl*(v - el)
}
 
INITIAL {
	LOCAL stsum

	if (se>=0) {set_seed(se)}

    ratesNa(v)
    ratesK(v)
    
	M=alpha_m/beta_m
	H=alpha_h/beta_h
	N=alpha_n/beta_n
	stsum=(1+H)*(1+M)^3
    : calculate initial states

	Nast[1]=floor(NNa*3*M/stsum+0.5)
	Nast[2]=floor(NNa*3*M^2/stsum+0.5)
	Nast[3]=floor(NNa*M^3/stsum+0.5)
	Nast[4]=floor(NNa*H/stsum+0.5)
	Nast[5]=floor(NNa*H*3*M/stsum+0.5)
	Nast[6]=floor(NNa*H*3*M^2/stsum+0.5)
	Nast[7]=floor(NNa*H*M^3/stsum+0.5)
    Nast[0]=NNa-Nast[1]-Nast[2]-Nast[3]-Nast[4]-Nast[5]-Nast[6]-Nast[7]
	ratesNa(v)
    :calculate the random number (log) that will be used in the first transition 
    :time and set the last transition to t=0
	nextRNa = log(scop_random())
	prev_evNa=0
	
	stsum=(1+N)^4
	:calculate initial state occupancies
    Kst[1]=floor(NK*4*N/stsum+0.5)
	Kst[2]=floor(NK*6*N^2/stsum+0.5)
	Kst[3]=floor(NK*4*N^3/stsum+0.5)
	Kst[4]=floor(NK*N^4/stsum+0.5)
    Kst[0]=NK-Kst[1]-Kst[2]-Kst[3]-Kst[4]
	ratesK(v)
    :calculate the random number (log) that will be used in the first transition 
    :time and set the last transition to t=0
	nextRK = log(scop_random())
	prev_evK=0
}

DERIVATIVE mula {
    :recalculate rates
    ratesNa(v)
    :recalculate time of next event with the already existing random value (nextRNa)
	next_evNa = prev_evNa - nextRNa/sumrtNa  
	while (t>= next_evNa){ :do transitions if needed
        transNa()
        prev_evNa = next_evNa
        :calculate again next transition in case it falls within the current time step
		next_evNa = prev_evNa - nextRNa/sumrtNa  
    }

    :same for potassium
    ratesK(v)
	next_evK = prev_evK - nextRK/sumrtK
	while (t>= next_evK){
		transK()
        prev_evK = next_evK
		next_evK = prev_evK - nextRK/sumrtK
	}
	mock'=0
}
 
LOCAL q10

PROCEDURE ratesNa(v(mV)) {  :Computes rate and other constants at current v.
	UNITSOFF
	q10 = 3^((celsius - 6.3)/10)
	alpha_m = q10*0.1*(v+40)/(1-exp(-(v+40)/10))
	beta_m = q10*4*exp(-(v+65)/18)
	alpha_h = q10*0.07*exp(-(v+65)/20) 
	beta_h = q10/(1+exp(-(v+35)/10))
    :Nart[i] is the effective rate for the 'i' transition
	Nart[0]=3*alpha_m*Nast[0]
	Nart[1]=beta_m*Nast[1]
	Nart[2]=2*alpha_m*Nast[1]
	Nart[3]=2*beta_m*Nast[2]
	Nart[4]=alpha_m*Nast[2]
	Nart[5]=3*beta_m*Nast[3]
	Nart[6]=alpha_h*Nast[0]
	Nart[7]=beta_h*Nast[4]
	Nart[8]=alpha_h*Nast[1]
	Nart[9]=beta_h*Nast[5]
	Nart[10]=alpha_h*Nast[2]
	Nart[11]=beta_h*Nast[6]
	Nart[12]=alpha_h*Nast[3]
	Nart[13]=beta_h*Nast[7]
	Nart[14]=3*alpha_m*Nast[4]
	Nart[15]=beta_m*Nast[5]
	Nart[16]=2*alpha_m*Nast[5]
	Nart[17]=2*beta_m*Nast[6]
	Nart[18]=alpha_m*Nast[6]
	Nart[19]=3*beta_m*Nast[7]
	sumrtNa=0
	FROM ii=0 TO 19 {
		sumrtNa = sumrtNa + Nart[ii]
	}
	UNITSON
}

PROCEDURE ratesK(v(mV)) {
	UNITSOFF
	q10 = 3^((celsius - 6.3)/10)
	alpha_n = q10*0.01*(v+55)/(1-exp(-(v+55)/10))
	beta_n = q10*0.125*exp(-(v+65)/80)
    :Krt[i] is the effective rate for the 'i' transition
	Krt[0]=4*alpha_n*Kst[0]
	Krt[1]=beta_n*Kst[1]
	Krt[2]=3*alpha_n*Kst[1]
	Krt[3]=2*beta_n*Kst[2]
	Krt[4]=2*alpha_n*Kst[2]
	Krt[5]=3*beta_n*Kst[3]
	Krt[6]=alpha_n*Kst[3]
	Krt[7]=4*beta_n*Kst[4]
	sumrtK=0
	FROM ii=0 TO 7 {
		sumrtK = sumrtK + Krt[ii]
	}

	UNITSON
}

PROCEDURE transK() {  :perform a transition on K channels
    :calculate rates
	ratesK(v)
    :calculate a cummulative sum of effective transition rates
   	sumrtK=0
    UNITSOFF
	FROM ii=0 TO 7 {
		sumrtK = sumrtK + Krt[ii]
		cumsumK[ii] = sumrtK
	}
    :normalize the cummulative sum to 1
	FROM ii=0 TO 7 {cumsumK[ii] = cumsumK[ii] / sumrtK}
    UNITSON
    :draw a random number [0,1] and select a transition depending on 
    :where it falls within the cummulative sum of transition rates
	ev = scop_random()*1(/ms)
	if (ev <= cumsumK[0]) {
		Kst[0]=Kst[0]-1
		Kst[1]=Kst[1]+1
	}
	if (cumsumK[0] < ev && ev <= cumsumK[1]) {
		Kst[0]=Kst[0]+1
		Kst[1]=Kst[1]-1
	}	
	if (cumsumK[1] < ev && ev <= cumsumK[2]) {
		Kst[1]=Kst[1]-1
		Kst[2]=Kst[2]+1
	}
	if (cumsumK[2] < ev && ev <= cumsumK[3]) {
		Kst[1]=Kst[1]+1
		Kst[2]=Kst[2]-1
	}	
	if (cumsumK[3] < ev && ev <= cumsumK[4]) {
		Kst[2]=Kst[2]-1
		Kst[3]=Kst[3]+1
	}
	if (cumsumK[4] < ev && ev <= cumsumK[5]) {
		Kst[2]=Kst[2]+1
		Kst[3]=Kst[3]-1
	}
	if (cumsumK[5] < ev && ev <= cumsumK[6]) {
		Kst[3]=Kst[3]-1
		Kst[4]=Kst[4]+1
	}
	if (cumsumK[6] < ev && ev <= cumsumK[7]) {
		Kst[3]=Kst[3]+1
		Kst[4]=Kst[4]-1
	}
    :finally, calculate a random number used to determine the next transition time
    :logarithm is applied immediately
	nextRK = log(scop_random())
}

 
PROCEDURE transNa() { :perform a transition on sodium channels, the same as described for K channels
	ratesNa(v)
    UNITSOFF
    sumrtNa=0
    FROM ii=0 TO 19 {
	  sumrtNa = sumrtNa + Nart[ii]
	  cumsumNa[ii] = sumrtNa
    }
	FROM ii=0 TO 19 {cumsumNa[ii] = cumsumNa[ii] / sumrtNa}
    UNITSON
	ev = scop_random()*1(/ms)
	if (ev <= cumsumNa[0]) {
		Nast[0]=Nast[0]-1
		Nast[1]=Nast[1]+1
	}
	if (cumsumNa[0] < ev && ev <= cumsumNa[1]) {
		Nast[0]=Nast[0]+1
		Nast[1]=Nast[1]-1
	}	
	if (cumsumNa[1] < ev && ev <= cumsumNa[2]) {
		Nast[1]=Nast[1]-1
		Nast[2]=Nast[2]+1
	}
	if (cumsumNa[2] < ev && ev <= cumsumNa[3]) {
		Nast[1]=Nast[1]+1
		Nast[2]=Nast[2]-1
	}	
	if (cumsumNa[3] < ev && ev <= cumsumNa[4]) {
		Nast[2]=Nast[2]-1
		Nast[3]=Nast[3]+1
	}
	if (cumsumNa[4] < ev && ev <= cumsumNa[5]) {
		Nast[2]=Nast[2]+1
		Nast[3]=Nast[3]-1
	}
	if (cumsumNa[5] < ev && ev <= cumsumNa[6]) {
		Nast[0]=Nast[0]-1
		Nast[4]=Nast[4]+1
	}
	if (cumsumNa[6] < ev && ev <= cumsumNa[7]) {
		Nast[0]=Nast[0]+1
		Nast[4]=Nast[4]-1
	}
	if (cumsumNa[7] < ev && ev <= cumsumNa[8]) {
		Nast[1]=Nast[1]-1
		Nast[5]=Nast[5]+1
	}
	if (cumsumNa[8] < ev && ev <= cumsumNa[9]) {
		Nast[1]=Nast[1]+1
		Nast[5]=Nast[5]-1
	}
	if (cumsumNa[9] < ev && ev <= cumsumNa[10]) {
		Nast[2]=Nast[2]-1
		Nast[6]=Nast[6]+1
	}
	if (cumsumNa[10] < ev && ev <= cumsumNa[11]) {
		Nast[2]=Nast[2]+1
		Nast[6]=Nast[6]-1
	}				
	if (cumsumNa[11] < ev && ev <= cumsumNa[12]) {
		Nast[3]=Nast[3]-1
		Nast[7]=Nast[7]+1
	}
	if (cumsumNa[12] < ev && ev <= cumsumNa[13]) {
		Nast[3]=Nast[3]+1
		Nast[7]=Nast[7]-1
	}
	if (cumsumNa[13] < ev && ev <= cumsumNa[14]) {
		Nast[4]=Nast[4]-1
		Nast[5]=Nast[5]+1
	}
	if (cumsumNa[14] < ev && ev <= cumsumNa[15]) {
		Nast[4]=Nast[4]+1
		Nast[5]=Nast[5]-1
	}
	if (cumsumNa[15] < ev && ev <= cumsumNa[16]) {
		Nast[5]=Nast[5]-1
		Nast[6]=Nast[6]+1
	}
	if (cumsumNa[16] < ev && ev <= cumsumNa[17]) {
		Nast[5]=Nast[5]+1
		Nast[6]=Nast[6]-1
	}
	if (cumsumNa[17] < ev && ev <= cumsumNa[18]) {
		Nast[6]=Nast[6]-1
		Nast[7]=Nast[7]+1
	}
	if (cumsumNa[18] < ev && ev <= cumsumNa[19]) {
		Nast[6]=Nast[6]+1
		Nast[7]=Nast[7]-1
	}
    nextRNa=log(scop_random())
}
