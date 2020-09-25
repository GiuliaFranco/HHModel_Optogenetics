COMMENT
26 Ago 2002 Modification of original channel to allow variable time step and to correct an initialization error.
    Done by Michael Hines(michael.hines@yale.e) and Ruggero Scorcioni(rscorcio@gmu.edu) at EU Advance Course in Computational Neuroscience. Obidos, Portugal

km.mod

Potassium channel, Hodgkin-Huxley style kinetics
Based on I-M (muscarinic K channel)
Slow, noninactivating

Author: Zach Mainen, Salk Institute, 1995, zach@salk.edu

20150512 NTC
Cleaned code up a bit.
Made threadsafe and added efun to deal with singularity.
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
  SUFFIX km
  USEION k READ ek WRITE ik
  RANGE n, gk, gbar
  RANGE ninf, ntau
  GLOBAL Ra, Rb
  GLOBAL q10, temp, tadj, vmin, vmax
}

UNITS {
  (mA) = (milliamp)
  (mV) = (millivolt)
  (pS) = (picosiemens)
  (um) = (micron)
}

PARAMETER {
  gbar = 10 (pS/um2) : 0.001 mho/cm2
:  v     (mV)

  tha  = -30  (mV)   : v 1/2 for inf
  qa   = 9  (mV)     : inf slope

  Ra   = 0.001 (/ms) : max act rate  (slow)
  Rb   = 0.001 (/ms) : max deact rate  (slow)

:  dt    (ms)
:  celsius    (degC)
  temp = 23  (degC)    : original temp
  q10  = 2.3      : temperature sensitivity

  vmin = -120  (mV)
  vmax = 100  (mV)
}

ASSIGNED {
  v     (mV)
  celsius (degC)
  a     (/ms)
  b     (/ms)
  ik    (mA/cm2)
  gk    (pS/um2)
  ek    (mV)
  ninf
  ntau (ms)
  tadj
}

STATE { n }

INITIAL {
  : since tadj is a per-thread GLOBAL
  : all threads must calculate its value at initialization
  tadj = q10^((celsius - temp)/(10 (degC)))
  trates(v)
  n = ninf
}

BREAKPOINT {
  SOLVE states METHOD cnexp
:  gk = tadj*gbar*n
  gk = gbar*n
  ik = (1e-4) * gk * (v - ek)
}

: LOCAL nexp

DERIVATIVE states { :Computes state variable n
  trates(v)         :  at the current v
  n' = (ninf-n)/ntau
  :n = n + nexp*(ninf-n)
}

PROCEDURE trates(v (mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
  TABLE ninf, ntau
  DEPEND celsius, temp, Ra, Rb, tha, qa
  FROM vmin TO vmax WITH 199

  rates(v): not consistently executed from here if usetable_hh == 1

        :tadj = q10^((celsius - temp)/10)

        :tinc = -dt * tadj
        :nexp = 1 - exp(tinc/ntau)
}

UNITSOFF
PROCEDURE rates(v (mV)) {
:  a = Ra * (v - tha) / (1 - exp(-(v - tha)/qa))
:  b = -Rb * (v - tha) / (1 - exp((v - tha)/qa))

  a = Ra*qa*efun((tha-v)/qa)
  b = Rb*qa*efun((v-tha)/qa)

:  tadj = q10^((celsius - temp)/10)
  tadj = q10^((celsius - temp)/(10 (degC)))

  ntau = 1/tadj/(a+b)
  ninf = a/(a+b)

:        ntau = 1/(a+b)
:  ninf = a*ntau
}

FUNCTION efun(z) {
  if (fabs(z) < 1e-6) {
    efun = 1 - z/2
  }else{
    efun = z/(exp(z) - 1)
  }
}
UNITSON

