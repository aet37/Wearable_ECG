/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ECG_algorithm.h
 *
 * Code generation for function 'ECG_algorithm'
 *
 */

#ifndef ECG_ALGORITHM_H
#define ECG_ALGORITHM_H

/* Include files */
#include "ECG_algorithm_types.h"
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void
ECG_algorithm(const double ECG_data[3600], double *heartRate,
              double p_index_data[], int p_index_size[2], double q_index_data[],
              int q_index_size[2], double r_index_data[], int r_index_size[2],
              double s_index_data[], int s_index_size[2], double t_index_data[],
              int t_index_size[2], emxArray_real_T *px_values,
              emxArray_real_T *tx_values, emxArray_real_T *y_values);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (ECG_algorithm.h) */
