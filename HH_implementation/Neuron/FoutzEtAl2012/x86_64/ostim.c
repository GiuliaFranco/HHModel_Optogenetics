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
 
#define nrn_init _nrn_init__ostim
#define _nrn_initial _nrn_initial__ostim
#define nrn_cur _nrn_cur__ostim
#define _nrn_current _nrn_current__ostim
#define nrn_jacob _nrn_jacob__ostim
#define nrn_state _nrn_state__ostim
#define _net_receive _net_receive__ostim 
 
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
#define radius _p[0]
#define delay _p[1]
#define dur _p[2]
#define amp _p[3]
#define wavelength _p[4]
#define pulses _p[5]
#define isi _p[6]
#define pcount _p[7]
#define on _p[8]
#define _tsav _p[9]
#define _nd_area  *_ppvar[0]._pval
#define irradiance	*_ppvar[2]._pval
#define _p_irradiance	_ppvar[2]._pval
#define flux	*_ppvar[3]._pval
#define _p_flux	_ppvar[3]._pval
#define photons	*_ppvar[4]._pval
#define _p_photons	_ppvar[4]._pval
#define tstimon	*_ppvar[5]._pval
#define _p_tstimon	_ppvar[5]._pval
#define tstimoff	*_ppvar[6]._pval
#define _p_tstimoff	_ppvar[6]._pval
#define area	*_ppvar[7]._pval
 
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
 static int hoc_nrnpointerindex =  2;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_calc_irradiance_photons_flux();
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

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "calc_irradiance_photons_flux", _hoc_calc_irradiance_photons_flux,
 0, 0
};
#define calc_irradiance_photons_flux calc_irradiance_photons_flux_ostim
 extern double calc_irradiance_photons_flux( );
 /* declare global and static user variables */
#define c c_ostim
 double c = 2.99792e+08;
#define h h_ostim
 double h = 6.62607e-34;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "h_ostim", "m2",
 "c_ostim", "m/s",
 "radius", "um",
 "delay", "ms",
 "dur", "ms",
 "amp", "W/cm2",
 "wavelength", "m",
 "isi", "ms",
 "irradiance", "W/cm2",
 "flux", "1/ms cm2",
 "photons", "photons/ms",
 0,0
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "h_ostim", &h_ostim,
 "c_ostim", &c_ostim,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void _ba1() ;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"ostim",
 "radius",
 "delay",
 "dur",
 "amp",
 "wavelength",
 "pulses",
 "isi",
 0,
 "pcount",
 0,
 0,
 "irradiance",
 "flux",
 "photons",
 "tstimon",
 "tstimoff",
 0};
 extern Node* nrn_alloc_node_;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 10, _prop);
 	/*initialize range parameters*/
 	radius = 100;
 	delay = 1;
 	dur = 5;
 	amp = 38;
 	wavelength = 4.73e-07;
 	pulses = 1;
 	isi = 1;
  }
 	_prop->param = _p;
 	_prop->param_size = 10;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 9, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 	_ppvar[7]._pval = &nrn_alloc_node_->_area; /* diam */
 
}
 static void _initlists();
 
#define _tqitem &(_ppvar[8]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _ostim_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,(void*)0, (void*)0, (void*)0, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 10, 9);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
  hoc_register_dparam_semantics(_mechtype, 3, "pointer");
  hoc_register_dparam_semantics(_mechtype, 4, "pointer");
  hoc_register_dparam_semantics(_mechtype, 5, "pointer");
  hoc_register_dparam_semantics(_mechtype, 6, "pointer");
  hoc_register_dparam_semantics(_mechtype, 8, "netsend");
  hoc_register_dparam_semantics(_mechtype, 7, "area");
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_reg_ba(_mechtype, _ba1, 11);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ostim /Users/giulia/Desktop/FoutzEtAl2012/x86_64/ostim.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double PI = 3.14159;
static int _reset;
static char *modelname = "Optical Stimulation";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 /* BEFORE BREAKPOINT */
 static void _ba1(Node*_nd, double* _pp, Datum* _ppd, Datum* _thread, _NrnThread* _nt)  {
    _p = _pp; _ppvar = _ppd;
  v = NODEV(_nd);
 if ( on  == 0.0 ) {
     irradiance = 0.0 ;
     photons = 0.0 ;
     flux = 0.0 ;
     }
   else if ( on  == 1.0 ) {
     calc_irradiance_photons_flux ( _threadargs_ ) ;
     }
   }
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 1.0 ) {
     on = 1.0 ;
     tstimon = t ;
     pcount = pcount - 1.0 ;
     if ( pcount > 0.0 ) {
       net_send ( _tqitem, _args, _pnt, t +  dur , 3.0 ) ;
       }
     else {
       net_send ( _tqitem, _args, _pnt, t +  dur , 2.0 ) ;
       }
     }
   else if ( _lflag  == 2.0 ) {
     on = 0.0 ;
     tstimoff = t ;
     }
   else if ( _lflag  == 3.0 ) {
     on = 0.0 ;
     net_send ( _tqitem, _args, _pnt, t +  isi , 1.0 ) ;
     tstimoff = t ;
     }
   } }
 
double calc_irradiance_photons_flux (  ) {
   double _lcalc_irradiance_photons_flux;
 double _lphoton_energy , _larea ;
 irradiance = amp ;
   _lphoton_energy = h * c / wavelength ;
   flux = ( 1.0 / 1000.0 ) * amp / _lphoton_energy ;
   _larea = PI * ( pow( radius , 2.0 ) ) ;
   photons = 1e-8 * flux * _larea ;
   
return _lcalc_irradiance_photons_flux;
 }
 
static double _hoc_calc_irradiance_photons_flux(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  calc_irradiance_photons_flux (  );
 return(_r);
}

static void initmodel() {
  int _i; double _save;_ninits++;
{
 {
   on = 0.0 ;
   pcount = pulses ;
   irradiance = 0.0 ;
   flux = 0.0 ;
   photons = 0.0 ;
   net_send ( _tqitem, (double*)0, _ppvar[1]._pvoid, t +  delay , 1.0 ) ;
   tstimon = 0.0 ;
   tstimoff = 0.0 ;
   }

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
 _tsav = -1e20;
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

static double _nrn_current(double _v){double _current=0.;v=_v;{
} return _current;
}

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
}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/giulia/Desktop/FoutzEtAl2012/ostim.mod";
static const char* nmodl_file_text = 
  ": test units: modlunit ostim.mod\n"
  "\n"
  "TITLE Optical Stimulation\n"
  "\n"
  "NEURON {\n"
  "    POINT_PROCESS ostim\n"
  "    RANGE radius\n"
  "    RANGE delay, amp, dur\n"
  "    RANGE pulses, isi, pcount\n"
  "    POINTER irradiance\n"
  "    POINTER flux\n"
  "    POINTER photons\n"
  "    POINTER tstimon\n"
  "    POINTER tstimoff\n"
  "    RANGE wavelength\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "    (mW) = (milliwatt)\n"
  "    (W)  = (watt)\n"
  "    PI   = (pi)             (1)\n"
  "\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    radius    = 100             (um)\n"
  "    delay     = 1               (ms)\n"
  "    dur       = 5               (ms)\n"
  "    : Aravanis et al 2007\n"
  "    :     Psrc = 20 mW\n"
  "    :     Af = 0.6\n"
  "    :     r = 0.1 mm\n"
  "    :     Irradiance = Af * Psrc/(pi * r**2) = 380 mW/mm2 --> 0.38 W/mm2 --> 38 W/cm2\n"
  "    amp = 38                    (W/cm2)\n"
  "    wavelength = 4.73e-7        (m)\n"
  "    h = 6.6260693e-34           (m2 kg/s)  : planck's constant\n"
  "    c = 299792458.0             (m/s)      : speed of light\n"
  "\n"
  "    : Number of pulses\n"
  "    pulses = 1\n"
  "    isi    = 1                 (ms)        : Inter-spike interval\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    on\n"
  "    irradiance (W/cm2)         : W/cm2\n"
  "    flux      (1/ms cm2)       : photons/ms cm2\n"
  "    photons   (photons/ms)     : photons/ms\n"
  "    pcount\n"
  "    tstimon\n"
  "    tstimoff\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    on          = 0\n"
  "    pcount      = pulses\n"
  "    irradiance   = 0\n"
  "    flux        = 0\n"
  "    photons     = 0\n"
  "    net_send(delay,1)          : Sends a packet that should arrive after given initial_delay\n"
  "    tstimon     = 0\n"
  "    tstimoff    = 0\n"
  "}\n"
  "\n"
  "BEFORE BREAKPOINT {\n"
  "    if (on==0) {\n"
  "        irradiance = 0\n"
  "        photons   = 0\n"
  "        flux      = 0\n"
  "    } else if (on==1) {\n"
  "        calc_irradiance_photons_flux()\n"
  "    }\n"
  "}\n"
  "\n"
  "NET_RECEIVE (w) {\n"
  "    if (flag==1) {\n"
  "        on = 1\n"
  "        tstimon = t\n"
  "        pcount = pcount - 1\n"
  "        if (pcount>0) {\n"
  "            net_send(dur,3)\n"
  "        } else {\n"
  "            net_send(dur,2)\n"
  "        }\n"
  "    }else if (flag==2) { : stimulus complete\n"
  "        on = 0\n"
  "        tstimoff = t\n"
  "    }else if (flag==3) { : spike train\n"
  "        on = 0\n"
  "        net_send(isi,1)\n"
  "        tstimoff = t\n"
  "    }\n"
  "\n"
  "}\n"
  "\n"
  "FUNCTION calc_irradiance_photons_flux() {\n"
  "    LOCAL photon_energy, area\n"
  "    irradiance = amp\n"
  "    photon_energy = h * c / wavelength : J / photon\n"
  "    flux = (1 / 1000) * amp / photon_energy : (1 s / 1000 ms) * (W/cm2) * (photons/W s)\n"
  "                                              :     --> photons/ms cm2\n"
  "    area = PI * (radius ^ 2) : um2\n"
  "    photons = 1e-8 * flux * area : (1 cm2/1e8 um2) * (um2) * (photons/ms cm2)\n"
  "}\n"
  "\n"
  ;
#endif
