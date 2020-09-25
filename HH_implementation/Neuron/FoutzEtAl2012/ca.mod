COMMENT
26 Ago 2002 Modification of original channel to allow variable time step and to correct an initialization error.
    Done by Michael Hines(michael.hines@yale.e) and Ruggero Scorcioni(rscorcio@gmu.edu) at EU Advance Course in Computational Neuroscience. Obidos, Portugal

ca.mod
Uses fixed eca instead of GHK eqn

HVA Ca current
Based on Reuveni, Friedman, Amitai and Gutnick (1993) J. Neurosci. 13:
4609-4621.

Author: Zach Mainen, Salk Institute, 1994, zach@salk.edu

20150512 NTC
Cleaned code up a bit.
Made threadsafe, and applied existing FUNCTION efun to deal 
with a singularity.
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
  SUFFIX ca
  USEION ca READ eca WRITE ica
  RANGE m, h, gca, gbar
  RANGE minf, hinf, mtau, htau
  GLOBAL q10, temp, tadj, vmin, vmax, vshift
}

UNITS {
  (mA) = (milliamp)
  (mV) = (millivolt)
  (pS) = (picosiemens)
  (um) = (micron)
  (mM) = (milli/liter)
  FARADAY = (faraday) (coulomb)
  R = (k-mole) (joule/degC)
  PI  = (pi) (1)
}

PARAMETER {
  gbar = 0.1 (pS/um2) : 1e-5 mho/cm2
  vshift = 0  (mV)    : voltage shift (affects all)

  cao  = 2.5  (mM)    : external ca concentration
  cai    (mM)

  temp = 23  (degC)   : original temp
  q10  = 2.3          : temperature sensitivity

:  v     (mV)
:  dt    (ms)
:  celsius    (degC)
  vmin = -120  (mV)
  vmax = 100  (mV)
}

ASSIGNED {
  v    (mV)
  celsius (degC)
  a    (/ms)
  b    (/ms)
  ica  (mA/cm2)
  gca  (pS/um2)
  eca  (mV)
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
:  gca = tadj*gbar*m*m*h
  gca = gbar*m*m*h
  ica = (1e-4) * gca * (v - eca)
}

: LOCAL mexp, hexp

:PROCEDURE states() {
:        trates(v+vshift)
:        m = m + mexp*(minf-m)
:        h = h + hexp*(hinf-h)
:  VERBATIM
:  return 0;
:  ENDVERBATIM
:}

DERIVATIVE states {
  trates(v+vshift)
  m' =  (minf-m)/mtau
  h' =  (hinf-h)/htau
}

PROCEDURE trates(v (mV)) {
  TABLE minf, hinf, mtau, htau
  DEPEND celsius, temp
  FROM vmin TO vmax WITH 199

  rates(v): not consistently executed from here if usetable == 1

:        tadj = q10^((celsius - temp)/10)
:        tinc = -dt * tadj

:        mexp = 1 - exp(tinc/mtau)
:        hexp = 1 - exp(tinc/htau)
}

UNITSOFF
PROCEDURE rates(vm (mV)) {
:        LOCAL  a, b

:  tadj = q10^((celsius - temp)/10)
  tadj = q10^((celsius - temp)/(10 (degC)))

:  a = 0.055*(-27 - vm)/(exp((-27-vm)/3.8) - 1)
  a = 0.055*3.8*efun(-(27 + vm)/3.8)
  b = 0.94*exp((-75-vm)/17)

  mtau = 1/tadj/(a+b)
  minf = a/(a+b)

  :"h" inactivation

  a = 0.000457*exp((-13-vm)/50)
  b = 0.0065/(exp((-vm-15)/28) + 1)

  htau = 1/tadj/(a+b)
  hinf = a/(a+b)
}

FUNCTION efun(z) {
:  if (fabs(z) < 1e-4) {
  if (fabs(z) < 1e-6) {
    efun = 1 - z/2
  }else{
    efun = z/(exp(z) - 1)
  }
}
UNITSON

