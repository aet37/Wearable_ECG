/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * AlgHRandLeads_terminate.c
 *
 * Code generation for function 'AlgHRandLeads_terminate'
 *
 */

/* Include files */
#include "AlgHRandLeads_terminate.h"
#include "AlgHRandLeads_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void AlgHRandLeads_terminate(void)
{
  omp_destroy_nest_lock(&AlgHRandLeads_nestLockGlobal);
  isInitialized_AlgHRandLeads = false;
}

/* End of code generation (AlgHRandLeads_terminate.c) */
