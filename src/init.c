
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern SEXP col_to_rgb_(SEXP cols_);
extern SEXP col_to_int_(SEXP cols_);

static const R_CallMethodDef CEntries[] = {
  
  {"col_to_rgb_", (DL_FUNC) &col_to_rgb_, 1},
  {"col_to_int_", (DL_FUNC) &col_to_int_, 1},
  {NULL , NULL, 0}
};


void R_init_colorfast(DllInfo *info) {
  R_registerRoutines(
    info,      // DllInfo
    NULL,      // .C
    CEntries,  // .Call
    NULL,      // Fortran
    NULL       // External
  );
  R_useDynamicSymbols(info, FALSE);
}



