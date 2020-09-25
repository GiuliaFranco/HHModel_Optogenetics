COMMENT

na16.mod

Sodium channel, Hodgkin-Huxley style kinetics.

Kinetics were fit to data from Huguenard et al. (1988) and Hamill et
al. (1991)

qi is not well constrained by the data, since there are no points
between -80 and -55.  So this was fixed at 5 while the thi1,thi2,Rg,Rd
were optimized using a simplex least square proc

voltage dependencies are shifted approximately from the best
fit to give higher threshold

Author: Zach Mainen, Salk Institute, 1994, zach@salk.edu

20150512 NTC
Cleaned code up a bit.
Made threadsafe and replaced vtrap0 with efun,
which is a better approximation in the vicinity of a singularity.
See na.mod in ModelDB entry 2488.

Special comment:

This mechanism borrowed heavily from na.mod in ModelDB entry 2488.
That code, which was intended to be used only at 37 deg C 
(see comments from 20120514 in that file),
calculated ionic conductance as the product
  g = tadj*gbar*product_of_gating_variables
where
  tadj = q10^((celsius - temp)/10)
  temp is the "reference temperature" (at which the gating variable
    time constants were originally determined)
  celsius is the "operating temperature"
This deviates from the standard HH formula
  g = gbar*product_of_gating_variables
and has the unfortunate consequence of not only making the 
effective channel density differ from the nominal (i.e. user-assigned) 
channel density, but it would also make the effective channel density
depend on temperature!
Sooner or later this is guaranteed to confound studies of the effects 
of temperature on model operation.
It would also be a debugging nightmare, not least because
the ModelView tool--so handy for discovering the properties of a 
model and verifying a close match between the computational model
and the conceptual model--would report the NOMINAL channel density,
not the effective channel density.

To eliminate this problem, every statement of the form
  g = tadj*gbar*gating variables
has been replaced by 
  g = gbar*gating variables
Furthermore, the numerical value assigned to gbar,
whether by an assignment statement in the PARAMETER block
or by a hoc or Python statement, 
must now use the actual conductance density.
For this particular mechanism, tadj at 37 deg C is 3.20936
so the actual conductance density is 3.20936 times 
the nominal conductance density.
ENDCOMMENT

NEURON {
  THREADSAFE
  SUFFIX na16
  USEION na READ ena WRITE ina
  RANGE m, h, gna, gbar
  GLOBAL tha, thi1, thi2, qa, qi, qinf, thinf
  RANGE minf, hinf, mtau, htau
  GLOBAL Ra, Rb, Rd, Rg
  GLOBAL q10, temp, tadj, vmin, vmax, vshift
}

UNITS {
  (mA) = (milliamp)
  (mV) = (millivolt)
  (pS) = (picosiemens)
  (um) = (micron)
}

PARAMETER {
: this assignment doesn't matter
: if it is overridden by assignments in hoc or Python
  gbar = 1000 (pS/um2) : 0.1 mho/cm2
  vshift = -5 (mV)    : voltage shift (affects all)

  tha  = -43  (mV)    : v 1/2 for act    (-42)
  qa   = 6  (mV)      : act slope
  Ra   = 0.182  (/ms) : open (v)
  Rb   = 0.124  (/ms) : close (v)

  thi1  = -50  (mV)    : v 1/2 for inact
  thi2  = -75  (mV)    : v 1/2 for inact
  qi   = 5  (mV)       : inact tau slope
  thinf  = -72  (mV)   : inact inf slope
  qinf  = 6.2  (mV)    : inact inf slope
  Rg   = 0.0091  (/ms) : inact (v)
  Rd   = 0.024  (/ms)  : inact recov (v)

  temp = 23  (degC)    : original temp
  q10  = 2.3           : temperature sensitivity

:  v     (mV)
:  dt    (ms)
:  celsius    (degC)
  vmin = -120  (mV)
  vmax = 100  (mV)
}

ASSIGNED {
  v      (mV)
  celsius (degC)
  a      (/ms)
  b      (/ms)
  ina    (mA/cm2)
  gna    (pS/um2)
  ena    (mV)
  minf   hinf
  mtau (ms)  htau (ms)
  tadj
}

STATE { m h }

INITIAL {
  : since tadj is a per-thread GLOBAL
  : all threads must calculate its value at initialization
  tadj = q10^((celsius - temp)/(10 (degC)))
  trates(v+vshift)
  m = minf
  h = hinf
}

BREAKPOINT {
  SOLVE states METHOD cnexp
:  gna = tadj*gbar*m*m*m*h
  gna = gbar*m*m*m*h
  ina = (1e-4) * gna * (v - ena)
}

: LOCAL mexp, hexp

DERIVATIVE states {   :Computes state variables m and h
  trates(v+vshift)    :  at the current v
  m' =  (minf-m)/mtau
  h' =  (hinf-h)/htau
:  m = m + mexp*(minf-m)
:  h = h + hexp*(hinf-h)
}

PROCEDURE trates(v (mV)) {
  TABLE minf, hinf, mtau, htau
  DEPEND celsius, temp, Ra, Rb, Rd, Rg, tha, thi1, thi2, qa, qi, qinf
  FROM vmin TO vmax WITH 199

  rates(v): not consistently executed from here if usetable == 1

:  tadj = q10^((celsius - temp)/10)
:  tinc = -dt * tadj

:  mexp = 1 - exp(tinc/mtau)
:  hexp = 1 - exp(tinc/htau)
}

UNITSOFF
PROCEDURE rates(vm (mV)) {
:  LOCAL  a, b

:  a = trap0(vm,tha,Ra,qa)
:  b = trap0(-vm,-tha,Rb,qa)
  a = Ra*qa*efun((tha-vm)/qa)
  b = Rb*qa*efun((vm-tha)/qa)

  tadj = q10^((celsius - temp)/(10 (degC)))

  mtau = 1/tadj/(a+b)
  minf = a/(a+b)

:  mtau = 1/(a+b)
:  minf = a*mtau

  :"h" inactivation

:  a = trap0(vm,thi1,Rd,qi)
:  b = trap0(-vm,-thi2,Rg,qi)
  a = Rd*qi*efun((thi1-vm)/qi)
  b = Rg*qi*efun((vm-thi2)/qi)

  htau = 1/tadj/(a+b)
  hinf = 1/(1+exp((vm-thinf)/qinf))

:  htau = 1/(a+b)
:  hinf = 1/(1+exp((vm-thinf)/qinf))
}

COMMENT
FUNCTION trap0(v,th,a,q) {
:  if (fabs(v/th) > 1e-6) {
  if (fabs((v-th)/q) > 1e-6) {
          trap0 = a * (v - th) / (1 - exp(-(v - th)/q))
  } else {
          trap0 = a * q
   }
}
ENDCOMMENT

FUNCTION efun(z) {
  if (fabs(z) < 1e-6) {
    efun = 1 - z/2
  }else{
    efun = z/(exp(z) - 1)
  }
}
UNITSON
