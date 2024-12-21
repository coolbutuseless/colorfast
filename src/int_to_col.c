
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Convert single packed_col (integer) to a hexadecimal string in CHARSXP format
// Called from C
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void int_to_col(uint32_t icol, char buf[10]) {
  
  static const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  
  buf[0] = '#';
  buf[9] = '\0';
  
  uint8_t *bptr = (uint8_t *)&icol;
  buf[1] = hexmap[(bptr[0] & 0xF0) >> 4];
  buf[2] = hexmap[(bptr[0] & 0x0F)     ];
  buf[3] = hexmap[(bptr[1] & 0xF0) >> 4];
  buf[4] = hexmap[(bptr[1] & 0x0F)     ];
  buf[5] = hexmap[(bptr[2] & 0xF0) >> 4];
  buf[6] = hexmap[(bptr[2] & 0x0F)     ];
  buf[7] = hexmap[(bptr[3] & 0xF0) >> 4];
  buf[8] = hexmap[(bptr[3] & 0x0F)     ];
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// R function
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP int_to_col_(SEXP icols_) {
  
  uint32_t *icols = (uint32_t *)INTEGER(icols_);
  SEXP res_ = PROTECT(Rf_allocVector(STRSXP, Rf_length(icols_)));
  
  char buf[10];
  for (int i = 0; i < Rf_length(icols_); ++i) {
    int_to_col(icols[i], buf);
    SET_STRING_ELT(res_, i, Rf_mkChar(buf));
  }
  
  UNPROTECT(1);
  return res_;
}

