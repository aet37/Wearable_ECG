/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * polyfit.h
 *
 * Code generation for function 'polyfit'
 *
 */

#ifndef POLYFIT_H
#define POLYFIT_H

/* Include files */
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void polyfit(double x[3600], const double y[3600], double p[10],
             double S_R[100], double *S_df, double *S_normr, double mu[2]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (polyfit.h) */
