/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * isLocalExtrema.c
 *
 * Code generation for function 'isLocalExtrema'
 *
 */

/* Include files */
#include "isLocalExtrema.h"
#include "interp1.h"
#include <string.h>

/* Function Definitions */
void getAllLocalMax(const double A[3600], boolean_T maxVals[3600],
                    boolean_T inflectionPts[3600])
{
  static double b[3599];
  static double b_y1[3599];
  static double varargin_1_data[3599];
  static double varargin_2_data[3599];
  double c_tmp_data[3599];
  double d_tmp_data[3599];
  double tmp2;
  double work;
  int tmp_size[2];
  int varargin_1_size[2];
  int b_i;
  int b_trueCount;
  int i;
  int indEnd;
  int trueCount;
  int xtmp;
  short b_tmp_data[3599];
  short tmp_data[3599];
  boolean_T x[3599];
  boolean_T exitg1;
  boolean_T y;
  work = A[0];
  for (xtmp = 0; xtmp < 3599; xtmp++) {
    tmp2 = work;
    work = A[xtmp + 1];
    tmp2 = work - tmp2;
    if (tmp2 < 0.0) {
      tmp2 = -1.0;
    } else if (tmp2 > 0.0) {
      tmp2 = 1.0;
    }
    b_y1[xtmp] = tmp2;
  }
  y = true;
  xtmp = 0;
  exitg1 = false;
  while ((!exitg1) && (xtmp < 3599)) {
    if (b_y1[xtmp] == 0.0) {
      y = false;
      exitg1 = true;
    } else {
      xtmp++;
    }
  }
  if (!y) {
    for (i = 0; i < 3599; i++) {
      tmp2 = b_y1[i];
      b[i] = tmp2;
      x[i] = (tmp2 != 0.0);
    }
    i = x[0];
    for (xtmp = 0; xtmp < 3598; xtmp++) {
      i += x[xtmp + 1];
    }
    if (i > 1) {
      trueCount = 0;
      xtmp = 0;
      b_trueCount = 0;
      indEnd = 0;
      for (i = 0; i < 3599; i++) {
        tmp2 = b_y1[i];
        if (tmp2 != 0.0) {
          trueCount++;
          tmp_data[xtmp] = (short)(i + 1);
          xtmp++;
        }
        if (tmp2 == 0.0) {
          b_trueCount++;
          b_tmp_data[indEnd] = (short)(i + 1);
          indEnd++;
        }
      }
      varargin_1_size[0] = 1;
      varargin_1_size[1] = trueCount;
      for (b_i = 0; b_i < trueCount; b_i++) {
        varargin_1_data[b_i] = ((double)tmp_data[b_i] - 1.0) + 1.0;
      }
      for (b_i = 0; b_i < trueCount; b_i++) {
        varargin_2_data[b_i] = b_y1[tmp_data[b_i] - 1];
      }
      xtmp = (short)b_trueCount;
      if (0 <= xtmp - 1) {
        memset(&c_tmp_data[0], 0, xtmp * sizeof(double));
      }
      if (b_trueCount != 0) {
        if (tmp_data[1] < tmp_data[0]) {
          b_i = trueCount >> 1;
          for (i = 0; i < b_i; i++) {
            xtmp = (int)varargin_1_data[i];
            indEnd = (trueCount - i) - 1;
            varargin_1_data[i] = varargin_1_data[indEnd];
            varargin_1_data[indEnd] = xtmp;
          }
          if ((trueCount != 0) && (trueCount > 1)) {
            for (xtmp = 0; xtmp < b_i; xtmp++) {
              tmp2 = varargin_2_data[xtmp];
              i = (trueCount - xtmp) - 1;
              varargin_2_data[xtmp] = varargin_2_data[i];
              varargin_2_data[i] = tmp2;
            }
          }
        }
        tmp_size[0] = 1;
        tmp_size[1] = b_trueCount;
        for (b_i = 0; b_i < b_trueCount; b_i++) {
          d_tmp_data[b_i] = ((double)b_tmp_data[b_i] - 1.0) + 1.0;
        }
        interp1Step(varargin_2_data, d_tmp_data, tmp_size, c_tmp_data,
                    varargin_1_data, varargin_1_size);
      }
      xtmp = 0;
      for (i = 0; i < 3599; i++) {
        if (b[i] == 0.0) {
          b[i] = c_tmp_data[xtmp];
          xtmp++;
        }
      }
    }
    tmp2 = 0.0;
    i = 0;
    indEnd = 3598;
    for (xtmp = 0; xtmp < 3599; xtmp++) {
      if (b_y1[xtmp] != 0.0) {
        if (tmp2 == 0.0) {
          i = xtmp;
        }
        indEnd = xtmp;
        tmp2++;
      }
    }
    if (1 > i) {
      xtmp = 0;
    } else {
      xtmp = i;
    }
    for (b_i = 0; b_i < xtmp; b_i++) {
      b[b_i] = b_y1[i];
    }
    if (indEnd + 2 > 3599) {
      b_i = -1;
      i = -1;
    } else {
      b_i = indEnd;
      i = 3598;
    }
    xtmp = i - b_i;
    for (i = 0; i < xtmp; i++) {
      b[(b_i + i) + 1] = b_y1[indEnd];
    }
    memcpy(&b_y1[0], &b[0], 3599U * sizeof(double));
  }
  memset(&maxVals[0], 0, 3600U * sizeof(boolean_T));
  work = b_y1[0];
  inflectionPts[0] = true;
  for (i = 0; i < 3598; i++) {
    tmp2 = work;
    work = b_y1[i + 1];
    maxVals[i + 1] = (work - tmp2 < 0.0);
    inflectionPts[i + 1] = ((b_y1[i] != work) && (A[i + 1] != A[i]));
  }
  inflectionPts[3599] = true;
}

/* End of code generation (isLocalExtrema.c) */
