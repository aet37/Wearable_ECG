/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * interp1.h
 *
 * Code generation for function 'interp1'
 *
 */

#ifndef INTERP1_H
#define INTERP1_H

/* Include files */
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void interp1(const double varargin_1_data[], const int varargin_1_size[2],
             const double varargin_2_data[], int varargin_2_size,
             const double varargin_3_data[], const int varargin_3_size[2],
             double Vq_data[], int Vq_size[2]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (interp1.h) */
