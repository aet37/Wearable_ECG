/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * isLocalExtrema.h
 *
 * Code generation for function 'isLocalExtrema'
 *
 */

#ifndef ISLOCALEXTREMA_H
#define ISLOCALEXTREMA_H

/* Include files */
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_adjustFlatRegions(const double A[3600], boolean_T maxVals[3600]);

void b_getAllLocalMax(const double A[3600], boolean_T maxVals[3600],
                      boolean_T inflectionPts[3600]);

void doLocalMaxSearch(double A_data[], int A_size, double minProm,
                      boolean_T maxVals_data[], int *maxVals_size,
                      double P_data[], int *P_size);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (isLocalExtrema.h) */
