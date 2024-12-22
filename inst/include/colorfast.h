

#pragma once

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void col_to_rgb(const char *col, int ptr[4]);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static inline void col_to_rgb(const char *col, int ptr[4]) {
  static void (*fun)(const char *,  int[4]) = NULL;
  
  if (fun == NULL) {
    fun = (void (*)(const char *, int[4])) R_GetCCallable("colorfast", "col_to_rgb");
  }
  
  fun(col, ptr);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// uint32_t col_to_int(const char *col); 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static inline uint32_t col_to_int(const char *col) {
  static uint32_t (*fun)(const char *) = NULL;
  
  if (fun == NULL) {
    fun = (uint32_t (*)(const char *)) R_GetCCallable("colorfast", "col_to_int");
  }
  
  return fun(col);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void int_to_col(uint32_t icol, char buf[10]);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static inline void int_to_col(uint32_t icol, char buf[10]) {
  static void (*fun)(uint32_t,  char[10]) = NULL;
  
  if (fun == NULL) {
    fun = (void (*)(uint32_t, char[10])) R_GetCCallable("colorfast", "int_to_col");
  }
  
  fun(icol, buf);
}
