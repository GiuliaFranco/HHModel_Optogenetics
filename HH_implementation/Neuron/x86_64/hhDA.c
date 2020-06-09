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
 
#define nrn_init _nrn_init__hhDA
#define _nrn_initial _nrn_initial__hhDA
#define nrn_cur _nrn_cur__hhDA
#define _nrn_current _nrn_current__hhDA
#define nrn_jacob _nrn_jacob__hhDA
#define nrn_state _nrn_state__hhDA
#define _net_receive _net_receive__hhDA 
#define rates rates__hhDA 
#define states states__hhDA 
 
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
#define mh1 _p[8]
#define mh2 _p[9]
#define mh3 _p[10]
#define mh4 _p[11]
#define mh5 _p[12]
#define mh6 _p[13]
#define mh7 _p[14]
#define n1 _p[15]
#define n2 _p[16]
#define n3 _p[17]
#define n4 _p[18]
#define ena _p[19]
#define ek _p[20]
#define ina _p[21]
#define ik _p[22]
#define am _p[23]
#define ah _p[24]
#define an _p[25]
#define bm _p[26]
#define bh _p[27]
#define bn _p[28]
#define stsum _p[29]
#define M _p[30]
#define N _p[31]
#define H _p[32]
#define R (_p + 33)
#define mh0 _p[47]
#define n0 _p[48]
#define Dmh1 _p[49]
#define Dmh2 _p[50]
#define Dmh3 _p[51]
#define Dmh4 _p[52]
#define Dmh5 _p[53]
#define Dmh6 _p[54]
#define Dmh7 _p[55]
#define Dn1 _p[56]
#define Dn2 _p[57]
#define Dn3 _p[58]
#define Dn4 _p[59]
#define _g _p[60]
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
 static void _hoc_rates(void);
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
 "setdata_hhDA", _hoc_setdata,
 "rates_hhDA", _hoc_rates,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "gl_hhDA", 0, 1e+09,
 "gkbar_hhDA", 0, 1e+09,
 "gnabar_hhDA", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gnabar_hhDA", "S/cm2",
 "gkbar_hhDA", "S/cm2",
 "gl_hhDA", "S/cm2",
 "el_hhDA", "mV",
 "il_hhDA", "mA/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double mh70 = 0;
 static double mh60 = 0;
 static double mh50 = 0;
 static double mh40 = 0;
 static double mh30 = 0;
 static double mh20 = 0;
 static double mh10 = 0;
 static double n40 = 0;
 static double n30 = 0;
 static double n20 = 0;
 static double n10 = 0;
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
"hhDA",
 "se_hhDA",
 "gnabar_hhDA",
 "gkbar_hhDA",
 "gl_hhDA",
 "el_hhDA",
 "NNa_hhDA",
 "NK_hhDA",
 0,
 "il_hhDA",
 0,
 "mh1_hhDA",
 "mh2_hhDA",
 "mh3_hhDA",
 "mh4_hhDA",
 "mh5_hhDA",
 "mh6_hhDA",
 "mh7_hhDA",
 "n1_hhDA",
 "n2_hhDA",
 "n3_hhDA",
 "n4_hhDA",
 0,
 0};
 static Symbol* _na_sym;
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 61, _prop);
 	/*initialize range parameters*/
 	se = -1;
 	gnabar = 0.12;
 	gkbar = 0.036;
 	gl = 0.0003;
 	el = -54.3;
 	NNa = 5000;
 	NK = 1600;
 	_prop->param = _p;
 	_prop->param_size = 61;
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

 void _hhDA_reg() {
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
  hoc_register_prop_size(_mechtype, 61, 7);
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
 	ivoc_help("help ?1 hhDA /Users/giulia/Desktop/Tesi/VagrantNeuro/TutorialsNeuron_and_Brian/DAcomparison/HH/Neuron/x86_64/hhDA.mod\n");
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
static int rates(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[11], _dlist1[11];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   Dmh1 = ( - 2.0 * am - bm - ah ) * mh1 + 3.0 * am * mh0 + 2.0 * bm * mh2 + bh * mh5 - R [ 0 ] + R [ 1 ] + R [ 4 ] ;
   Dmh2 = ( - am - 2.0 * bm - ah ) * mh2 + 2.0 * am * mh1 + 3.0 * bm * mh3 + bh * mh6 - R [ 1 ] + R [ 2 ] + R [ 5 ] ;
   Dmh3 = ( - 3.0 * bm - ah ) * mh3 + am * mh2 + bh * mh7 - R [ 2 ] + R [ 6 ] ;
   Dmh4 = ( - 3.0 * am - bh ) * mh4 + bm * mh5 + ah * mh0 + R [ 7 ] - R [ 3 ] ;
   Dmh5 = ( - 2.0 * am - bm - bh ) * mh5 + 3.0 * am * mh4 + 2.0 * bm * mh6 + ah * mh1 - R [ 7 ] + R [ 8 ] - R [ 4 ] ;
   Dmh6 = ( - am - 2.0 * bm - bh ) * mh6 + 2.0 * am * mh5 + 3.0 * bm * mh7 + ah * mh2 - R [ 8 ] + R [ 9 ] - R [ 5 ] ;
   Dmh7 = ( - 3.0 * bm - bh ) * mh7 + am * mh6 + ah * mh3 - R [ 9 ] - R [ 6 ] ;
   mh0 = 1.0 - mh1 - mh2 - mh3 - mh4 - mh5 - mh6 - mh7 ;
   Dn1 = ( - 3.0 * an - bn ) * n1 + 4.0 * an * n0 + 2.0 * bn * n2 - R [ 10 ] + R [ 11 ] ;
   Dn2 = ( - 2.0 * an - 2.0 * bn ) * n2 + 3.0 * an * n1 + 3.0 * bn * n3 - R [ 11 ] + R [ 12 ] ;
   Dn3 = ( - an - 3.0 * bn ) * n3 + 2.0 * an * n2 + 4.0 * bn * n4 - R [ 12 ] + R [ 13 ] ;
   Dn4 = - 4.0 * bn * n4 + an * n3 - R [ 13 ] ;
   n0 = 1.0 - n1 - n2 - n3 - n4 ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 Dmh1 = Dmh1  / (1. - dt*( ( ( - 2.0 * am - bm - ah ) )*( 1.0 ) )) ;
 Dmh2 = Dmh2  / (1. - dt*( ( ( - am - 2.0 * bm - ah ) )*( 1.0 ) )) ;
 Dmh3 = Dmh3  / (1. - dt*( ( ( - 3.0 * bm - ah ) )*( 1.0 ) )) ;
 Dmh4 = Dmh4  / (1. - dt*( ( ( - 3.0 * am - bh ) )*( 1.0 ) )) ;
 Dmh5 = Dmh5  / (1. - dt*( ( ( - 2.0 * am - bm - bh ) )*( 1.0 ) )) ;
 Dmh6 = Dmh6  / (1. - dt*( ( ( - am - 2.0 * bm - bh ) )*( 1.0 ) )) ;
 Dmh7 = Dmh7  / (1. - dt*( ( ( - 3.0 * bm - bh ) )*( 1.0 ) )) ;
 mh0 = 1.0 - mh1 - mh2 - mh3 - mh4 - mh5 - mh6 - mh7 ;
 Dn1 = Dn1  / (1. - dt*( ( ( - 3.0 * an - bn ) )*( 1.0 ) )) ;
 Dn2 = Dn2  / (1. - dt*( ( ( - 2.0 * an - 2.0 * bn ) )*( 1.0 ) )) ;
 Dn3 = Dn3  / (1. - dt*( ( ( - an - 3.0 * bn ) )*( 1.0 ) )) ;
 Dn4 = Dn4  / (1. - dt*( ( - 4.0 * bn )*( 1.0 ) )) ;
 n0 = 1.0 - n1 - n2 - n3 - n4 ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
    mh1 = mh1 + (1. - exp(dt*(( ( - 2.0 * am - bm - ah ) )*( 1.0 ))))*(- ( ( ( 3.0 )*( am ) )*( mh0 ) + ( ( 2.0 )*( bm ) )*( mh2 ) + ( bh )*( mh5 ) - R[0] + R[1] + R[4] ) / ( ( ( ( - 2.0 )*( am ) - bm - ah ) )*( 1.0 ) ) - mh1) ;
    mh2 = mh2 + (1. - exp(dt*(( ( - am - 2.0 * bm - ah ) )*( 1.0 ))))*(- ( ( ( 2.0 )*( am ) )*( mh1 ) + ( ( 3.0 )*( bm ) )*( mh3 ) + ( bh )*( mh6 ) - R[1] + R[2] + R[5] ) / ( ( ( - am - ( 2.0 )*( bm ) - ah ) )*( 1.0 ) ) - mh2) ;
    mh3 = mh3 + (1. - exp(dt*(( ( - 3.0 * bm - ah ) )*( 1.0 ))))*(- ( ( am )*( mh2 ) + ( bh )*( mh7 ) - R[2] + R[6] ) / ( ( ( ( - 3.0 )*( bm ) - ah ) )*( 1.0 ) ) - mh3) ;
    mh4 = mh4 + (1. - exp(dt*(( ( - 3.0 * am - bh ) )*( 1.0 ))))*(- ( ( bm )*( mh5 ) + ( ah )*( mh0 ) + R[7] - R[3] ) / ( ( ( ( - 3.0 )*( am ) - bh ) )*( 1.0 ) ) - mh4) ;
    mh5 = mh5 + (1. - exp(dt*(( ( - 2.0 * am - bm - bh ) )*( 1.0 ))))*(- ( ( ( 3.0 )*( am ) )*( mh4 ) + ( ( 2.0 )*( bm ) )*( mh6 ) + ( ah )*( mh1 ) - R[7] + R[8] - R[4] ) / ( ( ( ( - 2.0 )*( am ) - bm - bh ) )*( 1.0 ) ) - mh5) ;
    mh6 = mh6 + (1. - exp(dt*(( ( - am - 2.0 * bm - bh ) )*( 1.0 ))))*(- ( ( ( 2.0 )*( am ) )*( mh5 ) + ( ( 3.0 )*( bm ) )*( mh7 ) + ( ah )*( mh2 ) - R[8] + R[9] - R[5] ) / ( ( ( - am - ( 2.0 )*( bm ) - bh ) )*( 1.0 ) ) - mh6) ;
    mh7 = mh7 + (1. - exp(dt*(( ( - 3.0 * bm - bh ) )*( 1.0 ))))*(- ( ( am )*( mh6 ) + ( ah )*( mh3 ) - R[9] - R[6] ) / ( ( ( ( - 3.0 )*( bm ) - bh ) )*( 1.0 ) ) - mh7) ;
   mh0 = 1.0 - mh1 - mh2 - mh3 - mh4 - mh5 - mh6 - mh7 ;
    n1 = n1 + (1. - exp(dt*(( ( - 3.0 * an - bn ) )*( 1.0 ))))*(- ( ( ( 4.0 )*( an ) )*( n0 ) + ( ( 2.0 )*( bn ) )*( n2 ) - R[10] + R[11] ) / ( ( ( ( - 3.0 )*( an ) - bn ) )*( 1.0 ) ) - n1) ;
    n2 = n2 + (1. - exp(dt*(( ( - 2.0 * an - 2.0 * bn ) )*( 1.0 ))))*(- ( ( ( 3.0 )*( an ) )*( n1 ) + ( ( 3.0 )*( bn ) )*( n3 ) - R[11] + R[12] ) / ( ( ( ( - 2.0 )*( an ) - ( 2.0 )*( bn ) ) )*( 1.0 ) ) - n2) ;
    n3 = n3 + (1. - exp(dt*(( ( - an - 3.0 * bn ) )*( 1.0 ))))*(- ( ( ( 2.0 )*( an ) )*( n2 ) + ( ( 4.0 )*( bn ) )*( n4 ) - R[12] + R[13] ) / ( ( ( - an - ( 3.0 )*( bn ) ) )*( 1.0 ) ) - n3) ;
    n4 = n4 + (1. - exp(dt*(( - 4.0 * bn )*( 1.0 ))))*(- ( ( an )*( n3 ) - R[13] ) / ( ( ( - 4.0 )*( bn ) )*( 1.0 ) ) - n4) ;
   n0 = 1.0 - n1 - n2 - n3 - n4 ;
   }
  return 0;
}
 
static int  rates (  double _lv ) {
   double _lq10 ;
  _lq10 = pow( 3.0 , ( ( celsius - 6.3 ) / 10.0 ) ) ;
   am = _lq10 * 0.1 * ( _lv + 40.0 ) / ( 1.0 - exp ( - ( _lv + 40.0 ) / 10.0 ) ) ;
   bm = _lq10 * 4.0 * exp ( - ( _lv + 65.0 ) / 18.0 ) ;
   ah = _lq10 * 0.07 * exp ( - ( _lv + 65.0 ) / 20.0 ) ;
   bh = _lq10 / ( 1.0 + exp ( - ( _lv + 35.0 ) / 10.0 ) ) ;
   an = _lq10 * 0.01 * ( _lv + 55.0 ) / ( 1.0 - exp ( - ( _lv + 55.0 ) / 10.0 ) ) ;
   bn = _lq10 * 0.125 * exp ( - ( _lv + 65.0 ) / 80.0 ) ;
   {int  _lii ;for ( _lii = 0 ; _lii <= 9 ; _lii ++ ) {
     R [ _lii ] = normrand ( 0.0 , 1.0 / sqrt ( NNa * dt ) ) ;
     } }
   {int  _lii ;for ( _lii = 10 ; _lii <= 13 ; _lii ++ ) {
     R [ _lii ] = normrand ( 0.0 , 1.0 / sqrt ( NK * dt ) ) ;
     } }
   R [ 0 ] = R [ 0 ] * sqrt ( fabs ( 3.0 * am * mh0 + bm * mh1 ) ) ;
   R [ 1 ] = R [ 1 ] * sqrt ( fabs ( 2.0 * am * mh1 + 2.0 * bm * mh2 ) ) ;
   R [ 2 ] = R [ 2 ] * sqrt ( fabs ( am * mh2 + 3.0 * bm * mh3 ) ) ;
   R [ 3 ] = R [ 3 ] * sqrt ( fabs ( ah * mh0 + bh * mh4 ) ) ;
   R [ 4 ] = R [ 4 ] * sqrt ( fabs ( ah * mh1 + bh * mh5 ) ) ;
   R [ 5 ] = R [ 5 ] * sqrt ( fabs ( ah * mh2 + bh * mh6 ) ) ;
   R [ 6 ] = R [ 6 ] * sqrt ( fabs ( ah * mh3 + bh * mh7 ) ) ;
   R [ 7 ] = R [ 7 ] * sqrt ( fabs ( 3.0 * am * mh4 + bm * mh5 ) ) ;
   R [ 8 ] = R [ 8 ] * sqrt ( fabs ( 2.0 * am * mh5 + 2.0 * bm * mh6 ) ) ;
   R [ 9 ] = R [ 9 ] * sqrt ( fabs ( am * mh6 + 3.0 * bm * mh7 ) ) ;
   R [ 10 ] = R [ 10 ] * sqrt ( fabs ( 4.0 * an * n0 + bn * n1 ) ) ;
   R [ 11 ] = R [ 11 ] * sqrt ( fabs ( 3.0 * an * n1 + 2.0 * bn * n2 ) ) ;
   R [ 12 ] = R [ 12 ] * sqrt ( fabs ( 2.0 * an * n2 + 3.0 * bn * n3 ) ) ;
   R [ 13 ] = R [ 13 ] * sqrt ( fabs ( an * n3 + 4.0 * bn * n4 ) ) ;
     return 0; }
 
static void _hoc_rates(void) {
  double _r;
   _r = 1.;
 rates (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 11;}
 
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
	for (_i=0; _i < 11; ++_i) {
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
  mh7 = mh70;
  mh6 = mh60;
  mh5 = mh50;
  mh4 = mh40;
  mh3 = mh30;
  mh2 = mh20;
  mh1 = mh10;
  n4 = n40;
  n3 = n30;
  n2 = n20;
  n1 = n10;
 {
   rates ( _threadargscomma_ v ) ;
   if ( se >= 0.0 ) {
     set_seed ( se ) ;
     }
   M = am / bm ;
   H = ah / bh ;
   N = an / bn ;
   stsum = ( 1.0 + H ) * pow( ( 1.0 + M ) , 3.0 ) ;
   mh0 = 1.0 / stsum ;
   mh1 = 3.0 * M / stsum ;
   mh2 = 3.0 * pow( M , 2.0 ) / stsum ;
   mh3 = pow( M , 3.0 ) / stsum ;
   mh4 = H / stsum ;
   mh5 = H * 3.0 * M / stsum ;
   mh6 = H * 3.0 * pow( M , 2.0 ) / stsum ;
   mh7 = H * pow( M , 3.0 ) / stsum ;
   stsum = pow( ( 1.0 + N ) , 4.0 ) ;
   n0 = 1.0 / stsum ;
   n1 = 4.0 * N / stsum ;
   n2 = 6.0 * pow( N , 2.0 ) / stsum ;
   n3 = 4.0 * pow( N , 3.0 ) / stsum ;
   n4 = pow( N , 4.0 ) / stsum ;
   rates ( _threadargscomma_ v ) ;
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
   ina = gnabar * mh7 * ( v - ena ) ;
   ik = gkbar * n4 * ( v - ek ) ;
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
 { error =  states();
 if(error){fprintf(stderr,"at line 79 in file hhDA.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 }  }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(mh1) - _p;  _dlist1[0] = &(Dmh1) - _p;
 _slist1[1] = &(mh2) - _p;  _dlist1[1] = &(Dmh2) - _p;
 _slist1[2] = &(mh3) - _p;  _dlist1[2] = &(Dmh3) - _p;
 _slist1[3] = &(mh4) - _p;  _dlist1[3] = &(Dmh4) - _p;
 _slist1[4] = &(mh5) - _p;  _dlist1[4] = &(Dmh5) - _p;
 _slist1[5] = &(mh6) - _p;  _dlist1[5] = &(Dmh6) - _p;
 _slist1[6] = &(mh7) - _p;  _dlist1[6] = &(Dmh7) - _p;
 _slist1[7] = &(n1) - _p;  _dlist1[7] = &(Dn1) - _p;
 _slist1[8] = &(n2) - _p;  _dlist1[8] = &(Dn2) - _p;
 _slist1[9] = &(n3) - _p;  _dlist1[9] = &(Dn3) - _p;
 _slist1[10] = &(n4) - _p;  _dlist1[10] = &(Dn4) - _p;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/giulia/Desktop/Tesi/VagrantNeuro/TutorialsNeuron_and_Brian/DAcomparison/HH/Neuron/hhDA.mod";
static const char* nmodl_file_text = 
  "TITLE hh.mod   squid sodium, potassium, and leak channels\n"
  " \n"
  "COMMENT\n"
  "Stochastic Hodgkin and Huxley equations with diffusion aproximation (hhDA)\n"
  "Equations as in Orio & Soudry (2012) PLoS One\n"
  "Variables are unbound and real square roots are ensured by applying absolute values to variables, but only in random terms\n"
  "\n"
  "Sodium channel states are:\n"
  "mh0 = m0h0   mh1 = m1h0   mh2 = m2h0  mh3 = m3h0\n"
  "mh4 = m0h1   mh5 = m1h1   mh6 = m2h1  mh7 = m3h1\n"
  "\n"
  "Implemented for Pezo, Soudry and Orio (2014) Front Comp Neurosci \n"
  "ENDCOMMENT\n"
  " \n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "	(S) = (siemens)\n"
  "}\n"
  " \n"
  "NEURON {\n"
  "	SUFFIX hhDA\n"
  "	USEION na READ ena WRITE ina\n"
  "	USEION k READ ek WRITE ik\n"
  "	NONSPECIFIC_CURRENT il\n"
  "	RANGE gnabar, gkbar, gl, el, NNa, NK, sumN, sumMH, se\n"
  "}\n"
  " \n"
  "PARAMETER {\n"
  "	se=-1    : random seed. If se=-1, seed is not set\n"
  "	gnabar = .12 (S/cm2)	<0,1e9>\n"
  "	gkbar = .036 (S/cm2)	<0,1e9>\n"
  "	gl = .0003 (S/cm2)	<0,1e9>\n"
  "	el = -54.3 (mV)\n"
  "	NNa = 5000\n"
  "	NK = 1600 \n"
  "}\n"
  " \n"
  "ASSIGNED {\n"
  "	v (mV)\n"
  "	celsius (degC)\n"
  "	ena (mV)\n"
  "	ek (mV)\n"
  "	dt (ms)\n"
  "	ina (mA/cm2)\n"
  "	ik (mA/cm2)\n"
  "	il (mA/cm2)\n"
  "	am	(/ms)\n"
  "	ah	(/ms)\n"
  "	an	(/ms)\n"
  "	bm	(/ms)\n"
  "	bh	(/ms)\n"
  "	bn	(/ms)\n"
  "	stsum\n"
  "	M\n"
  "	N\n"
  "	H\n"
  "	R[14]	(/ms)\n"
  "	mh0   :mh0 and n0 are ASSIGNED because they don't follow a differential equation\n"
  "	n0\n"
  "	\n"
  "}\n"
  " \n"
  "STATE {	\n"
  "	mh1\n"
  "	mh2\n"
  "	mh3\n"
  "	mh4\n"
  "	mh5\n"
  "	mh6\n"
  "	mh7\n"
  "	n1\n"
  "	n2\n"
  "	n3\n"
  "	n4\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	ina = gnabar*mh7*(v - ena)\n"
  "	ik = gkbar*n4*(v - ek)\n"
  "	il = gl*(v - el)\n"
  "}\n"
  " \n"
  "INITIAL {\n"
  "	rates(v)	\n"
  "	if (se>=0) {set_seed(se)} :set seed\n"
  "	M=am/bm\n"
  "	H=ah/bh\n"
  "	N=an/bn\n"
  "	stsum=(1+H)*(1+M)^3\n"
  "	mh0=1/stsum\n"
  "	mh1=3*M/stsum\n"
  "	mh2=3*M^2/stsum\n"
  "	mh3=M^3/stsum\n"
  "	mh4=H/stsum\n"
  "	mh5=H*3*M/stsum\n"
  "	mh6=H*3*M^2/stsum\n"
  "	mh7=H*M^3/stsum\n"
  "	\n"
  "	stsum=(1+N)^4\n"
  "	n0=1/stsum\n"
  "	n1=4*N/stsum\n"
  "	n2=6*N^2/stsum\n"
  "	n3=4*N^3/stsum\n"
  "	n4=N^4/stsum\n"
  "	rates(v)\n"
  "}\n"
  "\n"
  "DERIVATIVE states {  \n"
  "	rates(v)\n"
  "	mh1' = (-2*am-bm-ah)*mh1 + 3*am*mh0 + 2*bm*mh2 + bh*mh5 -R[0]+R[1]+R[4]	\n"
  "	mh2' = (-am-2*bm-ah)*mh2 + 2*am*mh1 + 3*bm*mh3 + bh*mh6 -R[1]+R[2]+R[5]\n"
  "	mh3' = (-3*bm-ah)*mh3 + am*mh2 + bh*mh7 -R[2]+R[6]\n"
  "	mh4' = (-3*am-bh)*mh4 + bm*mh5 + ah*mh0 + R[7]-R[3]\n"
  "    	mh5' = (-2*am-bm-bh)*mh5 + 3*am*mh4 + 2*bm*mh6 + ah*mh1 -R[7]+R[8]-R[4]\n"
  "    	mh6' = (-am-2*bm-bh)*mh6 + 2*am*mh5 + 3*bm*mh7 + ah*mh2 -R[8]+R[9]-R[5]\n"
  "   	mh7' = (-3*bm-bh)*mh7 + am*mh6 + ah*mh3 -R[9]-R[6]\n"
  "    	mh0 = 1-mh1-mh2-mh3-mh4-mh5-mh6-mh7 :normalization\n"
  "	\n"
  "	n1' = (-3*an-bn)*n1 + 4*an*n0 + 2*bn*n2 - R[10] + R[11]\n"
  "	n2' = (-2*an-2*bn)*n2 + 3*an*n1 + 3*bn*n3 -R[11] + R[12]\n"
  "	n3' = (-an-3*bn)*n3 + 2*an*n2 + 4*bn*n4 -R[12] + R[13]\n"
  "	n4' = -4*bn*n4 + an*n3 -R[13]\n"
  "	n0 = 1-n1-n2-n3-n4		:normalization\n"
  "}\n"
  " \n"
  "LOCAL q10\n"
  "\n"
  "PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.\n"
  "	LOCAL q10\n"
  "	UNITSOFF\n"
  "	q10 = 3^((celsius - 6.3)/10)\n"
  "	am = q10*0.1*(v+40)/(1-exp(-(v+40)/10))\n"
  "	bm = q10*4*exp(-(v+65)/18)\n"
  "	ah = q10*0.07*exp(-(v+65)/20) \n"
  "	bh = q10/(1+exp(-(v+35)/10))\n"
  "	an = q10*0.01*(v+55)/(1-exp(-(v+55)/10))\n"
  "	bn = q10*0.125*exp(-(v+65)/80)\n"
  "		\n"
  "	FROM ii=0 TO 9 {R[ii]=normrand(0,1/sqrt(NNa*dt))}\n"
  "	FROM ii=10 TO 13 {R[ii]=normrand(0,1/sqrt(NK*dt))}\n"
  "	R[0] = R[0]*sqrt(fabs(3*am*mh0+bm*mh1))\n"
  "	R[1] = R[1]*sqrt(fabs(2*am*mh1+2*bm*mh2))\n"
  "	R[2] = R[2]*sqrt(fabs(am*mh2+3*bm*mh3))\n"
  "	R[3] = R[3]*sqrt(fabs(ah*mh0+bh*mh4))\n"
  "	R[4] = R[4]*sqrt(fabs(ah*mh1+bh*mh5))\n"
  "	R[5] = R[5]*sqrt(fabs(ah*mh2+bh*mh6))\n"
  "	R[6] = R[6]*sqrt(fabs(ah*mh3+bh*mh7))\n"
  "	R[7] = R[7]*sqrt(fabs(3*am*mh4+bm*mh5))\n"
  "	R[8] = R[8]*sqrt(fabs(2*am*mh5+2*bm*mh6))\n"
  "	R[9] = R[9]*sqrt(fabs(am*mh6+3*bm*mh7))\n"
  "	R[10] = R[10]*sqrt(fabs(4*an*n0+bn*n1)) \n"
  "	R[11] = R[11]*sqrt(fabs(3*an*n1+2*bn*n2))\n"
  "	R[12] = R[12]*sqrt(fabs(2*an*n2+3*bn*n3))\n"
  "	R[13] = R[13]*sqrt(fabs(an*n3+4*bn*n4))\n"
  "	UNITSON \n"
  "}\n"
  ;
#endif
