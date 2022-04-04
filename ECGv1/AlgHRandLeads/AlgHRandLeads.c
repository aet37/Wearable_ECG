/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * AlgHRandLeads.c
 *
 * Code generation for function 'AlgHRandLeads'
 *
 */

/* Include files */
#include "AlgHRandLeads.h"
#include "AlgHRandLeads_data.h"
#include "AlgHRandLeads_initialize.h"
#include "islocalmax.h"
#include "mean.h"
#include "minOrMax.h"
#include "polyfit.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void AlgHRandLeads(const double ECG_data[3600], double *heartRate,
                   boolean_T *leadsFlipped)
{
  static double f_y[3600];
  static double highest_value_data[3600];
  static double modified_detrend[3600];
  double expl_temp[100];
  double p[10];
  double mu[2];
  double b_expl_temp;
  double bsum;
  int f_y_size[2];
  int highest_value_size[2];
  int hi;
  int idx;
  int k;
  int trueCount;
  int xblockoffset;
  short ii_data[3600];
  boolean_T is_highest[3600];
  boolean_T exitg1;
  if (!isInitialized_AlgHRandLeads) {
    AlgHRandLeads_initialize();
  }
  /* polyfitting the data */
  for (idx = 0; idx < 3600; idx++) {
    modified_detrend[idx] = (double)idx + 1.0;
  }
  polyfit(modified_detrend, ECG_data, p, expl_temp, &bsum, &b_expl_temp, mu);
  bsum = mu[0];
  b_expl_temp = mu[1];
  for (idx = 0; idx < 3600; idx++) {
    modified_detrend[idx] = (((double)idx + 1.0) - bsum) / b_expl_temp;
    f_y[idx] = p[0];
  }
  for (k = 0; k < 9; k++) {
    for (idx = 0; idx < 3600; idx++) {
      f_y[idx] = modified_detrend[idx] * f_y[idx] + p[k + 1];
    }
  }
  for (idx = 0; idx < 3600; idx++) {
    f_y[idx] = ECG_data[idx] - f_y[idx];
  }
  /*  Find local maxima which corresponds to top of the QRS complex */
  b_expl_temp = f_y[0];
  for (k = 0; k < 1023; k++) {
    b_expl_temp += f_y[k + 1];
  }
  for (idx = 0; idx < 3; idx++) {
    xblockoffset = (idx + 1) << 10;
    bsum = f_y[xblockoffset];
    if (idx + 2 == 4) {
      hi = 528;
    } else {
      hi = 1024;
    }
    for (k = 2; k <= hi; k++) {
      bsum += f_y[(xblockoffset + k) - 1];
    }
    b_expl_temp += bsum;
  }
  islocalmax(f_y, (maximum(f_y) + b_expl_temp / 3600.0) / 2.0, is_highest);
  trueCount = 0;
  highest_value_size[0] = 1;
  idx = 0;
  /*  Find local minima which corresponds to top of the QRS complex if */
  /*  flipped */
  for (xblockoffset = 0; xblockoffset < 3600; xblockoffset++) {
    if (is_highest[xblockoffset]) {
      trueCount++;
      highest_value_data[idx] = f_y[xblockoffset];
      idx++;
    }
    modified_detrend[xblockoffset] = -f_y[xblockoffset];
  }
  highest_value_size[1] = trueCount;
  b_expl_temp = modified_detrend[0];
  for (k = 0; k < 1023; k++) {
    b_expl_temp += modified_detrend[k + 1];
  }
  for (idx = 0; idx < 3; idx++) {
    xblockoffset = (idx + 1) << 10;
    bsum = modified_detrend[xblockoffset];
    if (idx + 2 == 4) {
      hi = 528;
    } else {
      hi = 1024;
    }
    for (k = 2; k <= hi; k++) {
      bsum += modified_detrend[(xblockoffset + k) - 1];
    }
    b_expl_temp += bsum;
  }
  islocalmax(modified_detrend,
             (maximum(modified_detrend) + b_expl_temp / 3600.0) / 2.0,
             is_highest);
  hi = 0;
  idx = 0;
  for (xblockoffset = 0; xblockoffset < 3600; xblockoffset++) {
    if (is_highest[xblockoffset]) {
      hi++;
      ii_data[idx] = (short)(xblockoffset + 1);
      idx++;
    }
  }
  f_y_size[0] = 1;
  f_y_size[1] = hi;
  for (idx = 0; idx < hi; idx++) {
    modified_detrend[idx] = f_y[ii_data[idx] - 1];
  }
  if (mean(modified_detrend, f_y_size) >
      mean(highest_value_data, highest_value_size)) {
    *leadsFlipped = true;
    *heartRate = 0.0;
  } else {
    *leadsFlipped = false;
    idx = 0;
    xblockoffset = 0;
    exitg1 = false;
    while ((!exitg1) && (xblockoffset <= trueCount - 1)) {
      if (highest_value_data[xblockoffset] != 0.0) {
        idx++;
        if (idx >= trueCount) {
          exitg1 = true;
        } else {
          xblockoffset++;
        }
      } else {
        xblockoffset++;
      }
    }
    if (trueCount == 1) {
      if (idx == 0) {
        trueCount = 0;
      }
    } else if (1 > idx) {
      trueCount = 0;
    } else {
      trueCount = idx;
    }
    *heartRate = (double)trueCount * 6.0;
  }
}

/* End of code generation (AlgHRandLeads.c) */
