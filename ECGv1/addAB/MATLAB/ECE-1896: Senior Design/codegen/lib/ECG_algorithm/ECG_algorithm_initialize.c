/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ECG_algorithm_initialize.c
 *
 * Code generation for function 'ECG_algorithm_initialize'
 *
 */

/* Include files */
#include "ECG_algorithm_initialize.h"
#include "ECG_algorithm_data.h"

/* Function Definitions */
void ECG_algorithm_initialize(void)
{
  omp_init_nest_lock(&ECG_algorithm_nestLockGlobal);
  isInitialized_ECG_algorithm = true;
}

/* End of code generation (ECG_algorithm_initialize.c) */
