#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _WBCN_reg(void);
extern void _ChR2H134R_reg(void);
extern void _hhCN_reg(void);

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," WBCN.mod");
    fprintf(stderr," ChR2H134R.mod");
    fprintf(stderr," hhCN.mod");
    fprintf(stderr, "\n");
  }
  _WBCN_reg();
  _ChR2H134R_reg();
  _hhCN_reg();
}
