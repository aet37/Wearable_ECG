/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ECG_algorithm_api.h
 *
 * Code generation for function 'ECG_algorithm'
 *
 */

#ifndef _CODER_ECG_ALGORITHM_API_H
#define _CODER_ECG_ALGORITHM_API_H

/* Include files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void ECG_algorithm(real_T ECG_data[3600], real_T *heartRate,
                   real_T p_index_data[], int32_T p_index_size[2],
                   real_T q_index_data[], int32_T q_index_size[2],
                   real_T r_index_data[], int32_T r_index_size[2],
                   real_T s_index_data[], int32_T s_index_size[2],
                   real_T t_index_data[], int32_T t_index_size[2],
                   emxArray_real_T *px_values, emxArray_real_T *tx_values,
                   emxArray_real_T *y_values);

void ECG_algorithm_api(const mxArray *prhs, int32_T nlhs,
                       const mxArray *plhs[9]);

void ECG_algorithm_atexit(void);

void ECG_algorithm_initialize(void);

void ECG_algorithm_terminate(void);

void ECG_algorithm_xil_shutdown(void);

void ECG_algorithm_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_ECG_algorithm_api.h) */
