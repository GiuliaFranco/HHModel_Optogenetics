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
 
#define nrn_init _nrn_init__hhMC
#define _nrn_initial _nrn_initial__hhMC
#define nrn_cur _nrn_cur__hhMC
#define _nrn_current _nrn_current__hhMC
#define nrn_jacob _nrn_jacob__hhMC
#define nrn_state _nrn_state__hhMC
#define _net_receive _net_receive__hhMC 
#define mula mula__hhMC 
#define ratesK ratesK__hhMC 
#define ratesNa ratesNa__hhMC 
#define transK transK__hhMC 
#define transNa transNa__hhMC 
 
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
#define se _p[0]
#define gnabar _p[1]
#define gkbar _p[2]
#define gl _p[3]
#define el _p[4]
#define NNa _p[5]
#define NK _p[6]
#define il _p[7]
#define Nast (_p + 8)
#define Kst (_p + 16)
#define next_evNa _p[21]
#define next_evK _p[22]
#define nextRK _p[23]
#define nextRNa _p[24]
#define mock _p[25]
#define ena _p[26]
#define ek _p[27]
#define ina _p[28]
#define ik _p[29]
#define alpha_m _p[30]
#define alpha_h _p[31]
#define alpha_n _p[32]
#define beta_m _p[33]
#define beta_h _p[34]
#define beta_n _p[35]
#define Nart (_p + 36)
#define Krt (_p + 56)
#define sumrtNa _p[64]
#define sumrtK _p[65]
#define cumsumNa (_p + 66)
#define cumsumK (_p + 86)
#define prev_evNa _p[94]
#define prev_evK _p[95]
#define ev _p[96]
#define M _p[97]
#define N _p[98]
#define H _p[99]
#define Dmock _p[100]
#define _g _p[101]
#define _ion_ena	*_ppvar[0]._pval
#define _ion_ina	*_ppvar[1]._pval
#define _ion_dinadv	*_ppvar[2]._pval
#define _ion_ek	*_ppvar[3]._pval
#define _ion_ik	*_ppvar[4]._pval
#define _ion_dikdv	*_ppvar[5]._pval
 
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
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_ratesK(void);
 static void _hoc_ratesNa(void);
 static void _hoc_transK(void);
 static void _hoc_transNa(void);
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
 "setdata_hhMC", _hoc_setdata,
 "ratesK_hhMC", _hoc_ratesK,
 "ratesNa_hhMC", _hoc_ratesNa,
 "transK_hhMC", _hoc_transK,
 "transNa_hhMC", _hoc_transNa,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "gl_hhMC", 0, 1e+09,
 "gkbar_hhMC", 0, 1e+09,
 "gnabar_hhMC", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gnabar_hhMC", "S/cm2",
 "gkbar_hhMC", "S/cm2",
 "gl_hhMC", "S/cm2",
 "el_hhMC", "mV",
 "il_hhMC", "mA/cm2",
 "next_evNa_hhMC", "ms",
 "next_evK_hhMC", "ms",
 0,0
};
 static double delta_t = 0.01;
 static double mock0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
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
 
#define _cvode_ieq _ppvar[6]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"hhMC",
 "se_hhMC",
 "gnabar_hhMC",
 "gkbar_hhMC",
 "gl_hhMC",
 "el_hhMC",
 "NNa_hhMC",
 "NK_hhMC",
 0,
 "il_hhMC",
 "Nast_hhMC[8]",
 "Kst_hhMC[5]",
 "next_evNa_hhMC",
 "next_evK_hhMC",
 "nextRK_hhMC",
 "nextRNa_hhMC",
 0,
 "mock_hhMC",
 0,
 0};
 static Symbol* _na_sym;
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 102, _prop);
 	/*initialize range parameters*/
 	se = -1;
 	gnabar = 0.12;
 	gkbar = 0.036;
 	gl = 0.0003;
 	el = -54.3;
 	NNa = 5000;
 	NK = 1600;
 	_prop->param = _p;
 	_prop->param_size = 102;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 7, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[3]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[4]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[5]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _hhMC_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("na", -10000.);
 	ion_reg("k", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 102, 7);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 6, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 hhMC /Users/giulia/Desktop/Tesi/VagrantNeuro/TutorialsNeuron_and_Brian/DAcomparison/HH/Neuron/x86_64/hhMC.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double _zq10 ;
static int _reset;
static char *modelname = "hh.mod   squid sodium, potassium, and leak channels";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int ratesK(double);
static int ratesNa(double);
static int transK();
static int transNa();
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int mula(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   ratesNa ( _threadargscomma_ v ) ;
   next_evNa = prev_evNa - nextRNa / sumrtNa ;
   while ( t >= next_evNa ) {
     transNa ( _threadargs_ ) ;
     prev_evNa = next_evNa ;
     next_evNa = prev_evNa - nextRNa / sumrtNa ;
     }
   ratesK ( _threadargscomma_ v ) ;
   next_evK = prev_evK - nextRK / sumrtK ;
   while ( t >= next_evK ) {
     transK ( _threadargs_ ) ;
     prev_evK = next_evK ;
     next_evK = prev_evK - nextRK / sumrtK ;
     }
   Dmock = 0.0 ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 ratesNa ( _threadargscomma_ v ) ;
 next_evNa = prev_evNa - nextRNa / sumrtNa ;
 while ( t >= next_evNa ) {
   transNa ( _threadargs_ ) ;
   prev_evNa = next_evNa ;
   next_evNa = prev_evNa - nextRNa / sumrtNa ;
   }
 ratesK ( _threadargscomma_ v ) ;
 next_evK = prev_evK - nextRK / sumrtK ;
 while ( t >= next_evK ) {
   transK ( _threadargs_ ) ;
   prev_evK = next_evK ;
   next_evK = prev_evK - nextRK / sumrtK ;
   }
 Dmock = Dmock  / (1. - dt*( 0.0 )) ;
  return 0;
}
 /*END CVODE*/
 static int mula () {_reset=0;
 {
   ratesNa ( _threadargscomma_ v ) ;
   next_evNa = prev_evNa - nextRNa / sumrtNa ;
   while ( t >= next_evNa ) {
     transNa ( _threadargs_ ) ;
     prev_evNa = next_evNa ;
     next_evNa = prev_evNa - nextRNa / sumrtNa ;
     }
   ratesK ( _threadargscomma_ v ) ;
   next_evK = prev_evK - nextRK / sumrtK ;
   while ( t >= next_evK ) {
     transK ( _threadargs_ ) ;
     prev_evK = next_evK ;
     next_evK = prev_evK - nextRK / sumrtK ;
     }
    mock = mock - dt*(- ( 0.0 ) ) ;
   }
  return 0;
}
 
static int  ratesNa (  double _lv ) {
    _zq10 = pow( 3.0 , ( ( celsius - 6.3 ) / 10.0 ) ) ;
   alpha_m = _zq10 * 0.1 * ( _lv + 40.0 ) / ( 1.0 - exp ( - ( _lv + 40.0 ) / 10.0 ) ) ;
   beta_m = _zq10 * 4.0 * exp ( - ( _lv + 65.0 ) / 18.0 ) ;
   alpha_h = _zq10 * 0.07 * exp ( - ( _lv + 65.0 ) / 20.0 ) ;
   beta_h = _zq10 / ( 1.0 + exp ( - ( _lv + 35.0 ) / 10.0 ) ) ;
   Nart [ 0 ] = 3.0 * alpha_m * Nast [ 0 ] ;
   Nart [ 1 ] = beta_m * Nast [ 1 ] ;
   Nart [ 2 ] = 2.0 * alpha_m * Nast [ 1 ] ;
   Nart [ 3 ] = 2.0 * beta_m * Nast [ 2 ] ;
   Nart [ 4 ] = alpha_m * Nast [ 2 ] ;
   Nart [ 5 ] = 3.0 * beta_m * Nast [ 3 ] ;
   Nart [ 6 ] = alpha_h * Nast [ 0 ] ;
   Nart [ 7 ] = beta_h * Nast [ 4 ] ;
   Nart [ 8 ] = alpha_h * Nast [ 1 ] ;
   Nart [ 9 ] = beta_h * Nast [ 5 ] ;
   Nart [ 10 ] = alpha_h * Nast [ 2 ] ;
   Nart [ 11 ] = beta_h * Nast [ 6 ] ;
   Nart [ 12 ] = alpha_h * Nast [ 3 ] ;
   Nart [ 13 ] = beta_h * Nast [ 7 ] ;
   Nart [ 14 ] = 3.0 * alpha_m * Nast [ 4 ] ;
   Nart [ 15 ] = beta_m * Nast [ 5 ] ;
   Nart [ 16 ] = 2.0 * alpha_m * Nast [ 5 ] ;
   Nart [ 17 ] = 2.0 * beta_m * Nast [ 6 ] ;
   Nart [ 18 ] = alpha_m * Nast [ 6 ] ;
   Nart [ 19 ] = 3.0 * beta_m * Nast [ 7 ] ;
   sumrtNa = 0.0 ;
   {int  _lii ;for ( _lii = 0 ; _lii <= 19 ; _lii ++ ) {
     sumrtNa = sumrtNa + Nart [ _lii ] ;
     } }
     return 0; }
 
static void _hoc_ratesNa(void) {
  double _r;
   _r = 1.;
 ratesNa (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int  ratesK (  double _lv ) {
    _zq10 = pow( 3.0 , ( ( celsius - 6.3 ) / 10.0 ) ) ;
   alpha_n = _zq10 * 0.01 * ( _lv + 55.0 ) / ( 1.0 - exp ( - ( _lv + 55.0 ) / 10.0 ) ) ;
   beta_n = _zq10 * 0.125 * exp ( - ( _lv + 65.0 ) / 80.0 ) ;
   Krt [ 0 ] = 4.0 * alpha_n * Kst [ 0 ] ;
   Krt [ 1 ] = beta_n * Kst [ 1 ] ;
   Krt [ 2 ] = 3.0 * alpha_n * Kst [ 1 ] ;
   Krt [ 3 ] = 2.0 * beta_n * Kst [ 2 ] ;
   Krt [ 4 ] = 2.0 * alpha_n * Kst [ 2 ] ;
   Krt [ 5 ] = 3.0 * beta_n * Kst [ 3 ] ;
   Krt [ 6 ] = alpha_n * Kst [ 3 ] ;
   Krt [ 7 ] = 4.0 * beta_n * Kst [ 4 ] ;
   sumrtK = 0.0 ;
   {int  _lii ;for ( _lii = 0 ; _lii <= 7 ; _lii ++ ) {
     sumrtK = sumrtK + Krt [ _lii ] ;
     } }
     return 0; }
 
static void _hoc_ratesK(void) {
  double _r;
   _r = 1.;
 ratesK (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int  transK (  ) {
   ratesK ( _threadargscomma_ v ) ;
   sumrtK = 0.0 ;
    {int  _lii ;for ( _lii = 0 ; _lii <= 7 ; _lii ++ ) {
     sumrtK = sumrtK + Krt [ _lii ] ;
     cumsumK [ _lii ] = sumrtK ;
     } }
   {int  _lii ;for ( _lii = 0 ; _lii <= 7 ; _lii ++ ) {
     cumsumK [ _lii ] = cumsumK [ _lii ] / sumrtK ;
     } }
    ev = scop_random ( ) * 1.0 ;
   if ( ev <= cumsumK [ 0 ] ) {
     Kst [ 0 ] = Kst [ 0 ] - 1.0 ;
     Kst [ 1 ] = Kst [ 1 ] + 1.0 ;
     }
   if ( cumsumK [ 0 ] < ev  && ev <= cumsumK [ 1 ] ) {
     Kst [ 0 ] = Kst [ 0 ] + 1.0 ;
     Kst [ 1 ] = Kst [ 1 ] - 1.0 ;
     }
   if ( cumsumK [ 1 ] < ev  && ev <= cumsumK [ 2 ] ) {
     Kst [ 1 ] = Kst [ 1 ] - 1.0 ;
     Kst [ 2 ] = Kst [ 2 ] + 1.0 ;
     }
   if ( cumsumK [ 2 ] < ev  && ev <= cumsumK [ 3 ] ) {
     Kst [ 1 ] = Kst [ 1 ] + 1.0 ;
     Kst [ 2 ] = Kst [ 2 ] - 1.0 ;
     }
   if ( cumsumK [ 3 ] < ev  && ev <= cumsumK [ 4 ] ) {
     Kst [ 2 ] = Kst [ 2 ] - 1.0 ;
     Kst [ 3 ] = Kst [ 3 ] + 1.0 ;
     }
   if ( cumsumK [ 4 ] < ev  && ev <= cumsumK [ 5 ] ) {
     Kst [ 2 ] = Kst [ 2 ] + 1.0 ;
     Kst [ 3 ] = Kst [ 3 ] - 1.0 ;
     }
   if ( cumsumK [ 5 ] < ev  && ev <= cumsumK [ 6 ] ) {
     Kst [ 3 ] = Kst [ 3 ] - 1.0 ;
     Kst [ 4 ] = Kst [ 4 ] + 1.0 ;
     }
   if ( cumsumK [ 6 ] < ev  && ev <= cumsumK [ 7 ] ) {
     Kst [ 3 ] = Kst [ 3 ] + 1.0 ;
     Kst [ 4 ] = Kst [ 4 ] - 1.0 ;
     }
   nextRK = log ( scop_random ( ) ) ;
    return 0; }
 
static void _hoc_transK(void) {
  double _r;
   _r = 1.;
 transK (  );
 hoc_retpushx(_r);
}
 
static int  transNa (  ) {
   ratesNa ( _threadargscomma_ v ) ;
    sumrtNa = 0.0 ;
   {int  _lii ;for ( _lii = 0 ; _lii <= 19 ; _lii ++ ) {
     sumrtNa = sumrtNa + Nart [ _lii ] ;
     cumsumNa [ _lii ] = sumrtNa ;
     } }
   {int  _lii ;for ( _lii = 0 ; _lii <= 19 ; _lii ++ ) {
     cumsumNa [ _lii ] = cumsumNa [ _lii ] / sumrtNa ;
     } }
    ev = scop_random ( ) * 1.0 ;
   if ( ev <= cumsumNa [ 0 ] ) {
     Nast [ 0 ] = Nast [ 0 ] - 1.0 ;
     Nast [ 1 ] = Nast [ 1 ] + 1.0 ;
     }
   if ( cumsumNa [ 0 ] < ev  && ev <= cumsumNa [ 1 ] ) {
     Nast [ 0 ] = Nast [ 0 ] + 1.0 ;
     Nast [ 1 ] = Nast [ 1 ] - 1.0 ;
     }
   if ( cumsumNa [ 1 ] < ev  && ev <= cumsumNa [ 2 ] ) {
     Nast [ 1 ] = Nast [ 1 ] - 1.0 ;
     Nast [ 2 ] = Nast [ 2 ] + 1.0 ;
     }
   if ( cumsumNa [ 2 ] < ev  && ev <= cumsumNa [ 3 ] ) {
     Nast [ 1 ] = Nast [ 1 ] + 1.0 ;
     Nast [ 2 ] = Nast [ 2 ] - 1.0 ;
     }
   if ( cumsumNa [ 3 ] < ev  && ev <= cumsumNa [ 4 ] ) {
     Nast [ 2 ] = Nast [ 2 ] - 1.0 ;
     Nast [ 3 ] = Nast [ 3 ] + 1.0 ;
     }
   if ( cumsumNa [ 4 ] < ev  && ev <= cumsumNa [ 5 ] ) {
     Nast [ 2 ] = Nast [ 2 ] + 1.0 ;
     Nast [ 3 ] = Nast [ 3 ] - 1.0 ;
     }
   if ( cumsumNa [ 5 ] < ev  && ev <= cumsumNa [ 6 ] ) {
     Nast [ 0 ] = Nast [ 0 ] - 1.0 ;
     Nast [ 4 ] = Nast [ 4 ] + 1.0 ;
     }
   if ( cumsumNa [ 6 ] < ev  && ev <= cumsumNa [ 7 ] ) {
     Nast [ 0 ] = Nast [ 0 ] + 1.0 ;
     Nast [ 4 ] = Nast [ 4 ] - 1.0 ;
     }
   if ( cumsumNa [ 7 ] < ev  && ev <= cumsumNa [ 8 ] ) {
     Nast [ 1 ] = Nast [ 1 ] - 1.0 ;
     Nast [ 5 ] = Nast [ 5 ] + 1.0 ;
     }
   if ( cumsumNa [ 8 ] < ev  && ev <= cumsumNa [ 9 ] ) {
     Nast [ 1 ] = Nast [ 1 ] + 1.0 ;
     Nast [ 5 ] = Nast [ 5 ] - 1.0 ;
     }
   if ( cumsumNa [ 9 ] < ev  && ev <= cumsumNa [ 10 ] ) {
     Nast [ 2 ] = Nast [ 2 ] - 1.0 ;
     Nast [ 6 ] = Nast [ 6 ] + 1.0 ;
     }
   if ( cumsumNa [ 10 ] < ev  && ev <= cumsumNa [ 11 ] ) {
     Nast [ 2 ] = Nast [ 2 ] + 1.0 ;
     Nast [ 6 ] = Nast [ 6 ] - 1.0 ;
     }
   if ( cumsumNa [ 11 ] < ev  && ev <= cumsumNa [ 12 ] ) {
     Nast [ 3 ] = Nast [ 3 ] - 1.0 ;
     Nast [ 7 ] = Nast [ 7 ] + 1.0 ;
     }
   if ( cumsumNa [ 12 ] < ev  && ev <= cumsumNa [ 13 ] ) {
     Nast [ 3 ] = Nast [ 3 ] + 1.0 ;
     Nast [ 7 ] = Nast [ 7 ] - 1.0 ;
     }
   if ( cumsumNa [ 13 ] < ev  && ev <= cumsumNa [ 14 ] ) {
     Nast [ 4 ] = Nast [ 4 ] - 1.0 ;
     Nast [ 5 ] = Nast [ 5 ] + 1.0 ;
     }
   if ( cumsumNa [ 14 ] < ev  && ev <= cumsumNa [ 15 ] ) {
     Nast [ 4 ] = Nast [ 4 ] + 1.0 ;
     Nast [ 5 ] = Nast [ 5 ] - 1.0 ;
     }
   if ( cumsumNa [ 15 ] < ev  && ev <= cumsumNa [ 16 ] ) {
     Nast [ 5 ] = Nast [ 5 ] - 1.0 ;
     Nast [ 6 ] = Nast [ 6 ] + 1.0 ;
     }
   if ( cumsumNa [ 16 ] < ev  && ev <= cumsumNa [ 17 ] ) {
     Nast [ 5 ] = Nast [ 5 ] + 1.0 ;
     Nast [ 6 ] = Nast [ 6 ] - 1.0 ;
     }
   if ( cumsumNa [ 17 ] < ev  && ev <= cumsumNa [ 18 ] ) {
     Nast [ 6 ] = Nast [ 6 ] - 1.0 ;
     Nast [ 7 ] = Nast [ 7 ] + 1.0 ;
     }
   if ( cumsumNa [ 18 ] < ev  && ev <= cumsumNa [ 19 ] ) {
     Nast [ 6 ] = Nast [ 6 ] + 1.0 ;
     Nast [ 7 ] = Nast [ 7 ] - 1.0 ;
     }
   nextRNa = log ( scop_random ( ) ) ;
    return 0; }
 
static void _hoc_transNa(void) {
  double _r;
   _r = 1.;
 transNa (  );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
  ek = _ion_ek;
     _ode_spec1 ();
   }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
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
  ena = _ion_ena;
  ek = _ion_ek;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 4);
   nrn_update_ion_pointer(_k_sym, _ppvar, 3, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 4, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 5, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  mock = mock0;
 {
   double _lstsum ;
 if ( se >= 0.0 ) {
     set_seed ( se ) ;
     }
   ratesNa ( _threadargscomma_ v ) ;
   ratesK ( _threadargscomma_ v ) ;
   M = alpha_m / beta_m ;
   H = alpha_h / beta_h ;
   N = alpha_n / beta_n ;
   _lstsum = ( 1.0 + H ) * pow( ( 1.0 + M ) , 3.0 ) ;
   Nast [ 1 ] = floor ( NNa * 3.0 * M / _lstsum + 0.5 ) ;
   Nast [ 2 ] = floor ( NNa * 3.0 * pow( M , 2.0 ) / _lstsum + 0.5 ) ;
   Nast [ 3 ] = floor ( NNa * pow( M , 3.0 ) / _lstsum + 0.5 ) ;
   Nast [ 4 ] = floor ( NNa * H / _lstsum + 0.5 ) ;
   Nast [ 5 ] = floor ( NNa * H * 3.0 * M / _lstsum + 0.5 ) ;
   Nast [ 6 ] = floor ( NNa * H * 3.0 * pow( M , 2.0 ) / _lstsum + 0.5 ) ;
   Nast [ 7 ] = floor ( NNa * H * pow( M , 3.0 ) / _lstsum + 0.5 ) ;
   Nast [ 0 ] = NNa - Nast [ 1 ] - Nast [ 2 ] - Nast [ 3 ] - Nast [ 4 ] - Nast [ 5 ] - Nast [ 6 ] - Nast [ 7 ] ;
   ratesNa ( _threadargscomma_ v ) ;
   nextRNa = log ( scop_random ( ) ) ;
   prev_evNa = 0.0 ;
   _lstsum = pow( ( 1.0 + N ) , 4.0 ) ;
   Kst [ 1 ] = floor ( NK * 4.0 * N / _lstsum + 0.5 ) ;
   Kst [ 2 ] = floor ( NK * 6.0 * pow( N , 2.0 ) / _lstsum + 0.5 ) ;
   Kst [ 3 ] = floor ( NK * 4.0 * pow( N , 3.0 ) / _lstsum + 0.5 ) ;
   Kst [ 4 ] = floor ( NK * pow( N , 4.0 ) / _lstsum + 0.5 ) ;
   Kst [ 0 ] = NK - Kst [ 1 ] - Kst [ 2 ] - Kst [ 3 ] - Kst [ 4 ] ;
   ratesK ( _threadargscomma_ v ) ;
   nextRK = log ( scop_random ( ) ) ;
   prev_evK = 0.0 ;
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
  ena = _ion_ena;
  ek = _ion_ek;
 initmodel();
  }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ina = gnabar * Nast [ 7 ] * ( v - ena ) / NNa ;
   ik = gkbar * Kst [ 4 ] * ( v - ek ) / NK ;
   il = gl * ( v - el ) ;
   }
 _current += ina;
 _current += ik;
 _current += il;

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
  ena = _ion_ena;
  ek = _ion_ek;
 _g = _nrn_current(_v + .001);
 	{ double _dik;
 double _dina;
  _dina = ina;
  _dik = ik;
 _rhs = _nrn_current(_v);
  _ion_dinadv += (_dina - ina)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
  _ion_ik += ik ;
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
  ena = _ion_ena;
  ek = _ion_ek;
 { error =  mula();
 if(error){fprintf(stderr,"at line 106 in file hhMC.mod:\n	SOLVE mula METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 }  }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(mock) - _p;  _dlist1[0] = &(Dmock) - _p;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/giulia/Desktop/Tesi/VagrantNeuro/TutorialsNeuron_and_Brian/DAcomparison/HH/Neuron/hhMC.mod";
static const char* nmodl_file_text = 
  "TITLE hh.mod   squid sodium, potassium, and leak channels\n"
  "\n"
  "COMMENT\n"
  "Stochastic Hodgkin and Huxley model using Markov Chain modeling.\n"
  "Gillespie's method with a modification for low channel numbers (or few transitions)\n"
  "Written for Pezo, Soudry and Orio (2014) Front. Comp Neurosci\n"
  "\n"
  "Sodium channel states are:\n"
  "Nast[0] = m0h0   Nast[1] = m1h0   Nast[2] = m2h0  Nast[3] = m3h0\n"
  "Nast[4] = m0h1   Nast[5] = m1h1   Nast[6] = m2h1  Nast[7] = m3h1\n"
  "\n"
  "Potassium states are:\n"
  "Kst[0] =  n0   Kst[1] = n1   Kst[2] = n2  Kst[3] = n3  Kst[4] = n4\n"
  "\n"
  "conducting states are m3h1 and n4, respectively\n"
  "\n"
  "Possible Sodium channel transitions are indexed as follows:\n"
  "First row trasitions (m particles)\n"
  "    Forward            Backward\n"
  "  0: Nast[0] --> Nast[1]   1: Nast[1] --> Nast[0]\n"
  "  2: Nast[1] --> Nast[2]   3: Nast[2] --> Nast[1]\n"
  "  4: Nast[2] --> Nast[3]   5: Nast[3] --> Nast[2]\n"
  "Vertical transitions (h particle)\n"
  "  6: Nast[0] --> Nast[4]   7: Nast[4] --> Nast[0]\n"
  "  8: Nast[1] --> Nast[5]   9: Nast[5] --> Nast[1]\n"
  " 10: Nast[2] --> Nast[6]  11: Nast[6] --> Nast[2]\n"
  " 12: Nast[3] --> Nast[7]  13: Nast[7] --> Nast[3]\n"
  "First row trasitions (m particles)\n"
  " 14: Nast[4] --> Nast[5]  15: Nast[5] --> Nast[4]\n"
  " 16: Nast[5] --> Nast[6]  17: Nast[6] --> Nast[5]\n"
  " 18: Nast[6] --> Nast[7]  19: Nast[7] --> Nast[6]\n"
  "\n"
  "Possible Potassium channel transitions are indexed as follows:\n"
  "    Forward            Backward\n"
  " 0: Kst[0] --> Kst[1]   1: Kst[1] --> Kst[0]\n"
  " 2: Kst[1] --> Kst[2]   3: Kst[2] --> Kst[1]\n"
  " 4: Kst[2] --> Kst[3]   5: Kst[3] --> Kst[2]\n"
  " 6: Kst[3] --> Kst[4]   7: Kst[4] --> Kst[3]\n"
  "\n"
  "ENDCOMMENT\n"
  " \n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "	(S) = (siemens)\n"
  "}\n"
  " \n"
  "NEURON {\n"
  "	SUFFIX hhMC \n"
  "	USEION na READ ena WRITE ina\n"
  "	USEION k READ ek WRITE ik\n"
  "	NONSPECIFIC_CURRENT il\n"
  "	RANGE gnabar, gkbar, gl, el, NNa, NK, next_evK, next_evNa, Nast, Kst, se\n"
  "	RANGE nextRK, nextRNa\n"
  "}\n"
  " \n"
  "PARAMETER {\n"
  "	se = -1  : seed to be used. se=-1 means no seed is set\n"
  "	gnabar = .12 (S/cm2)	<0,1e9>\n"
  "	gkbar = .036 (S/cm2)	<0,1e9>\n"
  "	gl = .0003 (S/cm2)	<0,1e9>\n"
  "	el = -54.3 (mV)\n"
  "	NNa = 5000\n"
  "	NK = 1600 \n"
  "	\n"
  "}\n"
  " \n"
  "ASSIGNED {\n"
  "	v (mV)\n"
  "	celsius (degC)\n"
  "	ena (mV)\n"
  "	ek (mV)\n"
  "\n"
  "	ina (mA/cm2)\n"
  "	ik (mA/cm2)\n"
  "	il (mA/cm2)\n"
  "	alpha_m	(/ms)\n"
  "	alpha_h	(/ms)\n"
  "	alpha_n	(/ms)\n"
  "	beta_m	(/ms)\n"
  "	beta_h	(/ms)\n"
  "	beta_n	(/ms)\n"
  "	Nast[8]\n"
  "	Kst[5]\n"
  "	Nart[20]	(/ms)\n"
  "	Krt[8]		(/ms)\n"
  "	sumrtNa		(/ms)\n"
  "	sumrtK		(/ms)\n"
  "	cumsumNa[20](/ms)\n"
  "	cumsumK[8]	(/ms)\n"
  "	next_evNa	(ms)\n"
  "	next_evK	(ms)\n"
  "	prev_evNa	(ms)\n"
  "	prev_evK	(ms)\n"
  "    	nextRK\n"
  "    	nextRNa\n"
  "	ev			(/ms)\n"
  "	M\n"
  "	N\n"
  "	H\n"
  "}\n"
  " \n"
  "STATE {mock}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE mula METHOD cnexp\n"
  "	ina = gnabar*Nast[7]*(v - ena)/NNa\n"
  "	ik = gkbar*Kst[4]*(v - ek)/NK      \n"
  "	il = gl*(v - el)\n"
  "}\n"
  " \n"
  "INITIAL {\n"
  "	LOCAL stsum\n"
  "\n"
  "	if (se>=0) {set_seed(se)}\n"
  "\n"
  "    ratesNa(v)\n"
  "    ratesK(v)\n"
  "    \n"
  "	M=alpha_m/beta_m\n"
  "	H=alpha_h/beta_h\n"
  "	N=alpha_n/beta_n\n"
  "	stsum=(1+H)*(1+M)^3\n"
  "    : calculate initial states\n"
  "\n"
  "	Nast[1]=floor(NNa*3*M/stsum+0.5)\n"
  "	Nast[2]=floor(NNa*3*M^2/stsum+0.5)\n"
  "	Nast[3]=floor(NNa*M^3/stsum+0.5)\n"
  "	Nast[4]=floor(NNa*H/stsum+0.5)\n"
  "	Nast[5]=floor(NNa*H*3*M/stsum+0.5)\n"
  "	Nast[6]=floor(NNa*H*3*M^2/stsum+0.5)\n"
  "	Nast[7]=floor(NNa*H*M^3/stsum+0.5)\n"
  "    Nast[0]=NNa-Nast[1]-Nast[2]-Nast[3]-Nast[4]-Nast[5]-Nast[6]-Nast[7]\n"
  "	ratesNa(v)\n"
  "    :calculate the random number (log) that will be used in the first transition \n"
  "    :time and set the last transition to t=0\n"
  "	nextRNa = log(scop_random())\n"
  "	prev_evNa=0\n"
  "	\n"
  "	stsum=(1+N)^4\n"
  "	:calculate initial state occupancies\n"
  "    Kst[1]=floor(NK*4*N/stsum+0.5)\n"
  "	Kst[2]=floor(NK*6*N^2/stsum+0.5)\n"
  "	Kst[3]=floor(NK*4*N^3/stsum+0.5)\n"
  "	Kst[4]=floor(NK*N^4/stsum+0.5)\n"
  "    Kst[0]=NK-Kst[1]-Kst[2]-Kst[3]-Kst[4]\n"
  "	ratesK(v)\n"
  "    :calculate the random number (log) that will be used in the first transition \n"
  "    :time and set the last transition to t=0\n"
  "	nextRK = log(scop_random())\n"
  "	prev_evK=0\n"
  "}\n"
  "\n"
  "DERIVATIVE mula {\n"
  "    :recalculate rates\n"
  "    ratesNa(v)\n"
  "    :recalculate time of next event with the already existing random value (nextRNa)\n"
  "	next_evNa = prev_evNa - nextRNa/sumrtNa  \n"
  "	while (t>= next_evNa){ :do transitions if needed\n"
  "        transNa()\n"
  "        prev_evNa = next_evNa\n"
  "        :calculate again next transition in case it falls within the current time step\n"
  "		next_evNa = prev_evNa - nextRNa/sumrtNa  \n"
  "    }\n"
  "\n"
  "    :same for potassium\n"
  "    ratesK(v)\n"
  "	next_evK = prev_evK - nextRK/sumrtK\n"
  "	while (t>= next_evK){\n"
  "		transK()\n"
  "        prev_evK = next_evK\n"
  "		next_evK = prev_evK - nextRK/sumrtK\n"
  "	}\n"
  "	mock'=0\n"
  "}\n"
  " \n"
  "LOCAL q10\n"
  "\n"
  "PROCEDURE ratesNa(v(mV)) {  :Computes rate and other constants at current v.\n"
  "	UNITSOFF\n"
  "	q10 = 3^((celsius - 6.3)/10)\n"
  "	alpha_m = q10*0.1*(v+40)/(1-exp(-(v+40)/10))\n"
  "	beta_m = q10*4*exp(-(v+65)/18)\n"
  "	alpha_h = q10*0.07*exp(-(v+65)/20) \n"
  "	beta_h = q10/(1+exp(-(v+35)/10))\n"
  "    :Nart[i] is the effective rate for the 'i' transition\n"
  "	Nart[0]=3*alpha_m*Nast[0]\n"
  "	Nart[1]=beta_m*Nast[1]\n"
  "	Nart[2]=2*alpha_m*Nast[1]\n"
  "	Nart[3]=2*beta_m*Nast[2]\n"
  "	Nart[4]=alpha_m*Nast[2]\n"
  "	Nart[5]=3*beta_m*Nast[3]\n"
  "	Nart[6]=alpha_h*Nast[0]\n"
  "	Nart[7]=beta_h*Nast[4]\n"
  "	Nart[8]=alpha_h*Nast[1]\n"
  "	Nart[9]=beta_h*Nast[5]\n"
  "	Nart[10]=alpha_h*Nast[2]\n"
  "	Nart[11]=beta_h*Nast[6]\n"
  "	Nart[12]=alpha_h*Nast[3]\n"
  "	Nart[13]=beta_h*Nast[7]\n"
  "	Nart[14]=3*alpha_m*Nast[4]\n"
  "	Nart[15]=beta_m*Nast[5]\n"
  "	Nart[16]=2*alpha_m*Nast[5]\n"
  "	Nart[17]=2*beta_m*Nast[6]\n"
  "	Nart[18]=alpha_m*Nast[6]\n"
  "	Nart[19]=3*beta_m*Nast[7]\n"
  "	sumrtNa=0\n"
  "	FROM ii=0 TO 19 {\n"
  "		sumrtNa = sumrtNa + Nart[ii]\n"
  "	}\n"
  "	UNITSON\n"
  "}\n"
  "\n"
  "PROCEDURE ratesK(v(mV)) {\n"
  "	UNITSOFF\n"
  "	q10 = 3^((celsius - 6.3)/10)\n"
  "	alpha_n = q10*0.01*(v+55)/(1-exp(-(v+55)/10))\n"
  "	beta_n = q10*0.125*exp(-(v+65)/80)\n"
  "    :Krt[i] is the effective rate for the 'i' transition\n"
  "	Krt[0]=4*alpha_n*Kst[0]\n"
  "	Krt[1]=beta_n*Kst[1]\n"
  "	Krt[2]=3*alpha_n*Kst[1]\n"
  "	Krt[3]=2*beta_n*Kst[2]\n"
  "	Krt[4]=2*alpha_n*Kst[2]\n"
  "	Krt[5]=3*beta_n*Kst[3]\n"
  "	Krt[6]=alpha_n*Kst[3]\n"
  "	Krt[7]=4*beta_n*Kst[4]\n"
  "	sumrtK=0\n"
  "	FROM ii=0 TO 7 {\n"
  "		sumrtK = sumrtK + Krt[ii]\n"
  "	}\n"
  "\n"
  "	UNITSON\n"
  "}\n"
  "\n"
  "PROCEDURE transK() {  :perform a transition on K channels\n"
  "    :calculate rates\n"
  "	ratesK(v)\n"
  "    :calculate a cummulative sum of effective transition rates\n"
  "   	sumrtK=0\n"
  "    UNITSOFF\n"
  "	FROM ii=0 TO 7 {\n"
  "		sumrtK = sumrtK + Krt[ii]\n"
  "		cumsumK[ii] = sumrtK\n"
  "	}\n"
  "    :normalize the cummulative sum to 1\n"
  "	FROM ii=0 TO 7 {cumsumK[ii] = cumsumK[ii] / sumrtK}\n"
  "    UNITSON\n"
  "    :draw a random number [0,1] and select a transition depending on \n"
  "    :where it falls within the cummulative sum of transition rates\n"
  "	ev = scop_random()*1(/ms)\n"
  "	if (ev <= cumsumK[0]) {\n"
  "		Kst[0]=Kst[0]-1\n"
  "		Kst[1]=Kst[1]+1\n"
  "	}\n"
  "	if (cumsumK[0] < ev && ev <= cumsumK[1]) {\n"
  "		Kst[0]=Kst[0]+1\n"
  "		Kst[1]=Kst[1]-1\n"
  "	}	\n"
  "	if (cumsumK[1] < ev && ev <= cumsumK[2]) {\n"
  "		Kst[1]=Kst[1]-1\n"
  "		Kst[2]=Kst[2]+1\n"
  "	}\n"
  "	if (cumsumK[2] < ev && ev <= cumsumK[3]) {\n"
  "		Kst[1]=Kst[1]+1\n"
  "		Kst[2]=Kst[2]-1\n"
  "	}	\n"
  "	if (cumsumK[3] < ev && ev <= cumsumK[4]) {\n"
  "		Kst[2]=Kst[2]-1\n"
  "		Kst[3]=Kst[3]+1\n"
  "	}\n"
  "	if (cumsumK[4] < ev && ev <= cumsumK[5]) {\n"
  "		Kst[2]=Kst[2]+1\n"
  "		Kst[3]=Kst[3]-1\n"
  "	}\n"
  "	if (cumsumK[5] < ev && ev <= cumsumK[6]) {\n"
  "		Kst[3]=Kst[3]-1\n"
  "		Kst[4]=Kst[4]+1\n"
  "	}\n"
  "	if (cumsumK[6] < ev && ev <= cumsumK[7]) {\n"
  "		Kst[3]=Kst[3]+1\n"
  "		Kst[4]=Kst[4]-1\n"
  "	}\n"
  "    :finally, calculate a random number used to determine the next transition time\n"
  "    :logarithm is applied immediately\n"
  "	nextRK = log(scop_random())\n"
  "}\n"
  "\n"
  " \n"
  "PROCEDURE transNa() { :perform a transition on sodium channels, the same as described for K channels\n"
  "	ratesNa(v)\n"
  "    UNITSOFF\n"
  "    sumrtNa=0\n"
  "    FROM ii=0 TO 19 {\n"
  "	  sumrtNa = sumrtNa + Nart[ii]\n"
  "	  cumsumNa[ii] = sumrtNa\n"
  "    }\n"
  "	FROM ii=0 TO 19 {cumsumNa[ii] = cumsumNa[ii] / sumrtNa}\n"
  "    UNITSON\n"
  "	ev = scop_random()*1(/ms)\n"
  "	if (ev <= cumsumNa[0]) {\n"
  "		Nast[0]=Nast[0]-1\n"
  "		Nast[1]=Nast[1]+1\n"
  "	}\n"
  "	if (cumsumNa[0] < ev && ev <= cumsumNa[1]) {\n"
  "		Nast[0]=Nast[0]+1\n"
  "		Nast[1]=Nast[1]-1\n"
  "	}	\n"
  "	if (cumsumNa[1] < ev && ev <= cumsumNa[2]) {\n"
  "		Nast[1]=Nast[1]-1\n"
  "		Nast[2]=Nast[2]+1\n"
  "	}\n"
  "	if (cumsumNa[2] < ev && ev <= cumsumNa[3]) {\n"
  "		Nast[1]=Nast[1]+1\n"
  "		Nast[2]=Nast[2]-1\n"
  "	}	\n"
  "	if (cumsumNa[3] < ev && ev <= cumsumNa[4]) {\n"
  "		Nast[2]=Nast[2]-1\n"
  "		Nast[3]=Nast[3]+1\n"
  "	}\n"
  "	if (cumsumNa[4] < ev && ev <= cumsumNa[5]) {\n"
  "		Nast[2]=Nast[2]+1\n"
  "		Nast[3]=Nast[3]-1\n"
  "	}\n"
  "	if (cumsumNa[5] < ev && ev <= cumsumNa[6]) {\n"
  "		Nast[0]=Nast[0]-1\n"
  "		Nast[4]=Nast[4]+1\n"
  "	}\n"
  "	if (cumsumNa[6] < ev && ev <= cumsumNa[7]) {\n"
  "		Nast[0]=Nast[0]+1\n"
  "		Nast[4]=Nast[4]-1\n"
  "	}\n"
  "	if (cumsumNa[7] < ev && ev <= cumsumNa[8]) {\n"
  "		Nast[1]=Nast[1]-1\n"
  "		Nast[5]=Nast[5]+1\n"
  "	}\n"
  "	if (cumsumNa[8] < ev && ev <= cumsumNa[9]) {\n"
  "		Nast[1]=Nast[1]+1\n"
  "		Nast[5]=Nast[5]-1\n"
  "	}\n"
  "	if (cumsumNa[9] < ev && ev <= cumsumNa[10]) {\n"
  "		Nast[2]=Nast[2]-1\n"
  "		Nast[6]=Nast[6]+1\n"
  "	}\n"
  "	if (cumsumNa[10] < ev && ev <= cumsumNa[11]) {\n"
  "		Nast[2]=Nast[2]+1\n"
  "		Nast[6]=Nast[6]-1\n"
  "	}				\n"
  "	if (cumsumNa[11] < ev && ev <= cumsumNa[12]) {\n"
  "		Nast[3]=Nast[3]-1\n"
  "		Nast[7]=Nast[7]+1\n"
  "	}\n"
  "	if (cumsumNa[12] < ev && ev <= cumsumNa[13]) {\n"
  "		Nast[3]=Nast[3]+1\n"
  "		Nast[7]=Nast[7]-1\n"
  "	}\n"
  "	if (cumsumNa[13] < ev && ev <= cumsumNa[14]) {\n"
  "		Nast[4]=Nast[4]-1\n"
  "		Nast[5]=Nast[5]+1\n"
  "	}\n"
  "	if (cumsumNa[14] < ev && ev <= cumsumNa[15]) {\n"
  "		Nast[4]=Nast[4]+1\n"
  "		Nast[5]=Nast[5]-1\n"
  "	}\n"
  "	if (cumsumNa[15] < ev && ev <= cumsumNa[16]) {\n"
  "		Nast[5]=Nast[5]-1\n"
  "		Nast[6]=Nast[6]+1\n"
  "	}\n"
  "	if (cumsumNa[16] < ev && ev <= cumsumNa[17]) {\n"
  "		Nast[5]=Nast[5]+1\n"
  "		Nast[6]=Nast[6]-1\n"
  "	}\n"
  "	if (cumsumNa[17] < ev && ev <= cumsumNa[18]) {\n"
  "		Nast[6]=Nast[6]-1\n"
  "		Nast[7]=Nast[7]+1\n"
  "	}\n"
  "	if (cumsumNa[18] < ev && ev <= cumsumNa[19]) {\n"
  "		Nast[6]=Nast[6]+1\n"
  "		Nast[7]=Nast[7]-1\n"
  "	}\n"
  "    nextRNa=log(scop_random())\n"
  "}\n"
  ;
#endif
