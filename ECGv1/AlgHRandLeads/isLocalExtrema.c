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
#include "AlgHRandLeads_internal_types.h"
#include "diff.h"
#include "interp1.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static void adjustFlatRegions(const double A_data[], int A_size,
                              boolean_T maxVals_data[],
                              const int *maxVals_size);

static void getAllLocalMax(const double A_data[], int A_size,
                           boolean_T maxVals_data[], int *maxVals_size,
                           boolean_T inflectionPts_data[],
                           int *inflectionPts_size);

/* Function Definitions */
static void adjustFlatRegions(const double A_data[], int A_size,
                              boolean_T maxVals_data[], const int *maxVals_size)
{
  static double leftRange_data[3601];
  static double b_A_data[3600];
  static double tmp_data[3599];
  double b_ctr;
  int b_tmp_data[3601];
  int c_tmp_data[3601];
  int ctr;
  int i;
  int i1;
  int j;
  int k;
  int leftRange_size;
  int loop_ub;
  int trueCount;
  short ranges_data[7202];
  short rightRange_data[3602];
  short idxTemp_data[3600];
  boolean_T flatRegion_data[3601];
  boolean_T x_data[3601];
  boolean_T locUniLeadMax_data[3599];
  boolean_T colRngTF;
  boolean_T exitg1;
  colRngTF = false;
  ctr = 1;
  exitg1 = false;
  while ((!exitg1) && (ctr <= *maxVals_size)) {
    if (maxVals_data[ctr - 1]) {
      colRngTF = true;
      exitg1 = true;
    } else {
      ctr++;
    }
  }
  ctr = 0;
  if (colRngTF) {
    ctr = 1;
  }
  i = (1 <= ctr);
  if ((0 <= i - 1) && (0 <= A_size - 1)) {
    memcpy(&b_A_data[0], &A_data[0], A_size * sizeof(double));
  }
  for (k = 0; k < i; k++) {
    diff(b_A_data, A_size, tmp_data, &ctr);
    for (i1 = 0; i1 < ctr; i1++) {
      locUniLeadMax_data[i1] = (tmp_data[i1] != 0.0);
    }
    if (0 <= A_size - 1) {
      memset(&idxTemp_data[0], 0, A_size * sizeof(short));
    }
    b_ctr = 1.0;
    for (j = 0; j < ctr; j++) {
      if (locUniLeadMax_data[j]) {
        idxTemp_data[(int)b_ctr - 1] = (short)(j + 1);
        b_ctr++;
      }
    }
    if (1.0 > b_ctr - 1.0) {
      j = 0;
    } else {
      j = (int)(b_ctr - 1.0);
    }
    leftRange_size = j + 1;
    leftRange_data[0] = 1.0;
    for (i1 = 0; i1 < j; i1++) {
      leftRange_data[i1 + 1] = (double)idxTemp_data[i1] + 1.0;
    }
    if (2 > j + 1) {
      i1 = 0;
      trueCount = 0;
    } else {
      i1 = 1;
      trueCount = j + 1;
    }
    loop_ub = trueCount - i1;
    ctr = loop_ub + 1;
    for (trueCount = 0; trueCount < loop_ub; trueCount++) {
      rightRange_data[trueCount] =
          (short)((short)leftRange_data[i1 + trueCount] - 1);
    }
    rightRange_data[loop_ub] = (short)A_size;
    for (i1 = 0; i1 < ctr; i1++) {
      flatRegion_data[i1] = (rightRange_data[i1] > (int)leftRange_data[i1]);
    }
    colRngTF = false;
    ctr = 1;
    exitg1 = false;
    while ((!exitg1) && (ctr <= loop_ub + 1)) {
      if (flatRegion_data[ctr - 1]) {
        colRngTF = true;
        exitg1 = true;
      } else {
        ctr++;
      }
    }
    if (colRngTF) {
      for (i1 = 0; i1 < leftRange_size; i1++) {
        x_data[i1] =
            (maxVals_data[(int)leftRange_data[i1] - 1] && flatRegion_data[i1]);
      }
      colRngTF = false;
      ctr = 1;
      exitg1 = false;
      while ((!exitg1) && (ctr <= j + 1)) {
        if (x_data[ctr - 1]) {
          colRngTF = true;
          exitg1 = true;
        } else {
          ctr++;
        }
      }
      if (colRngTF) {
        ctr = j;
        trueCount = 0;
        for (loop_ub = 0; loop_ub <= j; loop_ub++) {
          if (maxVals_data[(int)leftRange_data[loop_ub] - 1] &&
              flatRegion_data[loop_ub]) {
            trueCount++;
          }
        }
        j = 0;
        for (loop_ub = 0; loop_ub <= ctr; loop_ub++) {
          if (maxVals_data[(int)leftRange_data[loop_ub] - 1] &&
              flatRegion_data[loop_ub]) {
            b_tmp_data[j] = loop_ub + 1;
            j++;
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
          maxVals_data[c_tmp_data[i1] - 1] = false;
        }
        if (trueCount == 0) {
          leftRange_size = 0;
        } else {
          leftRange_size = (short)trueCount;
          for (ctr = 0; ctr < trueCount; ctr++) {
            leftRange_data[ctr] = ranges_data[ctr];
          }
          for (ctr = 0; ctr < trueCount; ctr++) {
            leftRange_data[ctr] += (double)ranges_data[trueCount + ctr];
          }
        }
        for (i1 = 0; i1 < leftRange_size; i1++) {
          leftRange_data[i1] /= 2.0;
        }
        for (ctr = 0; ctr < leftRange_size; ctr++) {
          leftRange_data[ctr] = floor(leftRange_data[ctr]);
        }
        for (i1 = 0; i1 < leftRange_size; i1++) {
          c_tmp_data[i1] = (int)leftRange_data[i1];
        }
        for (i1 = 0; i1 < leftRange_size; i1++) {
          maxVals_data[c_tmp_data[i1] - 1] = true;
        }
      }
    }
  }
}

static void getAllLocalMax(const double A_data[], int A_size,
                           boolean_T maxVals_data[], int *maxVals_size,
                           boolean_T inflectionPts_data[],
                           int *inflectionPts_size)
{
  static double b_data[3599];
  static double b_s_data[3599];
  static double b_y_data[3599];
  static double c_y_data[3599];
  static double d_tmp_data[3599];
  static double s_data[3599];
  double ctr;
  int b_y_size[2];
  int tmp_size[2];
  int y_size[2];
  int i;
  int indEnd;
  int k;
  int nz;
  int s_size;
  int trueCount;
  short y_data[3600];
  short b_tmp_data[3599];
  short tmp_data[3599];
  boolean_T b_uniquePts_data[3600];
  boolean_T c_tmp_data[3600];
  boolean_T nanMask_data[3600];
  boolean_T uniquePts_data[3600];
  boolean_T idx_data[3599];
  boolean_T x_data[3599];
  boolean_T exitg1;
  boolean_T y;
  diff(A_data, A_size, s_data, &s_size);
  for (k = 0; k < s_size; k++) {
    ctr = s_data[k];
    if (ctr < 0.0) {
      ctr = -1.0;
    } else if (ctr > 0.0) {
      ctr = 1.0;
    } else if (ctr == 0.0) {
      ctr = 0.0;
    }
    s_data[k] = ctr;
  }
  for (i = 0; i < A_size; i++) {
    nanMask_data[i] = rtIsNaN(A_data[i]);
  }
  y = false;
  nz = 1;
  exitg1 = false;
  while ((!exitg1) && (nz <= A_size)) {
    if (nanMask_data[nz - 1]) {
      y = true;
      exitg1 = true;
    } else {
      nz++;
    }
  }
  if (y) {
    for (i = 0; i <= A_size - 2; i++) {
      if (nanMask_data[i]) {
        s_data[i] = -1.0;
      }
    }
    nz = A_size - 1;
    for (i = 0; i < nz; i++) {
      idx_data[i] = !nanMask_data[i];
    }
    for (i = 0; i < nz; i++) {
      if (idx_data[i] && nanMask_data[i + 1]) {
        s_data[i] = 1.0;
      }
    }
  }
  y = true;
  nz = 1;
  exitg1 = false;
  while ((!exitg1) && (nz <= s_size)) {
    if (s_data[nz - 1] == 0.0) {
      y = false;
      exitg1 = true;
    } else {
      nz++;
    }
  }
  if (!y) {
    if (0 <= s_size - 1) {
      memcpy(&b_data[0], &s_data[0], s_size * sizeof(double));
    }
    for (i = 0; i < s_size; i++) {
      idx_data[i] = (s_data[i] != 0.0);
    }
    for (i = 0; i < s_size; i++) {
      x_data[i] = (s_data[i] != 0.0);
    }
    if (s_size == 0) {
      nz = 0;
    } else {
      nz = x_data[0];
      for (k = 2; k <= s_size; k++) {
        nz += x_data[k - 1];
      }
    }
    if (nz > 1) {
      if (s_size >= 1) {
        k = (short)s_size - 1;
        for (i = 0; i <= k; i++) {
          y_data[i] = (short)(i + 1);
        }
      }
      nz = s_size - 1;
      indEnd = 0;
      k = 0;
      for (i = 0; i <= nz; i++) {
        if (s_data[i] != 0.0) {
          indEnd++;
          tmp_data[k] = (short)(i + 1);
          k++;
        }
      }
      trueCount = 0;
      k = 0;
      for (i = 0; i <= nz; i++) {
        if (!(s_data[i] != 0.0)) {
          trueCount++;
          b_tmp_data[k] = (short)(i + 1);
          k++;
        }
      }
      y_size[0] = 1;
      y_size[1] = indEnd;
      for (i = 0; i < indEnd; i++) {
        b_y_data[i] = y_data[tmp_data[i] - 1];
      }
      for (i = 0; i < indEnd; i++) {
        b_s_data[i] = s_data[tmp_data[i] - 1];
      }
      b_y_size[0] = 1;
      b_y_size[1] = trueCount;
      for (i = 0; i < trueCount; i++) {
        c_y_data[i] = y_data[b_tmp_data[i] - 1];
      }
      interp1(b_y_data, y_size, b_s_data, indEnd, c_y_data, b_y_size,
              d_tmp_data, tmp_size);
      k = 0;
      for (i = 0; i < s_size; i++) {
        if (!(b_data[i] != 0.0)) {
          b_data[i] = d_tmp_data[k];
          k++;
        }
      }
    }
    ctr = 0.0;
    nz = 0;
    indEnd = s_size;
    for (k = 0; k < s_size; k++) {
      if (idx_data[k]) {
        if (ctr == 0.0) {
          nz = k;
        }
        indEnd = k + 1;
        ctr++;
      }
    }
    if (1 > nz) {
      k = 0;
    } else {
      k = nz;
    }
    for (i = 0; i < k; i++) {
      b_data[i] = s_data[nz];
    }
    if (indEnd + 1 > s_size) {
      i = 0;
      nz = 0;
    } else {
      i = indEnd;
      nz = s_size;
    }
    k = nz - i;
    for (nz = 0; nz < k; nz++) {
      b_data[i + nz] = s_data[indEnd - 1];
    }
    if (0 <= s_size - 1) {
      memcpy(&s_data[0], &b_data[0], s_size * sizeof(double));
    }
  }
  nz = (short)A_size;
  *maxVals_size = (short)A_size;
  if (0 <= nz - 1) {
    memset(&maxVals_data[0], 0, nz * sizeof(boolean_T));
  }
  diff(s_data, s_size, b_data, &nz);
  for (i = 0; i < nz; i++) {
    maxVals_data[i + 1] = (b_data[i] < 0.0);
  }
  uniquePts_data[0] = true;
  for (i = 0; i <= A_size - 2; i++) {
    uniquePts_data[i + 1] = (A_data[i + 1] != A_data[i]);
  }
  for (i = 0; i < A_size; i++) {
    nanMask_data[i] = rtIsNaN(A_data[i]);
  }
  y = false;
  nz = 1;
  exitg1 = false;
  while ((!exitg1) && (nz <= A_size)) {
    if (nanMask_data[nz - 1]) {
      y = true;
      exitg1 = true;
    } else {
      nz++;
    }
  }
  if (y) {
    k = A_size - 2;
    nz = A_size - 1;
    for (i = 0; i <= k; i++) {
      nanMask_data[i] = rtIsNaN(A_data[i + 1]);
    }
    for (i = 0; i < nz; i++) {
      c_tmp_data[i] = rtIsNaN(A_data[i]);
    }
    k = A_size - 2;
    b_uniquePts_data[0] = uniquePts_data[0];
    for (i = 0; i <= k; i++) {
      b_uniquePts_data[i + 1] =
          (uniquePts_data[i + 1] && ((!nanMask_data[i]) || (!c_tmp_data[i])));
    }
    if (0 <= A_size - 1) {
      memcpy(&uniquePts_data[0], &b_uniquePts_data[0],
             A_size * sizeof(boolean_T));
    }
  }
  if (1 > s_size - 1) {
    k = 1;
  } else {
    k = s_size;
  }
  i = (2 <= s_size);
  *inflectionPts_size = k + 1;
  inflectionPts_data[0] = true;
  for (nz = 0; nz <= k - 2; nz++) {
    inflectionPts_data[nz + 1] =
        ((s_data[nz] != s_data[i + nz]) && uniquePts_data[nz + 1]);
  }
  inflectionPts_data[k] = true;
}

void b_adjustFlatRegions(const double A[3600], boolean_T maxVals[3600])
{
  double leftRange_data[3601];
  double b_y1[3599];
  double tmp2;
  double work;
  int b_tmp_data[3601];
  int tmp_data[3601];
  int b_i;
  int b_loop_ub;
  int ctr;
  int i;
  int i1;
  int k;
  int leftRange_size;
  int loop_ub;
  short ranges_data[7202];
  short rightRange_data[3602];
  short idxTemp[3600];
  boolean_T flatRegion_data[3601];
  boolean_T x_data[3601];
  boolean_T colRngTF;
  boolean_T exitg1;
  colRngTF = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3600)) {
    if (maxVals[k]) {
      colRngTF = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  ctr = 0;
  if (colRngTF) {
    ctr = 1;
  }
  i = (1 <= ctr);
  for (k = 0; k < i; k++) {
    work = A[0];
    for (ctr = 0; ctr < 3599; ctr++) {
      tmp2 = work;
      work = A[ctr + 1];
      b_y1[ctr] = work - tmp2;
    }
    memset(&idxTemp[0], 0, 3600U * sizeof(short));
    work = 1.0;
    for (ctr = 0; ctr < 3599; ctr++) {
      if (b_y1[ctr] != 0.0) {
        idxTemp[(int)work - 1] = (short)(ctr + 1);
        work++;
      }
    }
    if (1.0 > work - 1.0) {
      loop_ub = 0;
    } else {
      loop_ub = (int)(work - 1.0);
    }
    leftRange_size = loop_ub + 1;
    leftRange_data[0] = 1.0;
    for (i1 = 0; i1 < loop_ub; i1++) {
      leftRange_data[i1 + 1] = (double)idxTemp[i1] + 1.0;
    }
    if (2 > loop_ub + 1) {
      i1 = 0;
      b_i = 0;
    } else {
      i1 = 1;
      b_i = loop_ub + 1;
    }
    b_loop_ub = b_i - i1;
    ctr = b_loop_ub + 1;
    for (b_i = 0; b_i < b_loop_ub; b_i++) {
      rightRange_data[b_i] = (short)((int)leftRange_data[i1 + b_i] - 1);
    }
    rightRange_data[b_loop_ub] = 3600;
    for (i1 = 0; i1 < ctr; i1++) {
      flatRegion_data[i1] = (rightRange_data[i1] > (int)leftRange_data[i1]);
    }
    colRngTF = false;
    ctr = 1;
    exitg1 = false;
    while ((!exitg1) && (ctr <= b_loop_ub + 1)) {
      if (flatRegion_data[ctr - 1]) {
        colRngTF = true;
        exitg1 = true;
      } else {
        ctr++;
      }
    }
    if (colRngTF) {
      for (i1 = 0; i1 < leftRange_size; i1++) {
        x_data[i1] =
            (maxVals[(int)leftRange_data[i1] - 1] && flatRegion_data[i1]);
      }
      colRngTF = false;
      ctr = 1;
      exitg1 = false;
      while ((!exitg1) && (ctr <= loop_ub + 1)) {
        if (x_data[ctr - 1]) {
          colRngTF = true;
          exitg1 = true;
        } else {
          ctr++;
        }
      }
      if (colRngTF) {
        ctr = loop_ub;
        b_loop_ub = 0;
        for (b_i = 0; b_i <= loop_ub; b_i++) {
          if (maxVals[(int)leftRange_data[b_i] - 1] && flatRegion_data[b_i]) {
            b_loop_ub++;
          }
        }
        loop_ub = 0;
        for (b_i = 0; b_i <= ctr; b_i++) {
          if (maxVals[(int)leftRange_data[b_i] - 1] && flatRegion_data[b_i]) {
            tmp_data[loop_ub] = b_i + 1;
            loop_ub++;
          }
        }
        for (i1 = 0; i1 < b_loop_ub; i1++) {
          ranges_data[i1] = (short)leftRange_data[tmp_data[i1] - 1];
        }
        for (i1 = 0; i1 < b_loop_ub; i1++) {
          ranges_data[i1 + b_loop_ub] = rightRange_data[tmp_data[i1] - 1];
        }
        for (i1 = 0; i1 < b_loop_ub; i1++) {
          b_tmp_data[i1] = ranges_data[i1];
        }
        for (i1 = 0; i1 < b_loop_ub; i1++) {
          maxVals[b_tmp_data[i1] - 1] = false;
        }
        if (b_loop_ub == 0) {
          leftRange_size = 0;
        } else {
          leftRange_size = (short)b_loop_ub;
          for (ctr = 0; ctr < b_loop_ub; ctr++) {
            leftRange_data[ctr] = ranges_data[ctr];
          }
          for (ctr = 0; ctr < b_loop_ub; ctr++) {
            leftRange_data[ctr] += (double)ranges_data[b_loop_ub + ctr];
          }
        }
        for (i1 = 0; i1 < leftRange_size; i1++) {
          leftRange_data[i1] /= 2.0;
        }
        for (ctr = 0; ctr < leftRange_size; ctr++) {
          leftRange_data[ctr] = floor(leftRange_data[ctr]);
        }
        for (i1 = 0; i1 < leftRange_size; i1++) {
          b_tmp_data[i1] = (int)leftRange_data[i1];
        }
        for (i1 = 0; i1 < leftRange_size; i1++) {
          maxVals[b_tmp_data[i1] - 1] = true;
        }
      }
    }
  }
}

void b_getAllLocalMax(const double A[3600], boolean_T maxVals[3600],
                      boolean_T inflectionPts[3600])
{
  static double b[3599];
  static double b_tmp_data[3599];
  static double b_y1[3599];
  double d_tmp_data[3599];
  double e_tmp_data[3599];
  double y1_data[3599];
  double tmp2;
  double work;
  int b_tmp_size[2];
  int c_tmp_size[2];
  int tmp_size[2];
  int b_i;
  int b_trueCount;
  int i;
  int indEnd;
  int k;
  int trueCount;
  short c_tmp_data[3599];
  short tmp_data[3599];
  boolean_T nanMask[3600];
  boolean_T uniquePts[3600];
  boolean_T x[3599];
  boolean_T exitg1;
  boolean_T y;
  work = A[0];
  for (k = 0; k < 3599; k++) {
    tmp2 = work;
    work = A[k + 1];
    tmp2 = work - tmp2;
    if (tmp2 < 0.0) {
      tmp2 = -1.0;
    } else if (tmp2 > 0.0) {
      tmp2 = 1.0;
    } else if (tmp2 == 0.0) {
      tmp2 = 0.0;
    }
    b_y1[k] = tmp2;
  }
  for (i = 0; i < 3600; i++) {
    nanMask[i] = rtIsNaN(A[i]);
  }
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3600)) {
    if (nanMask[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (y) {
    for (i = 0; i < 3599; i++) {
      y = nanMask[i];
      if (y) {
        b_y1[i] = -1.0;
      }
      if ((!y) && nanMask[i + 1]) {
        b_y1[i] = 1.0;
      }
    }
  }
  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3599)) {
    if (b_y1[k] == 0.0) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!y) {
    for (i = 0; i < 3599; i++) {
      tmp2 = b_y1[i];
      b[i] = tmp2;
      x[i] = (tmp2 != 0.0);
    }
    i = x[0];
    for (k = 0; k < 3598; k++) {
      i += x[k + 1];
    }
    if (i > 1) {
      trueCount = 0;
      k = 0;
      b_trueCount = 0;
      indEnd = 0;
      for (i = 0; i < 3599; i++) {
        tmp2 = b_y1[i];
        if (tmp2 != 0.0) {
          trueCount++;
          tmp_data[k] = (short)(i + 1);
          k++;
        }
        if (!(tmp2 != 0.0)) {
          b_trueCount++;
          c_tmp_data[indEnd] = (short)(i + 1);
          indEnd++;
        }
      }
      tmp_size[0] = 1;
      tmp_size[1] = trueCount;
      for (b_i = 0; b_i < trueCount; b_i++) {
        b_tmp_data[b_i] = ((double)tmp_data[b_i] - 1.0) + 1.0;
      }
      for (b_i = 0; b_i < trueCount; b_i++) {
        y1_data[b_i] = b_y1[tmp_data[b_i] - 1];
      }
      b_tmp_size[0] = 1;
      b_tmp_size[1] = b_trueCount;
      for (b_i = 0; b_i < b_trueCount; b_i++) {
        d_tmp_data[b_i] = ((double)c_tmp_data[b_i] - 1.0) + 1.0;
      }
      interp1(b_tmp_data, tmp_size, y1_data, trueCount, d_tmp_data, b_tmp_size,
              e_tmp_data, c_tmp_size);
      k = 0;
      for (i = 0; i < 3599; i++) {
        if (!(b[i] != 0.0)) {
          b[i] = e_tmp_data[k];
          k++;
        }
      }
    }
    tmp2 = 0.0;
    i = 0;
    indEnd = 3598;
    for (k = 0; k < 3599; k++) {
      if (b_y1[k] != 0.0) {
        if (tmp2 == 0.0) {
          i = k;
        }
        indEnd = k;
        tmp2++;
      }
    }
    if (1 > i) {
      k = 0;
    } else {
      k = i;
    }
    for (b_i = 0; b_i < k; b_i++) {
      b[b_i] = b_y1[i];
    }
    if (indEnd + 2 > 3599) {
      b_i = -1;
      i = -1;
    } else {
      b_i = indEnd;
      i = 3598;
    }
    k = i - b_i;
    for (i = 0; i < k; i++) {
      b[(b_i + i) + 1] = b_y1[indEnd];
    }
    memcpy(&b_y1[0], &b[0], 3599U * sizeof(double));
  }
  memset(&maxVals[0], 0, 3600U * sizeof(boolean_T));
  work = b_y1[0];
  for (i = 0; i < 3598; i++) {
    tmp2 = work;
    work = b_y1[i + 1];
    maxVals[i + 1] = (work - tmp2 < 0.0);
  }
  uniquePts[0] = true;
  for (i = 0; i < 3599; i++) {
    uniquePts[i + 1] = (A[i + 1] != A[i]);
  }
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3600)) {
    if (nanMask[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (y) {
    nanMask[0] = uniquePts[0];
    for (i = 0; i < 3599; i++) {
      nanMask[i + 1] =
          (uniquePts[i + 1] && ((!rtIsNaN(A[i + 1])) || (!rtIsNaN(A[i]))));
    }
    memcpy(&uniquePts[0], &nanMask[0], 3600U * sizeof(boolean_T));
  }
  inflectionPts[0] = true;
  for (i = 0; i < 3598; i++) {
    inflectionPts[i + 1] = ((b_y1[i] != b_y1[i + 1]) && uniquePts[i + 1]);
  }
  inflectionPts[3599] = true;
}

void doLocalMaxSearch(double A_data[], int A_size, double minProm,
                      boolean_T maxVals_data[], int *maxVals_size,
                      double P_data[], int *P_size)
{
  static double x_data[3600];
  emxArray_int32_T_3600 b_x_data;
  double localMaxValue_tmp;
  double localMins_idx_0;
  double localMins_idx_1;
  double m;
  int iidx_data[3600];
  int b_i;
  int exitg3;
  int exitg4;
  int i;
  int idx_size_idx_1;
  int nz;
  int right;
  int trueCount;
  short b_tmp_data[3600];
  short idx_data[3600];
  short locMaxima_data[3600];
  boolean_T inflectionPts_data[3600];
  boolean_T isLocMax_data[3600];
  boolean_T tmp_data[3600];
  boolean_T calculateProminence;
  boolean_T exitg1;
  *P_size = A_size;
  if (0 <= A_size - 1) {
    memset(&P_data[0], 0, A_size * sizeof(double));
  }
  if (A_size < 3) {
    *maxVals_size = A_size;
    if (0 <= A_size - 1) {
      memset(&maxVals_data[0], 0, A_size * sizeof(boolean_T));
    }
  } else {
    for (i = 0; i < A_size; i++) {
      isLocMax_data[i] = rtIsInf(A_data[i]);
    }
    for (i = 0; i < A_size; i++) {
      tmp_data[i] = (A_data[i] > 0.0);
    }
    for (b_i = 0; b_i < A_size; b_i++) {
      if (isLocMax_data[b_i] && tmp_data[b_i]) {
        A_data[b_i] = rtNaN;
      }
    }
    getAllLocalMax(A_data, A_size, maxVals_data, maxVals_size,
                   inflectionPts_data, &nz);
    for (i = 0; i < *maxVals_size; i++) {
      maxVals_data[i] = (maxVals_data[i] || (isLocMax_data[i] && tmp_data[i]));
    }
    for (b_i = 0; b_i < A_size; b_i++) {
      if (isLocMax_data[b_i] && tmp_data[b_i]) {
        A_data[b_i] = rtInf;
      }
    }
    nz = maxVals_data[0];
    for (right = 2; right <= *maxVals_size; right++) {
      nz += maxVals_data[right - 1];
    }
    calculateProminence = (3600 < nz);
    if ((minProm > 0.0) || calculateProminence) {
      idx_size_idx_1 = (short)A_size;
      nz = (short)A_size - 1;
      for (i = 0; i <= nz; i++) {
        idx_data[i] = (short)(i + 1);
      }
      if (!rtIsNaN(A_data[0])) {
        nz = 1;
      } else {
        nz = 0;
        right = 2;
        exitg1 = false;
        while ((!exitg1) && (right <= A_size)) {
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
        for (right = i; right <= A_size; right++) {
          localMaxValue_tmp = A_data[right - 1];
          if (m > localMaxValue_tmp) {
            m = localMaxValue_tmp;
          }
        }
      }
      nz = *maxVals_size - 1;
      trueCount = 0;
      right = 0;
      for (b_i = 0; b_i <= nz; b_i++) {
        if (maxVals_data[b_i] || inflectionPts_data[b_i]) {
          trueCount++;
          iidx_data[right] = b_i + 1;
          right++;
        }
      }
      for (i = 0; i < idx_size_idx_1; i++) {
        isLocMax_data[i] = maxVals_data[idx_data[i] - 1];
      }
      for (b_i = 0; b_i < trueCount; b_i++) {
        i = idx_data[iidx_data[b_i] - 1] - 1;
        if (isLocMax_data[i]) {
          localMaxValue_tmp = A_data[i];
          if (rtIsInf(localMaxValue_tmp) || rtIsNaN(localMaxValue_tmp)) {
            P_data[i] = rtInf;
          } else if ((!calculateProminence) &&
                     (localMaxValue_tmp - m < minProm)) {
            maxVals_data[i] = false;
          } else {
            localMins_idx_0 = localMaxValue_tmp;
            localMins_idx_1 = localMaxValue_tmp;
            nz = b_i - 1;
            right = b_i + 1;
            do {
              exitg4 = 0;
              if (nz + 1 > 0) {
                idx_size_idx_1 = idx_data[iidx_data[nz] - 1] - 1;
                if (!isLocMax_data[idx_size_idx_1]) {
                  localMins_idx_0 =
                      fmin(localMins_idx_0, A_data[idx_size_idx_1]);
                  nz--;
                } else if (A_data[idx_size_idx_1] > localMaxValue_tmp) {
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
                idx_size_idx_1 = idx_data[iidx_data[right] - 1] - 1;
                if (!isLocMax_data[idx_size_idx_1]) {
                  localMins_idx_1 =
                      fmin(localMins_idx_1, A_data[idx_size_idx_1]);
                  right++;
                } else if (A_data[idx_size_idx_1] > localMaxValue_tmp) {
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
            P_data[i] = localMaxValue_tmp - localMins_idx_0;
            maxVals_data[i] = (P_data[i] >= minProm);
          }
        }
      }
    }
    nz = maxVals_data[0];
    for (right = 2; right <= *maxVals_size; right++) {
      nz += maxVals_data[right - 1];
    }
    if (3600 < nz) {
      nz = (short)A_size - 1;
      for (i = 0; i <= nz; i++) {
        idx_data[i] = (short)(i + 1);
      }
      nz = *maxVals_size - 1;
      trueCount = 0;
      right = 0;
      for (b_i = 0; b_i <= nz; b_i++) {
        if (maxVals_data[b_i]) {
          trueCount++;
          b_tmp_data[right] = (short)(b_i + 1);
          right++;
        }
      }
      for (i = 0; i < trueCount; i++) {
        locMaxima_data[i] = idx_data[b_tmp_data[i] - 1];
      }
      for (i = 0; i < trueCount; i++) {
        x_data[i] = P_data[locMaxima_data[i] - 1];
      }
      sort(x_data, &trueCount, b_x_data.data, &b_x_data.size[0]);
    }
    adjustFlatRegions(A_data, A_size, maxVals_data, maxVals_size);
  }
}

/* End of code generation (isLocalExtrema.c) */
