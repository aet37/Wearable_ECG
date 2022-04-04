/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_addAB_api.h
 *
 * Code generation for function 'addAB'
 *
 */

#ifndef _CODER_ADDAB_API_H
#define _CODER_ADDAB_API_H

/* Include files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
real_T addAB(real_T A, real_T B);

void addAB_api(const mxArray *const prhs[2], const mxArray **plhs);

void addAB_atexit(void);

void addAB_initialize(void);

void addAB_terminate(void);

void addAB_xil_shutdown(void);

void addAB_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_addAB_api.h) */
