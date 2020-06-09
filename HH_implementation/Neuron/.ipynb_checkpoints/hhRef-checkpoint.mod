TITLE hh.mod   squid sodium, potassium, and leak channels
 
COMMENT
Stochastic Hodgkin and Huxley equations with diffusion aproximation using a reflection method to correct normalization and bounding of variables (hhRef)
Equations as in Dangerfield, Kay & Burrage (2012) Phy Rev E 85:051907-1
 DOI: 10.1103/PhysRevE.85.051907
Implemented for Pezo, Soudry and Orio (2014) Front Comp Neurosci 

ENDCOMMENT
 
UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
	(S) = (siemens)
}
 
NEURON {
	SUFFIX hhRef
	USEION na READ ena WRITE ina
	USEION k READ ek WRITE ik
	NONSPECIFIC_CURRENT il
	RANGE gnabar, gkbar, gl, el, NNa, NK, contm, contn, se
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
	R[14]	(/ms)
	contm
	contn
}
 
STATE {	
	mh0
	mh1
	mh2
	mh3
	mh4
	mh5
	mh6
	mh7
	n0
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
	if (se>0) {set_seed(se)}
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
	contm = 0
	contn = 0
	rates(v)
}

DERIVATIVE states {  
	rates(v)

	mh0' = (-3*am-ah)*mh0 + bm*mh1 + bh*mh4 + R[0]+R[3]
	mh1' = (-2*am-bm-ah)*mh1 + 3*am*mh0 + 2*bm*mh2 + bh*mh5 -R[0]+R[1]+R[4]	
	mh2' = (-am-2*bm-ah)*mh2 + 2*am*mh1 + 3*bm*mh3 + bh*mh6 -R[1]+R[2]+R[5]
	mh3' = (-3*bm-ah)*mh3 + am*mh2 + bh*mh7 -R[2]+R[6]
	mh4' = (-3*am-bh)*mh4 + bm*mh5 + ah*mh0 + R[7]-R[3]
    	mh5' = (-2*am-bm-bh)*mh5 + 3*am*mh4 + 2*bm*mh6 + ah*mh1 -R[7]+R[8]-R[4]
    	mh6' = (-am-2*bm-bh)*mh6 + 2*am*mh5 + 3*bm*mh7 + ah*mh2 -R[8]+R[9]-R[5]
    	mh7' = (-3*bm-bh)*mh7 + am*mh6 + ah*mh3 -R[9]-R[6]
	
	n0' = -4*an*n0 + bn*n1 + R[10]
	n1' = (-3*an-bn)*n1 + 4*an*n0 + 2*bn*n2 - R[10] + R[11]
	n2' = (-2*an-2*bn)*n2 + 3*an*n1 + 3*bn*n3 -R[11] + R[12]
	n3' = (-an-3*bn)*n3 + 2*an*n2 + 4*bn*n4 -R[12] + R[13]
	n4' = -4*bn*n4 + an*n3 -R[13]

  	projection()
}
 
LOCAL q10

PROCEDURE projection() { :Computes projection
	LOCAL summh, sumn, im, jm, flagm, flagn, w, k, tem, ii, jj, tmax, tsum, kk, bget, MH[8], N[5], Maux[8], Naux[5]
	UNITSOFF
	MH[0]=mh0
	MH[1]=mh1
	MH[2]=mh2
	MH[3]=mh3
	MH[4]=mh4
	MH[5]=mh5
	MH[6]=mh6
	MH[7]=mh7
	N[0]=n0
	N[1]=n1
	N[2]=n2
	N[3]=n3
	N[4]=n4

	:::::::M:::::::
	summh = 0
	flagm = 0
	FROM im=0 TO 7 {
		summh = summh + MH[im]
		if (MH[im]<0 || MH[im]>1) {flagm = flagm + 1} :check boundary constraint
		Maux[im]=MH[im]
	}

	w=0
	if (summh != 1 || flagm != 0) {  :only if one of the constraints is broken
		while (w != (8-1)) {
			w=0
            :::::::Sort M:::::::
			FROM k = 0 TO (8-2) {
				if (MH[k]>=MH[k+1]) {
					w=w+1
				} else{
					tem = MH[k]
					MH[k] = MH[k+1]
					MH[k+1] = tem
				}
			}
		}
	   :::::::Project M:::::::
		bget = 0
		tsum = 0
		FROM ii = 0 TO 6 {
			tsum = tsum + MH[ii]
			tmax = (tsum - 1)/(ii+1)
			if (tmax > MH[ii+1]){
				bget = 1
				VERBATIM
				break;
				ENDVERBATIM
			}
		}
		if (bget==0) {tmax = (tsum + MH[7] -1)/8} 
		FROM kk=0 TO 7 {
			if (Maux[kk]>tmax) {
				MH[kk]=Maux[kk]-tmax
			} else {
				MH[kk]=0
			}
		}
		contm=contm+1 :count the times m is projected
	}

	:::::::N:::::::
	sumn = 0
	flagn = 0
	FROM jm=0 TO 4 {
		sumn = sumn + N[jm]
		if (N[jm]<0 || N[jm]>1) {flagn = flagn + 1}		
		Naux[jm]=N[jm]
	}
	:::::::Sort N:::::::
	w=0
	if (sumn != 1 || flagn != 0) {
		while (w != (5-1)) {
			w=0
			FROM k = 0 TO (5-2) {
				if (N[k]>=N[k+1]) {
					w=w+1
				} else{
					tem = N[k]
					N[k] = N[k+1]
					N[k+1] = tem
				}
			}
		}
	:::::::Proyect N:::::::
	bget = 0
	tsum = 0
	FROM jj = 0 TO 3 {
		tsum = tsum + N[jj]
		tmax = (tsum - 1)/(jj+1)
			if (tmax > N[jj+1]){
				bget = 1
				VERBATIM
				break;
				ENDVERBATIM
			}
		}
	if (bget==0) {tmax = (tsum + N[4] -1)/5} 
	FROM kk=0 TO 4 {
		if (Naux[kk]>tmax) {
			N[kk]=Naux[kk]-tmax
		} else {
			N[kk]=0
			}
		}
		contn=contn+1 :count the times n is projected
	}
	
	:::::::Deliver projection:::::::
	mh0=MH[0]
	mh1=MH[1]
	mh2=MH[2]
	mh3=MH[3]
	mh4=MH[4]
	mh5=MH[5]
	mh6=MH[6]
	mh7=MH[7]
	n0=N[0]
	n1=N[1]
	n2=N[2]
	n3=N[3]
	n4=N[4]
	UNITSON
}

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
	R[0] = R[0]*sqrt(3*am*mh0+bm*mh1)
	R[1] = R[1]*sqrt(2*am*mh1+2*bm*mh2)
	R[2] = R[2]*sqrt(am*mh2+3*bm*mh3)
	R[3] = R[3]*sqrt(ah*mh0+bh*mh4)
	R[4] = R[4]*sqrt(ah*mh1+bh*mh5)
	R[5] = R[5]*sqrt(ah*mh2+bh*mh6)
	R[6] = R[6]*sqrt(ah*mh3+bh*mh7)
	R[7] = R[7]*sqrt(3*am*mh4+bm*mh5)
	R[8] = R[8]*sqrt(2*am*mh5+2*bm*mh6)
	R[9] = R[9]*sqrt(am*mh6+3*bm*mh7)
	R[10] = R[10]*sqrt(4*an*n0+bn*n1)
	R[11] = R[11]*sqrt(3*an*n1+2*bn*n2)
	R[12] = R[12]*sqrt(2*an*n2+3*bn*n3)
	R[13] = R[13]*sqrt(an*n3+4*bn*n4)
	UNITSON 
}
