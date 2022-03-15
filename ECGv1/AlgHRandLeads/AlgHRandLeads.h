/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * AlgHRandLeads.h
 *
 * Code generation for function 'AlgHRandLeads'
 *
 */

#ifndef ALGHRANDLEADS_H
#define ALGHRANDLEADS_H

/* Include files */
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void AlgHRandLeads(const double ECG_data[3600], double *heartRate,
                          boolean_T *leadsFlipped);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (AlgHRandLeads.h) */
