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
#include "isLocalExtrema.h"
#include "sort.h"
#include <math.h>
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_int32_T_3600
#define struct_emxArray_int32_T_3600
struct emxArray_int32_T_3600 {
  int data[3600];
  int size[1];
};
#endif /* struct_emxArray_int32_T_3600 */
#ifndef typedef_emxArray_int32_T_3600
#define typedef_emxArray_int32_T_3600
typedef struct emxArray_int32_T_3600 emxArray_int32_T_3600;
#endif /* typedef_emxArray_int32_T_3600 */

/* Function Definitions */
void islocalmax(const double A[3600], double varargin_2, boolean_T tf[3600])
{
  static double leftRange_data[3601];
  static double idxTemp[3600];
  static double x_data[3600];
  static double b_y1[3599];
  emxArray_int32_T_3600 b_x_data;
  double ex;
  double localMins_idx_0;
  double localMins_idx_1;
  double work;
  int b_tmp_data[3601];
  int c_tmp_data[3601];
  int b_i;
  int exitg2;
  int exitg3;
  int i;
  int i1;
  int k;
  int leftRange_size;
  int nz;
  int right;
  int trueCount;
  short ranges_data[7202];
  short rightRange_data[3602];
  short locMaxima_data[3600];
  short tmp_data[3600];
  boolean_T c_x_data[3601];
  boolean_T flatRegion_data[3601];
  boolean_T isLocMax[3600];
  boolean_T b;
  boolean_T colRngTF;
  boolean_T exitg4;
  memset(&idxTemp[0], 0, 3600U * sizeof(double));
  getAllLocalMax(A, tf, isLocMax);
  nz = tf[0];
  for (k = 0; k < 3599; k++) {
    nz += tf[k + 1];
  }
  colRngTF = (3600 < nz);
  if ((varargin_2 > 0.0) || colRngTF) {
    ex = A[0];
    for (k = 0; k < 3599; k++) {
      work = A[k + 1];
      if (ex > work) {
        ex = work;
      }
    }
    trueCount = 0;
    nz = 0;
    for (i = 0; i < 3600; i++) {
      b = tf[i];
      if (b || isLocMax[i]) {
        trueCount++;
        locMaxima_data[nz] = (short)(i + 1);
        nz++;
      }
      isLocMax[i] = b;
    }
    for (i = 0; i < trueCount; i++) {
      b_i = locMaxima_data[i];
      if (isLocMax[b_i - 1]) {
        work = A[b_i - 1];
        if ((!colRngTF) && (work - ex < varargin_2)) {
          tf[b_i - 1] = false;
        } else {
          localMins_idx_0 = work;
          localMins_idx_1 = work;
          nz = i - 1;
          right = i + 1;
          do {
            exitg3 = 0;
            if (nz + 1 > 0) {
              i1 = locMaxima_data[nz] - 1;
              if (!isLocMax[i1]) {
                localMins_idx_0 = fmin(localMins_idx_0, A[i1]);
                nz--;
              } else if (A[i1] > work) {
                exitg3 = 1;
              } else {
                nz--;
              }
            } else {
              exitg3 = 2;
            }
          } while (exitg3 == 0);
          do {
            exitg2 = 0;
            if (right + 1 <= trueCount) {
              i1 = locMaxima_data[right] - 1;
              if (!isLocMax[i1]) {
                localMins_idx_1 = fmin(localMins_idx_1, A[i1]);
                right++;
              } else if (A[i1] > work) {
                exitg2 = 1;
              } else {
                right++;
              }
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);
          if (localMins_idx_0 < localMins_idx_1) {
            localMins_idx_0 = localMins_idx_1;
          }
          idxTemp[b_i - 1] = work - localMins_idx_0;
          tf[b_i - 1] = (idxTemp[b_i - 1] >= varargin_2);
        }
      }
    }
  }
  nz = tf[0];
  for (k = 0; k < 3599; k++) {
    nz += tf[k + 1];
  }
  if (3600 < nz) {
    trueCount = 0;
    nz = 0;
    for (i = 0; i < 3600; i++) {
      if (tf[i]) {
        trueCount++;
        tmp_data[nz] = (short)(i + 1);
        nz++;
      }
    }
    if (0 <= trueCount - 1) {
      memcpy(&locMaxima_data[0], &tmp_data[0], trueCount * sizeof(short));
    }
    for (b_i = 0; b_i < trueCount; b_i++) {
      x_data[b_i] = idxTemp[locMaxima_data[b_i] - 1];
    }
    sort(x_data, &trueCount, b_x_data.data, &b_x_data.size[0]);
  }
  colRngTF = false;
  k = 0;
  exitg4 = false;
  while ((!exitg4) && (k < 3600)) {
    if (tf[k]) {
      colRngTF = true;
      exitg4 = true;
    } else {
      k++;
    }
  }
  nz = 0;
  if (colRngTF) {
    nz = 1;
  }
  b_i = (1 <= nz);
  for (k = 0; k < b_i; k++) {
    work = A[0];
    for (nz = 0; nz < 3599; nz++) {
      localMins_idx_0 = work;
      work = A[nz + 1];
      b_y1[nz] = work - localMins_idx_0;
    }
    memset(&idxTemp[0], 0, 3600U * sizeof(double));
    work = 1.0;
    for (nz = 0; nz < 3599; nz++) {
      if (b_y1[nz] != 0.0) {
        idxTemp[(int)work - 1] = (double)nz + 1.0;
        work++;
      }
    }
    if (1.0 > work - 1.0) {
      i = 0;
    } else {
      i = (int)(work - 1.0);
    }
    leftRange_size = i + 1;
    leftRange_data[0] = 1.0;
    for (i1 = 0; i1 < i; i1++) {
      leftRange_data[i1 + 1] = idxTemp[i1] + 1.0;
    }
    if (2 > i + 1) {
      i1 = 0;
      nz = 0;
    } else {
      i1 = 1;
      nz = i + 1;
    }
    trueCount = nz - i1;
    right = trueCount + 1;
    for (nz = 0; nz < trueCount; nz++) {
      rightRange_data[nz] = (short)((int)leftRange_data[i1 + nz] - 1);
    }
    rightRange_data[trueCount] = 3600;
    for (i1 = 0; i1 < right; i1++) {
      flatRegion_data[i1] = (rightRange_data[i1] > (int)leftRange_data[i1]);
    }
    colRngTF = false;
    nz = 1;
    exitg4 = false;
    while ((!exitg4) && (nz <= trueCount + 1)) {
      if (flatRegion_data[nz - 1]) {
        colRngTF = true;
        exitg4 = true;
      } else {
        nz++;
      }
    }
    if (colRngTF) {
      for (i1 = 0; i1 < leftRange_size; i1++) {
        c_x_data[i1] = (tf[(int)leftRange_data[i1] - 1] && flatRegion_data[i1]);
      }
      colRngTF = false;
      nz = 1;
      exitg4 = false;
      while ((!exitg4) && (nz <= i + 1)) {
        if (c_x_data[nz - 1]) {
          colRngTF = true;
          exitg4 = true;
        } else {
          nz++;
        }
      }
      if (colRngTF) {
        right = i;
        trueCount = 0;
        for (i = 0; i <= right; i++) {
          if (tf[(int)leftRange_data[i] - 1] && flatRegion_data[i]) {
            trueCount++;
          }
        }
        nz = 0;
        for (i = 0; i <= right; i++) {
          if (tf[(int)leftRange_data[i] - 1] && flatRegion_data[i]) {
            b_tmp_data[nz] = i + 1;
            nz++;
          }
        }
        for (i1 = 0; i1 < trueCount; i1++) {
          ranges_data[i1] = (short)leftRange_data[b_tmp_data[i1] - 1];
        }
        for (i1 = 0; i1 < trueCount; i1++) {
          ranges_data[i1 + trueCount] = rightRange_data[b_tmp_data[i1] - 1];
        }
        for (i1 = 0; i1 < trueCount; i1++) {
          c_tmp_data[i1] = ranges_data[i1];
        }
        for (i1 = 0; i1 < trueCount; i1++) {
          tf[c_tmp_data[i1] - 1] = false;
        }
        if (trueCount == 0) {
          leftRange_size = 0;
        } else {
          leftRange_size = (short)trueCount;
          for (nz = 0; nz < trueCount; nz++) {
            leftRange_data[nz] = ranges_data[nz];
          }
          for (nz = 0; nz < trueCount; nz++) {
            leftRange_data[nz] += (double)ranges_data[trueCount + nz];
          }
        }
        for (i1 = 0; i1 < leftRange_size; i1++) {
          leftRange_data[i1] /= 2.0;
        }
        for (nz = 0; nz < leftRange_size; nz++) {
          leftRange_data[nz] = floor(leftRange_data[nz]);
        }
        for (i1 = 0; i1 < leftRange_size; i1++) {
          c_tmp_data[i1] = (int)leftRange_data[i1];
        }
        for (i1 = 0; i1 < leftRange_size; i1++) {
          tf[c_tmp_data[i1] - 1] = true;
        }
      }
    }
  }
}

/* End of code generation (islocalmax.c) */
