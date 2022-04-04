/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * AlgHRandLeads_initialize.c
 *
 * Code generation for function 'AlgHRandLeads_initialize'
 *
 */

/* Include files */
#include "AlgHRandLeads_initialize.h"
#include "AlgHRandLeads_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void AlgHRandLeads_initialize(void)
{
  omp_init_nest_lock(&AlgHRandLeads_nestLockGlobal);
  isInitialized_AlgHRandLeads = true;
}

/* End of code generation (AlgHRandLeads_initialize.c) */
