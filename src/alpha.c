
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "hash-color.h"


SEXP set_alpha_(SEXP cols_, SEXP alpha_) {
  
  int N = Rf_length(cols_);
  if (!Rf_isInteger(cols_)) {
    Rf_error("set_alpha_() is valid for integer vectors only");
  }
  uint32_t *col = (uint32_t *)INTEGER(cols_);
  
  SEXP res_ = PROTECT(Rf_allocVector(INTSXP, N));
  uint32_t *res = (uint32_t *)INTEGER(res_);
  
  uint32_t lower = 0x00FFFFFFu;
  
  if (Rf_length(alpha_) == 1) {
    uint32_t alpha = ((uint32_t)(Rf_asReal(alpha_) * 255) & 255) << 24;
    for (int i = 0; i < N; ++i) {
      res[i] = (col[i] & lower) | alpha;
    }
  } else if (Rf_length(alpha_) == N) {
    double *alphas = REAL(alpha_);
    for (int i = 0; i < N; ++i) {
      uint32_t alpha = ((uint32_t)(alphas[i] * 255) & 255) << 24;
      res[i] = (col[i] & lower) | alpha;
    }
    
  } else {
    Rf_error("set_alpha_(): 'alpha' must be length = 1, or same length as 'cols'");
  }
  
  UNPROTECT(1);
  return res_;
}
