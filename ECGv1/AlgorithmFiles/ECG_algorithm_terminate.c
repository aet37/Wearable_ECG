/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ECG_algorithm_terminate.c
 *
 * Code generation for function 'ECG_algorithm_terminate'
 *
 */

/* Include files */
#include "ECG_algorithm_terminate.h"
#include "ECG_algorithm_data.h"

/* Function Definitions */
void ECG_algorithm_terminate(void)
{
  omp_destroy_nest_lock(&ECG_algorithm_nestLockGlobal);
  isInitialized_ECG_algorithm = false;
}

/* End of code generation (ECG_algorithm_terminate.c) */
