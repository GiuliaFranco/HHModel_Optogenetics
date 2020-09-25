#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _cad_reg(void);
extern void _chanrhod_reg(void);
extern void _gabaa_reg(void);
extern void _kca_reg(void);
extern void _km_reg(void);
extern void _kv_reg(void);
extern void _na_reg(void);
extern void _na12_reg(void);
extern void _na16_reg(void);
extern void _ostim_reg(void);
extern void _xtra_reg(void);
extern void _ca_reg(void);

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," cad.mod");
    fprintf(stderr," chanrhod.mod");
    fprintf(stderr," gabaa.mod");
    fprintf(stderr," kca.mod");
    fprintf(stderr," km.mod");
    fprintf(stderr," kv.mod");
    fprintf(stderr," na.mod");
    fprintf(stderr," na12.mod");
    fprintf(stderr," na16.mod");
    fprintf(stderr," ostim.mod");
    fprintf(stderr," xtra.mod");
    fprintf(stderr," ca.mod");
    fprintf(stderr, "\n");
  }
  _cad_reg();
  _chanrhod_reg();
  _gabaa_reg();
  _kca_reg();
  _km_reg();
  _kv_reg();
  _na_reg();
  _na12_reg();
  _na16_reg();
  _ostim_reg();
  _xtra_reg();
  _ca_reg();
}
