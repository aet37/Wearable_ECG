/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * islocalmax.c
 *
 * Code generation for function 'islocalmax'
 *
 */

/* Include files */
#include "islocalmax.h"
#include "AlgHRandLeads_internal_types.h"
#include "isLocalExtrema.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void islocalmax(const double A[3600], double varargin_2, boolean_T tf[3600])
{
  static double A_data[3600];
  static double P[3600];
  static double x_data[3600];
  emxArray_int32_T_3600 b_x_data;
  double localMaxValue_tmp;
  double localMins_idx_0;
  double localMins_idx_1;
  double m;
  int b_i;
  int exitg3;
  int exitg4;
  int i;
  int nz;
  int right;
  int tmp_size;
  int trueCount;
  short b_tmp_data[3600];
  short locMaxima_data[3600];
  boolean_T inflectionPts[3600];
  boolean_T isnanA[3600];
  boolean_T tmp_data[3600];
  boolean_T b;
  boolean_T exitg1;
  boolean_T y;
  for (i = 0; i < 3600; i++) {
    localMaxValue_tmp = A[i];
    A_data[i] = localMaxValue_tmp;
    isnanA[i] = rtIsNaN(localMaxValue_tmp);
  }
  y = true;
  right = 0;
  exitg1 = false;
  while ((!exitg1) && (right < 3600)) {
    if (isnanA[right]) {
      y = false;
      exitg1 = true;
    } else {
      right++;
    }
  }
  if (!y) {
    right = 0;
    nz = 0;
    for (b_i = 0; b_i < 3600; b_i++) {
      tf[b_i] = false;
      b = !isnanA[b_i];
      isnanA[b_i] = b;
      if (b) {
        right++;
        locMaxima_data[nz] = (short)(b_i + 1);
        nz++;
      }
    }
    for (i = 0; i < right; i++) {
      A_data[i] = A[locMaxima_data[i] - 1];
    }
    doLocalMaxSearch(A_data, right, varargin_2, tmp_data, &tmp_size, x_data,
                     &trueCount);
    nz = 0;
    for (b_i = 0; b_i < 3600; b_i++) {
      if (isnanA[b_i]) {
        b_tmp_data[nz] = (short)(b_i + 1);
        nz++;
      }
    }
    for (i = 0; i < tmp_size; i++) {
      tf[b_tmp_data[i] - 1] = tmp_data[i];
    }
  } else {
    for (b_i = 0; b_i < 3600; b_i++) {
      P[b_i] = 0.0;
      localMaxValue_tmp = A[b_i];
      b = rtIsInf(localMaxValue_tmp);
      isnanA[b_i] = b;
      y = (localMaxValue_tmp > 0.0);
      tmp_data[b_i] = y;
      if (b && y) {
        A_data[b_i] = rtNaN;
      }
    }
    b_getAllLocalMax(A_data, tf, inflectionPts);
    for (b_i = 0; b_i < 3600; b_i++) {
      b = isnanA[b_i];
      y = tmp_data[b_i];
      tf[b_i] = (tf[b_i] || (b && y));
      if (b && y) {
        A_data[b_i] = rtInf;
      }
    }
    nz = tf[0];
    for (right = 0; right < 3599; right++) {
      nz += tf[right + 1];
    }
    y = (3600 < nz);
    if ((varargin_2 > 0.0) || y) {
      if (!rtIsNaN(A_data[0])) {
        nz = 1;
      } else {
        nz = 0;
        right = 2;
        exitg1 = false;
        while ((!exitg1) && (right <= 3600)) {
          if (!rtIsNaN(A_data[right - 1])) {
            nz = right;
            exitg1 = true;
          } else {
            right++;
          }
        }
      }
      if (nz == 0) {
        m = A_data[0];
      } else {
        m = A_data[nz - 1];
        i = nz + 1;
        for (right = i; right < 3601; right++) {
          localMaxValue_tmp = A_data[right - 1];
          if (m > localMaxValue_tmp) {
            m = localMaxValue_tmp;
          }
        }
      }
      trueCount = 0;
      nz = 0;
      for (b_i = 0; b_i < 3600; b_i++) {
        b = tf[b_i];
        if (b || inflectionPts[b_i]) {
          trueCount++;
          locMaxima_data[nz] = (short)(b_i + 1);
          nz++;
        }
        isnanA[b_i] = b;
      }
      for (b_i = 0; b_i < trueCount; b_i++) {
        i = locMaxima_data[b_i];
        if (isnanA[i - 1]) {
          localMaxValue_tmp = A_data[i - 1];
          if (rtIsInf(localMaxValue_tmp) || rtIsNaN(localMaxValue_tmp)) {
            P[i - 1] = rtInf;
          } else if ((!y) && (localMaxValue_tmp - m < varargin_2)) {
            tf[i - 1] = false;
          } else {
            localMins_idx_0 = localMaxValue_tmp;
            localMins_idx_1 = localMaxValue_tmp;
            nz = b_i - 1;
            right = b_i + 1;
            do {
              exitg4 = 0;
              if (nz + 1 > 0) {
                tmp_size = locMaxima_data[nz] - 1;
                if (!isnanA[tmp_size]) {
                  localMins_idx_0 = fmin(localMins_idx_0, A_data[tmp_size]);
                  nz--;
                } else if (A_data[tmp_size] > localMaxValue_tmp) {
                  exitg4 = 1;
                } else {
                  nz--;
                }
              } else {
                exitg4 = 2;
              }
            } while (exitg4 == 0);
            do {
              exitg3 = 0;
              if (right + 1 <= trueCount) {
                tmp_size = locMaxima_data[right] - 1;
                if (!isnanA[tmp_size]) {
                  localMins_idx_1 = fmin(localMins_idx_1, A_data[tmp_size]);
                  right++;
                } else if (A_data[tmp_size] > localMaxValue_tmp) {
                  exitg3 = 1;
                } else {
                  right++;
                }
              } else {
                exitg3 = 1;
              }
            } while (exitg3 == 0);
            if ((localMins_idx_0 < localMins_idx_1) ||
                (rtIsNaN(localMins_idx_0) && (!rtIsNaN(localMins_idx_1)))) {
              localMins_idx_0 = localMins_idx_1;
            }
            P[i - 1] = localMaxValue_tmp - localMins_idx_0;
            tf[i - 1] = (P[i - 1] >= varargin_2);
          }
        }
      }
    }
    nz = tf[0];
    for (right = 0; right < 3599; right++) {
      nz += tf[right + 1];
    }
    if (3600 < nz) {
      trueCount = 0;
      nz = 0;
      for (b_i = 0; b_i < 3600; b_i++) {
        if (tf[b_i]) {
          trueCount++;
          b_tmp_data[nz] = (short)(b_i + 1);
          nz++;
        }
      }
      if (0 <= trueCount - 1) {
        memcpy(&locMaxima_data[0], &b_tmp_data[0], trueCount * sizeof(short));
      }
      for (i = 0; i < trueCount; i++) {
        x_data[i] = P[locMaxima_data[i] - 1];
      }
      sort(x_data, &trueCount, b_x_data.data, &b_x_data.size[0]);
    }
    b_adjustFlatRegions(A_data, tf);
  }
}

/* End of code generation (islocalmax.c) */
