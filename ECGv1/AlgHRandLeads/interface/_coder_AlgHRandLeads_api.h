/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_AlgHRandLeads_api.h
 *
 * Code generation for function 'AlgHRandLeads'
 *
 */

#ifndef _CODER_ALGHRANDLEADS_API_H
#define _CODER_ALGHRANDLEADS_API_H

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
void AlgHRandLeads(real_T ECG_data[3600], real_T *heartRate,
                   boolean_T *leadsFlipped);

void AlgHRandLeads_api(const mxArray *prhs, int32_T nlhs,
                       const mxArray *plhs[2]);

void AlgHRandLeads_atexit(void);

void AlgHRandLeads_initialize(void);

void AlgHRandLeads_terminate(void);

void AlgHRandLeads_xil_shutdown(void);

void AlgHRandLeads_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_AlgHRandLeads_api.h) */
