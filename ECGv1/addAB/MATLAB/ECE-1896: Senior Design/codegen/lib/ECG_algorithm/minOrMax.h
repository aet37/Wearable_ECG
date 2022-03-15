/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * minOrMax.h
 *
 * Code generation for function 'minOrMax'
 *
 */

#ifndef MINORMAX_H
#define MINORMAX_H

/* Include files */
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void maximum(const double x_data[], const int x_size[2], double *ex, int *idx);

void minimum(const double x_data[], const int x_size[2], double *ex, int *idx);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (minOrMax.h) */
