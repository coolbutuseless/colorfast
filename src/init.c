
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include <stdint.h>

extern SEXP col_to_rgb_(SEXP cols_);
extern SEXP col_to_int_(SEXP cols_);
extern SEXP int_to_col_(SEXP icols_);

extern SEXP set_alpha_(SEXP cols_, SEXP alpha_);

static const R_CallMethodDef CEntries[] = {
  
  {"col_to_rgb_", (DL_FUNC) &col_to_rgb_, 1},
  {"col_to_int_", (DL_FUNC) &col_to_int_, 1},
  {"int_to_col_", (DL_FUNC) &int_to_col_, 1},
  
  {"set_alpha_", (DL_FUNC) &set_alpha_, 2},
  
  {NULL , NULL, 0}
};



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Make the C code available to other packages
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern void     col_to_rgb(const char *col, int ptr[4]);
extern uint32_t col_to_int(const char *col); 
extern void     int_to_col(uint32_t icol, char buf[10]);

void R_init_colorfast(DllInfo *info) {
  R_registerRoutines(
    info,      // DllInfo
    NULL,      // .C
    CEntries,  // .Call
    NULL,      // Fortran
    NULL       // External
  );
  R_useDynamicSymbols(info, FALSE);
  
  R_RegisterCCallable("colorfast", "col_to_rgb", (DL_FUNC) &col_to_rgb);
  R_RegisterCCallable("colorfast", "col_to_int", (DL_FUNC) &col_to_int);
  R_RegisterCCallable("colorfast", "int_to_col", (DL_FUNC) &int_to_col);
}
