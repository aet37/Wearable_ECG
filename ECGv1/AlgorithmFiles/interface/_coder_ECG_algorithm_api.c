/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ECG_algorithm_api.c
 *
 * Code generation for function 'ECG_algorithm'
 *
 */

/* Include files */
#include "_coder_ECG_algorithm_api.h"
#include "_coder_ECG_algorithm_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131611U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "ECG_algorithm",                                      /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3600];

static const mxArray *b_emlrt_marshallOut(const real_T u_data[],
                                          const int32_T u_size[2]);

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3600];

static const mxArray *c_emlrt_marshallOut(const emxArray_real_T *u);

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *ECG_data,
                                 const char_T *identifier))[3600];

static const mxArray *emlrt_marshallOut(const real_T u);

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

/* Function Definitions */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3600]
{
  real_T(*y)[3600];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *b_emlrt_marshallOut(const real_T u_data[],
                                          const int32_T u_size[2])
{
  static const int32_T iv[2] = {0, 0};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m, &u_size[0], 2);
  emlrtAssign(&y, m);
  return y;
}

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3600]
{
  static const int32_T dims[2] = {1, 3600};
  real_T(*ret)[3600];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  ret = (real_T(*)[3600])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static const mxArray *c_emlrt_marshallOut(const emxArray_real_T *u)
{
  static const int32_T iv[2] = {0, 0};
  const mxArray *m;
  const mxArray *y;
  const real_T *u_data;
  u_data = u->data;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m, &u->size[0], 2);
  emlrtAssign(&y, m);
  return y;
}

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *ECG_data,
                                 const char_T *identifier))[3600]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[3600];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(ECG_data), &thisId);
  emlrtDestroyArray(&ECG_data);
  return y;
}

static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference((emlrtCTX)sp, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocEmxArray(sizeof(emxArray_real_T));
  emlrtPushHeapReferenceStackEmxArray((emlrtCTX)sp, true, (void *)pEmxArray,
                                      (void *)&emxFree_real_T, NULL, NULL,
                                      NULL);
  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = 2;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * 2U);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < 2; i++) {
    emxArray->size[i] = 0;
  }
}

void ECG_algorithm_api(const mxArray *prhs, int32_T nlhs,
                       const mxArray *plhs[9])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  emxArray_real_T *px_values;
  emxArray_real_T *tx_values;
  emxArray_real_T *y_values;
  real_T(*ECG_data)[3600];
  real_T(*p_index_data)[3600];
  real_T(*q_index_data)[3600];
  real_T(*r_index_data)[3600];
  real_T(*s_index_data)[3600];
  real_T(*t_index_data)[3600];
  real_T heartRate;
  int32_T p_index_size[2];
  int32_T q_index_size[2];
  int32_T r_index_size[2];
  int32_T s_index_size[2];
  int32_T t_index_size[2];
  st.tls = emlrtRootTLSGlobal;
  p_index_data = (real_T(*)[3600])mxMalloc(sizeof(real_T[3600]));
  q_index_data = (real_T(*)[3600])mxMalloc(sizeof(real_T[3600]));
  r_index_data = (real_T(*)[3600])mxMalloc(sizeof(real_T[3600]));
  s_index_data = (real_T(*)[3600])mxMalloc(sizeof(real_T[3600]));
  t_index_data = (real_T(*)[3600])mxMalloc(sizeof(real_T[3600]));
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T(&st, &px_values);
  emxInit_real_T(&st, &tx_values);
  emxInit_real_T(&st, &y_values);
  /* Marshall function inputs */
  ECG_data = emlrt_marshallIn(&st, emlrtAlias(prhs), "ECG_data");
  /* Invoke the target function */
  ECG_algorithm(*ECG_data, &heartRate, *p_index_data, p_index_size,
                *q_index_data, q_index_size, *r_index_data, r_index_size,
                *s_index_data, s_index_size, *t_index_data, t_index_size,
                px_values, tx_values, y_values);
  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(heartRate);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*p_index_data, p_index_size);
  }
  if (nlhs > 2) {
    plhs[2] = b_emlrt_marshallOut(*q_index_data, q_index_size);
  }
  if (nlhs > 3) {
    plhs[3] = b_emlrt_marshallOut(*r_index_data, r_index_size);
  }
  if (nlhs > 4) {
    plhs[4] = b_emlrt_marshallOut(*s_index_data, s_index_size);
  }
  if (nlhs > 5) {
    plhs[5] = b_emlrt_marshallOut(*t_index_data, t_index_size);
  }
  if (nlhs > 6) {
    px_values->canFreeData = false;
    plhs[6] = c_emlrt_marshallOut(px_values);
  }
  emxFree_real_T(&st, &px_values);
  if (nlhs > 7) {
    tx_values->canFreeData = false;
    plhs[7] = c_emlrt_marshallOut(tx_values);
  }
  emxFree_real_T(&st, &tx_values);
  if (nlhs > 8) {
    y_values->canFreeData = false;
    plhs[8] = c_emlrt_marshallOut(y_values);
  }
  emxFree_real_T(&st, &y_values);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

void ECG_algorithm_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  ECG_algorithm_xil_terminate();
  ECG_algorithm_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void ECG_algorithm_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void ECG_algorithm_terminate(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_ECG_algorithm_api.c) */
