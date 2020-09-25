/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__chanrhod
#define _nrn_initial _nrn_initial__chanrhod
#define nrn_cur _nrn_cur__chanrhod
#define _nrn_current _nrn_current__chanrhod
#define nrn_jacob _nrn_jacob__chanrhod
#define nrn_state _nrn_state__chanrhod
#define _net_receive _net_receive__chanrhod 
#define states states__chanrhod 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define channel_density _p[0]
#define Tx _p[1]
#define x _p[2]
#define y _p[3]
#define z _p[4]
#define Ka1 _p[5]
#define Ka2 _p[6]
#define e12 _p[7]
#define e21 _p[8]
#define e12dark _p[9]
#define e21dark _p[10]
#define delta1 _p[11]
#define delta2 _p[12]
#define wavelength _p[13]
#define o10 _p[14]
#define o20 _p[15]
#define icat _p[16]
#define gdens1 _p[17]
#define gdens2 _p[18]
#define irradiance _p[19]
#define flux _p[20]
#define phi _p[21]
#define U _p[22]
#define U0 _p[23]
#define U1 _p[24]
#define Islow _p[25]
#define Ifast _p[26]
#define c_1 _p[27]
#define c_2 _p[28]
#define b _p[29]
#define amp _p[30]
#define photon_energy _p[31]
#define phi0 _p[32]
#define phio _p[33]
#define gcat _p[34]
#define o1 _p[35]
#define o2 _p[36]
#define c1 _p[37]
#define c2 _p[38]
#define Do1 _p[39]
#define Do2 _p[40]
#define Dc1 _p[41]
#define Dc2 _p[42]
#define _g _p[43]
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_chanrhod", _hoc_setdata,
 0, 0
};
 /* declare global and static user variables */
#define Imax Imax_chanrhod
 double Imax = 0;
#define Kr Kr_chanrhod
 double Kr = 0.0004;
#define Kd2 Kd2_chanrhod
 double Kd2 = 0.025;
#define Kd1 Kd1_chanrhod
 double Kd1 = 0.13;
#define c c_chanrhod
 double c = 2.99792e+08;
#define epsilon2 epsilon2_chanrhod
 double epsilon2 = 0.1;
#define epsilon1 epsilon1_chanrhod
 double epsilon1 = 0.5;
#define ecat ecat_chanrhod
 double ecat = 0;
#define gamma gamma_chanrhod
 double gamma = 0.05;
#define gcat2 gcat2_chanrhod
 double gcat2 = 2.5e-15;
#define gcat1 gcat1_chanrhod
 double gcat1 = 5e-14;
#define h h_chanrhod
 double h = 6.62607e-34;
#define sigma_retinal sigma_retinal_chanrhod
 double sigma_retinal = 1.2e-16;
#define source_irradiance source_irradiance_chanrhod
 double source_irradiance = 0;
#define source_flux source_flux_chanrhod
 double source_flux = 0;
#define source_photons source_photons_chanrhod
 double source_photons = 0;
#define tstimoff tstimoff_chanrhod
 double tstimoff = 0;
#define tstimon tstimon_chanrhod
 double tstimon = 0;
#define tChR tChR_chanrhod
 double tChR = 1.3;
#define vshift vshift_chanrhod
 double vshift = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gcat1_chanrhod", "mho",
 "gcat2_chanrhod", "mho",
 "sigma_retinal_chanrhod", "cm2",
 "epsilon1_chanrhod", "1",
 "ecat_chanrhod", "mV",
 "vshift_chanrhod", "mV",
 "tChR_chanrhod", "ms",
 "h_chanrhod", "m2",
 "c_chanrhod", "m/s",
 "source_irradiance_chanrhod", "W/cm2",
 "source_photons_chanrhod", "photons/ms",
 "source_flux_chanrhod", "photons/ms cm2",
 "channel_density_chanrhod", "1/cm2",
 "Tx_chanrhod", "1",
 "x_chanrhod", "1",
 "y_chanrhod", "1",
 "z_chanrhod", "1",
 "delta1_chanrhod", "ms",
 "delta2_chanrhod", "ms",
 "icat_chanrhod", "mA/cm2",
 "gdens1_chanrhod", "mho/cm2",
 "gdens2_chanrhod", "mho/cm2",
 "irradiance_chanrhod", "W/cm2",
 "flux_chanrhod", "photons/ms cm2",
 "phi_chanrhod", "photons/ms",
 0,0
};
 static double c20 = 0;
 static double c10 = 0;
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "gcat1_chanrhod", &gcat1_chanrhod,
 "gcat2_chanrhod", &gcat2_chanrhod,
 "gamma_chanrhod", &gamma_chanrhod,
 "sigma_retinal_chanrhod", &sigma_retinal_chanrhod,
 "epsilon1_chanrhod", &epsilon1_chanrhod,
 "epsilon2_chanrhod", &epsilon2_chanrhod,
 "ecat_chanrhod", &ecat_chanrhod,
 "vshift_chanrhod", &vshift_chanrhod,
 "tChR_chanrhod", &tChR_chanrhod,
 "Kd1_chanrhod", &Kd1_chanrhod,
 "Kd2_chanrhod", &Kd2_chanrhod,
 "Kr_chanrhod", &Kr_chanrhod,
 "h_chanrhod", &h_chanrhod,
 "c_chanrhod", &c_chanrhod,
 "source_irradiance_chanrhod", &source_irradiance_chanrhod,
 "source_photons_chanrhod", &source_photons_chanrhod,
 "source_flux_chanrhod", &source_flux_chanrhod,
 "Imax_chanrhod", &Imax_chanrhod,
 "tstimon_chanrhod", &tstimon_chanrhod,
 "tstimoff_chanrhod", &tstimoff_chanrhod,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[0]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"chanrhod",
 "channel_density_chanrhod",
 "Tx_chanrhod",
 "x_chanrhod",
 "y_chanrhod",
 "z_chanrhod",
 "Ka1_chanrhod",
 "Ka2_chanrhod",
 "e12_chanrhod",
 "e21_chanrhod",
 "e12dark_chanrhod",
 "e21dark_chanrhod",
 "delta1_chanrhod",
 "delta2_chanrhod",
 "wavelength_chanrhod",
 "o10_chanrhod",
 "o20_chanrhod",
 0,
 "icat_chanrhod",
 "gdens1_chanrhod",
 "gdens2_chanrhod",
 "irradiance_chanrhod",
 "flux_chanrhod",
 "phi_chanrhod",
 "U_chanrhod",
 "U0_chanrhod",
 "U1_chanrhod",
 "Islow_chanrhod",
 "Ifast_chanrhod",
 "c_1_chanrhod",
 "c_2_chanrhod",
 "b_chanrhod",
 "amp_chanrhod",
 "photon_energy_chanrhod",
 "phi0_chanrhod",
 "phio_chanrhod",
 "gcat_chanrhod",
 0,
 "o1_chanrhod",
 "o2_chanrhod",
 "c1_chanrhod",
 "c2_chanrhod",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 44, _prop);
 	/*initialize range parameters*/
 	channel_density = 1.3e+10;
 	Tx = 1;
 	x = 0;
 	y = 0;
 	z = 0;
 	Ka1 = 0.5;
 	Ka2 = 0.12;
 	e12 = 0.053;
 	e21 = 0.023;
 	e12dark = 0.022;
 	e21dark = 0.011;
 	delta1 = 0.03;
 	delta2 = 0.15;
 	wavelength = 4.45e-07;
 	o10 = 0;
 	o20 = 0;
 	_prop->param = _p;
 	_prop->param_size = 44;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 1, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _chanrhod_reg() {
	int _vectorized = 0;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 44, 1);
  hoc_register_dparam_semantics(_mechtype, 0, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 chanrhod /Users/giulia/Desktop/FoutzEtAl2012/x86_64/chanrhod.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Four-State Model of chanrhod channel for Subthalamic Nucleus";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[3], _dlist1[3];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   Do1 = Ka1 * c1 - ( Kd1 + e12 ) * o1 + e21 * o2 ;
   Do2 = Ka2 * c2 + e12 * o1 - ( Kd2 + e21 ) * o2 ;
   Dc2 = Kd2 * o2 - ( Ka2 + Kr ) * c2 ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 Do1 = Do1  / (1. - dt*( ( - ( ( Kd1 + e12 ) )*( 1.0 ) ) )) ;
 Do2 = Do2  / (1. - dt*( ( - ( ( Kd2 + e21 ) )*( 1.0 ) ) )) ;
 Dc2 = Dc2  / (1. - dt*( ( - ( ( Ka2 + Kr ) )*( 1.0 ) ) )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
    o1 = o1 + (1. - exp(dt*(( - ( ( Kd1 + e12 ) )*( 1.0 ) ))))*(- ( ( Ka1 )*( c1 ) + ( e21 )*( o2 ) ) / ( ( - ( ( Kd1 + e12 ) )*( 1.0 ) ) ) - o1) ;
    o2 = o2 + (1. - exp(dt*(( - ( ( Kd2 + e21 ) )*( 1.0 ) ))))*(- ( ( Ka2 )*( c2 ) + ( e12 )*( o1 ) ) / ( ( - ( ( Kd2 + e21 ) )*( 1.0 ) ) ) - o2) ;
    c2 = c2 + (1. - exp(dt*(( - ( ( Ka2 + Kr ) )*( 1.0 ) ))))*(- ( ( Kd2 )*( o2 ) ) / ( ( - ( ( Ka2 + Kr ) )*( 1.0 ) ) ) - c2) ;
   }
  return 0;
}
 
static int _ode_count(int _type){ return 3;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 ();
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 3; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 ();
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  c2 = c20;
  c1 = c10;
  o2 = o20;
  o1 = o10;
 {
   irradiance = 0.0 ;
   flux = 0.0 ;
   phi = 0.0 ;
   Islow = 0.0 ;
   Ifast = 0.0 ;
   tstimon = 0.0 ;
   tstimoff = 0.0 ;
   c1 = 1.0 ;
   c2 = 0.0 ;
   o1 = 0.0 ;
   o2 = 0.0 ;
   phio = 0.0 ;
   o10 = 0.0 ;
   o20 = 0.0 ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   irradiance = source_irradiance * Tx ;
   flux = source_flux * Tx ;
   phi = flux * sigma_retinal ;
   U = v - ecat - vshift - 75.0 ;
   U0 = 40.0 ;
   U1 = 15.0 ;
   Imax = ( v - ecat - vshift ) * gcat1 * channel_density ;
   b = ( Kd1 + Kd2 + e12dark + e21dark ) / 2.0 ;
   c_1 = 0.1029797709 ;
   c_2 = 0.0398631371 ;
   gcat = ( o1 + gamma * o2 ) * gcat1 * channel_density ;
   if ( phi > 0.0 ) {
     Ka1 = epsilon1 * phi * ( 1.0 - exp ( - ( t - tstimon ) / tChR ) ) ;
     Ka2 = epsilon2 * phi * ( 1.0 - exp ( - ( t - tstimon ) / tChR ) ) ;
     e12 = 0.053 ;
     e21 = 0.023 ;
     icat = Imax * ( o1 + gamma * o2 ) * ( 1.0 - exp ( - U / U0 ) ) / ( U / U1 ) ;
     o10 = o1 ;
     o20 = o2 ;
     phio = phi ;
     }
   else {
     Ka1 = epsilon1 * phio * ( exp ( - ( ( t - tstimoff ) / tChR ) ) - exp ( - ( t - tstimon ) / tChR ) ) ;
     Ka2 = epsilon2 * phio * ( exp ( - ( ( t - tstimoff ) / tChR ) ) - exp ( - ( t - tstimon ) / tChR ) ) ;
     e12 = 0.022 ;
     e21 = 0.011 ;
     Islow = Imax * ( ( ( delta2 - ( Kd1 + ( 1.0 - gamma ) * e12dark ) ) * o10 + ( ( 1.0 - gamma ) * e21dark + gamma * ( delta2 - Kd2 ) ) * o20 ) / ( delta2 - delta1 ) ) ;
     Ifast = Imax * ( ( ( Kd1 + ( 1.0 - gamma ) * e12dark - delta1 ) * o10 + ( - ( 1.0 - gamma ) * e21dark + gamma * ( Kd2 - delta1 ) ) * o20 ) / ( delta2 - delta1 ) ) ;
     icat = Islow * exp ( - delta1 * ( t - tstimoff ) ) + Ifast * exp ( - delta2 * ( t - tstimoff ) ) ;
     }
   if ( o1 > 1.0 ) {
     o1 = 1.0 ;
     }
   if ( o1 < 0.0 ) {
     o1 = 0.0 ;
     }
   if ( o2 > 1.0 ) {
     o2 = 1.0 ;
     }
   if ( o2 < 0.0 ) {
     o2 = 0.0 ;
     }
   if ( c1 > 1.0 ) {
     c1 = 1.0 ;
     }
   if ( c1 < 0.0 ) {
     c1 = 0.0 ;
     }
   if ( c2 > 1.0 ) {
     c2 = 1.0 ;
     }
   if ( c2 < 0.0 ) {
     c2 = 0.0 ;
     }
   c1 = 1.0 - o1 - o2 - c2 ;
   }
 _current += icat;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 { error =  states();
 if(error){fprintf(stderr,"at line 205 in file chanrhod.mod:\n    SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(o1) - _p;  _dlist1[0] = &(Do1) - _p;
 _slist1[1] = &(o2) - _p;  _dlist1[1] = &(Do2) - _p;
 _slist1[2] = &(c2) - _p;  _dlist1[2] = &(Dc2) - _p;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/giulia/Desktop/FoutzEtAl2012/chanrhod.mod";
static const char* nmodl_file_text = 
  "TITLE Four-State Model of chanrhod channel for Subthalamic Nucleus\n"
  "\n"
  "UNITS {\n"
  "    (mV) = (millivolt)\n"
  "    (mA) = (milliamp)\n"
  "    (nA) = (nanoamp)\n"
  "    (mW) = (milliwatt)\n"
  "    (photons)  = (1)\n"
  "}\n"
  "\n"
  "NEURON { :public interface of the mechanism\n"
  "	SUFFIX chanrhod\n"
  "	:Name of the Channel\n"
  "    NONSPECIFIC_CURRENT	icat\n"
  "    :Specific Channel for Na, Ca, K\n"
  "    RANGE photons, flux, irradiance, U, U0, U1\n"
  "    :Calculated optics values given source_values\n"
  "    RANGE channel_density, gdens1, gdens2\n"
  "    :Channel density and conductance. gdens1 = density conductance for o1. gdens2 = density conductance for o2\n"
  "    RANGE x, y, z\n"
  "    :Location of that segment (of nsegs)\n"
  "	:RANGE Ka1, Ka2, Kd1, Kd2, e12, e21, e12dark, e21dark, Kr, delta1, delta2, o10, o20, Islow, Ifast, c_1, c_2, b, h, c, amp, photon_energy, wavelength, phi0, phio, gcat\n"
  "	:Various Rate Constants, phi0:constant, phio: static value of phi\n"
  "    GLOBAL source_photons, source_flux, source_irradiance\n"
  "    :Optical Input\n"
  "    RANGE Ka1, Ka2\n"
  "    GLOBAL Kd1, Kd2\n"
  "    GLOBAL Kr\n"
  "    RANGE e12, e21, e12dark, e21dark\n"
  "    RANGE delta1, delta2\n"
  "    RANGE o10, o20\n"
  "    RANGE Islow, Ifast\n"
  "    RANGE c_1, c_2, b\n"
  "    GLOBAL h, c\n"
  "    RANGE amp, photon_energy\n"
  "    RANGE wavelength\n"
  "    RANGE phi0, phio, gcat    \n"
  "    GLOBAL sigma_retinal, gcat1, gcat2, ecat, Imax, gamma, tChR\n"
  "    :sigma_retinal = cross-sectional area of chanrhod, gcat1/2 = single channel conductance of chanrhod, ecat = nernst potential for chanrhod, Imax=maximum current if all channels are in o1, gamma=g2/g1\n"
  "    GLOBAL epsilon1, epsilon2\n"
  "    :epsilon1,2 = quantum efficiency for ka1, ka2\n"
  "    RANGE Tx, phi\n"
  "    :Tx = Transfer Resistance between two point locations assuming homogenous tissue (V=ITx), phi = photon flux / channel, phi = flux x Tx, flux = irradiance x cross section of retinal\n"
  "    GLOBAL tstimon, tstimoff\n"
  "}\n"
  "\n"
  ":NEURON doesn't change ion concentrations automatically - need another mechanism that will write cai and cao\n"
  "\n"
  "PARAMETER {\n"
  "    :channel_density        = 0\n"
  "    channel_density        = 1.3e10              (1/cm2) : variable : number of channels per cm2\n"
  "    : 2e9 per oocyte : Nagel 2003\n"
  "    : 100 ChR2s/um2 = 1e10 (Grossman 2011)\n"
  "\n"
  "    :gcat1    = 40e-15    (mho)   40 fS\n"
  "    :gcat2    = 40e-15    (mho)   40 fS\n"
  "    gcat1    = 50e-15    (mho)   : (Grossman 2011) 50 fS\n"
  "    gcat2    = 250e-17   (mho)   : Figure 8 Nickolic 2009\n"
  "    :g=150e-15 (mho) 15fA at -100mV (Harz 1992, Feldbauer 2009, Lin 2009)\n"
  "    : 100 fS : Channelrhodopsins: Molecular Properties and Applications Ernst Bamberg, PhD\n"
  "    : single-channel conductance of ~=50 fS : Channelrhodopsin-2, a directly light-gated cation-selective membrane channel Georg Nagel\n"
  "    : A value of 40 fS was obtained : Channelrhodopsin-2 is a leaky proton pump Katrin Feldbauer\n"
  "\n"
  "    gamma=0.05 : Figure 8 Nickolic 2009\n"
  "\n"
  "    sigma_retinal = 1.2e-16  (cm2)        : 1.2e-8 um2 which is cross-sectional area of retinal\n"
  "\n"
  "    epsilon1 = 0.5             (1)         : quantum efficiency of ChR-2 system : A typical value would be e 0.5 for rhodopsin; nikolic 2009, Hegemann (1999), Constant Value (Nikolic 2009)\n"
  "	:epsilon2 = 0.12                        : (Grossman 2011)\n"
  "	epsilon2 = 0.1                      : Figure 8 at source_irradiance = 0.9 mW/mm2 (Nikolic 2009)\n"
  "    ecat     = 0      (mV)     : Nagel 2003\n"
  "                               : -42 mV: Kang, Y., Okada, T., Ohmori, H., 1998. A phenytoin-sensitive cationic current... 1998.\n"
  "                               : -48 mV: Christian Alzheimer, A novelvoltage-dependentcationcurrentinratneocortical neurones. 1994.\n"
  "\n"
  "    Tx      = 1       (1)      : Default light \"transfer resistance\" between optrode and compartment; geometry dependent\n"
  "    vshift  = 0        (mV)     : Adjust the voltage for different resting potentials (resting potential of pyramidal cell is -65 and of fiber tract is -70)\n"
  "\n"
  "	:tChR=0.2 (ms) : Volvox - Figure 8 (Nickolic 2009)\n"
  "	tChR=1.3 (ms) : Axons (Nickolic 2009)\n"
  "\n"
  "    x = 0 (1) : spatial coords\n"
  "	y = 0 (1)\n"
  "	z = 0 (1)\n"
  "	Ka1 = 0.5 :(Grossman 2011)\n"
  "	Ka2 = 0.12 :(Grossman 2011)\n"
  "\n"
  "	:Kd1 = 0.1 : Constant Value (Grossman 2011)\n"
  "	:Kd2 = 0.05 : Constant Value (Grossman 2011)\n"
  "	Kd1 = 0.13 : Figure 8 at source_irradiance = 0.9 mW/mm2 (Nikolic 2009) - 0.09W/cm2\n"
  "	Kd2 = 0.025 : Figure 8 at source_irradiance = 0.9 mW/mm2 (Nikolic 2009)\n"
  "\n"
  "	Kr = 0.0004 : Figure 8 (Nikolic 2009)\n"
  "\n"
  "	e12 = 0.053 : Figure 8 at source_irradiance = 0.9 mW/mm2 (Nikolic 2009)\n"
  "	e21 = 0.023 : Figure 8 at source_irradiance = 0.9 mW/mm2 (Nikolic 2009)\n"
  "	e12dark = 0.022\n"
  "	e21dark = 0.011\n"
  "\n"
  "	delta1= 0.03 (ms): Figure 8 (Nikolic 2009)\n"
  "	delta2= 0.15 (ms): Figure 8 (Nikolic 2009)\n"
  "\n"
  "	h = 6.6260693e-34           (m2 kg/s)  : planck's constant\n"
  "    c = 299792458.0             (m/s)      : speed of light\n"
  "	wavelength = 4.45e-7\n"
  "}\n"
  "\n"
  "ASSIGNED {  :calculated by the mechanism (computed by NEURON)\n"
  "    v           (mV)\n"
  "    icat        (mA/cm2)\n"
  "    gdens1        (mho/cm2)\n"
  "    gdens2        (mho/cm2)\n"
  "    source_irradiance  (W/cm2)      : Light irradiance (W/mm2) exiting optrode, from ostim.mod\n"
  "    source_photons     (photons/ms) : number of photons exiting optrode per millisecond, from ostim.mod\n"
  "    source_flux        (photons/ms cm2) : flux of photons exiting optrode per millisecond, from ostim.mod\n"
  "    irradiance          (W/cm2)      : number of photons exiting optrode per millisecond, from ostim.mod\n"
  "    flux               (photons/ms cm2) : number of photons exiting optrode per millisecond, from ostim.mod\n"
  "    phi                (photons/ms) : number of photons hitting channel per millisecond\n"
  "    U\n"
  "    U0\n"
  "    U1\n"
  "    Imax\n"
  "    Islow\n"
  "    Ifast\n"
  "    c_1\n"
  "    c_2\n"
  "    b\n"
  "    amp\n"
  "    photon_energy\n"
  "    phi0\n"
  "    phio\n"
  "    gcat\n"
  "    tstimon\n"
  "    tstimoff\n"
  "}\n"
  "\n"
  "STATE { :state or independent variables\n"
  "	o1 o2 c1 c2\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    irradiance = 0\n"
  "    flux = 0\n"
  "    phi = 0\n"
  "    Islow=0\n"
  "    Ifast=0\n"
  "    :gdens1 = gcat1 * channel_density : (mho/cm2)\n"
  "	:gdens2 = gcat2 * channel_density : (mho/cm2)\n"
  "    tstimon = 0\n"
  "    tstimoff = 0\n"
  "\n"
  "    : STATES\n"
  "	c1 = 1 :Amount of channels at initial time\n"
  "	c2 = 0\n"
  "	o1 = 0\n"
  "	o2 = 0\n"
  "\n"
  "	phio = 0\n"
  "    o10=0\n"
  "    o20=0\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    irradiance = source_irradiance * Tx : (W/cm2)\n"
  "    flux      = source_flux * Tx           : (photons/ms cm2)\n"
  "    phi       = flux             * sigma_retinal\n"
  "                : (photons/ms cm2) * (cm2)\n"
  "                :  --> (photons/ms / channel)\n"
  "\n"
  "	U=v-ecat-vshift-75\n"
  "	U0=40\n"
  "	U1=15\n"
  "	Imax=(v-ecat-vshift)*gcat1*channel_density : mA/cm2\n"
  "\n"
  "    b= (Kd1+Kd2+e12dark+e21dark)/2\n"
  "\n"
  "    c_1 = 0.1029797709\n"
  "    c_2 = 0.0398631371\n"
  "\n"
  "    gcat=(o1+gamma*o2)*gcat1*channel_density\n"
  "\n"
  "	if (phi>0) {\n"
  "		Ka1 = epsilon1 * phi * (1 - exp( -(t - tstimon) / tChR)) :Need to add t-td for optical stimulation starting after t=0\n"
  "		Ka2 = epsilon2 * phi * (1 - exp( -(t - tstimon) / tChR))\n"
  "		:e12 = 0.011 + 0.005*log(phi/0.024) :(Grossman 2011) - have to use at suprathreshold phi values - need to have equation for phi at certain properities?\n"
  "		:e21 = 0.008 + 0.004*log(phi/0.024) :(Grossman 2011)\n"
  "		e12=0.053\n"
  "		e21=0.023\n"
  "		:e12 = e12dark + c_1*log10(1+phi/phi0) : e12=0.053 phi>0, e12=0.022 phi=0\n"
  "   		:e21 = e21dark + c_2*log10(1+phi/phi0) : e21=0.023 phi>0, e21=0.011 phi=0\n"
  "		icat = Imax * (o1 + gamma * o2) * (1-exp(-U/U0))/(U/U1) : (mA/cm2)\n"
  "		o10=o1\n"
  "		o20=o2\n"
  "		phio=phi\n"
  "	} else {\n"
  "		Ka1 = epsilon1 * phio * (exp (- ((t-tstimoff) / tChR)) - exp( -(t - tstimon) / tChR) ) : 500ms duration light pulse - very rapidly drops off due to long duration pulse and short tChR\n"
  "		Ka2 = epsilon2 * phio * (exp (- ((t-tstimoff) / tChR)) - exp( -(t - tstimon) / tChR) ) : 500ms duration light pulse\n"
  "		e12 = 0.022\n"
  "		e21 = 0.011\n"
  "		:icat = Imax * (o1 + gamma * o2) * (1-exp(-U/U0))/(U/U1) : (mA/cm2)\n"
  "    	Islow = Imax * ( ( (delta2 - (Kd1 + (1 - gamma) * e12dark)) * o10 + (( 1 - gamma) * e21dark + gamma*(delta2-Kd2)) * o20 ) / (delta2 - delta1) )\n"
  "    	Ifast = Imax * ( ( (Kd1 + (1 - gamma) * e12dark - delta1) * o10 + (-(1 - gamma)*e21dark+gamma*(Kd2-delta1))*o20 ) / (delta2 - delta1) )\n"
  "    	icat = Islow * exp(-delta1*(t-tstimoff)) + Ifast*exp(-delta2*(t-tstimoff)) : (mA/cm2)\n"
  "	}\n"
  "\n"
  "    SOLVE states METHOD cnexp\n"
  "    if (o1>1){o1=1}\n"
  "    if (o1<0){o1=0}\n"
  "	if (o2>1){o2=1}\n"
  "    if (o2<0){o2=0}\n"
  "    if (c1>1){c1=1}\n"
  "    if (c1<0){c1=0}\n"
  "    if (c2>1){c2=1}\n"
  "    if (c2<0){c2=0}\n"
  "    c1    = 1 - o1 - o2 - c2\n"
  "}\n"
  "\n"
  "DERIVATIVE states {  :states the set of diffy qs\n"
  "	o1' = Ka1*c1 - (Kd1 + e12)*o1 + e21*o2\n"
  "	o2' = Ka2*c2 + e12*o1 - (Kd2+e21)*o2\n"
  "	:c1' = c1* (Kd1 - Ka1) + c2 * Kr\n"
  "	c2' = Kd2*o2 - (Ka2+Kr)*c2\n"
  "}\n"
  ;
#endif
