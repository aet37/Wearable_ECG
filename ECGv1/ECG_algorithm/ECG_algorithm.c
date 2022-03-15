/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ECG_algorithm.c
 *
 * Code generation for function 'ECG_algorithm'
 *
 */

/* Include files */
#include "ECG_algorithm.h"
#include "ECG_algorithm_data.h"
#include "ECG_algorithm_emxutil.h"
#include "ECG_algorithm_initialize.h"
#include "ECG_algorithm_types.h"
#include "islocalmax.h"
#include "minOrMax.h"
#include "polyfit.h"
#include <string.h>

/* Function Definitions */
void ECG_algorithm(const double ECG_data[3600], double *heartRate,
                   double p_index_data[], int p_index_size[2],
                   double q_index_data[], int q_index_size[2],
                   double r_index_data[], int r_index_size[2],
                   double s_index_data[], int s_index_size[2],
                   double t_index_data[], int t_index_size[2],
                   emxArray_real_T *px_values, emxArray_real_T *tx_values,
                   emxArray_real_T *y_values)
{
  static double f_y[3600];
  static double s_value_data[3600];
  static double tp_valley_index_data[3600];
  static double x[3600];
  double expl_temp[100];
  double p[10];
  double mu[2];
  double bsum;
  double d;
  double diff;
  double ex;
  double *px_values_data;
  double *tx_values_data;
  double *y_values_data;
  int f_y_size[2];
  int hi;
  int i;
  int ib;
  int j;
  int k;
  int xblockoffset;
  short ii_data[3600];
  boolean_T r_point[3600];
  boolean_T exitg1;
  if (!isInitialized_ECG_algorithm) {
    ECG_algorithm_initialize();
  }
  /* polyfitting the data */
  for (i = 0; i < 3600; i++) {
    x[i] = (double)i + 1.0;
  }
  polyfit(x, ECG_data, p, expl_temp, &bsum, &diff, mu);
  d = mu[0];
  bsum = mu[1];
  for (i = 0; i < 3600; i++) {
    x[i] = (((double)i + 1.0) - d) / bsum;
    f_y[i] = p[0];
  }
  for (k = 0; k < 9; k++) {
    for (i = 0; i < 3600; i++) {
      f_y[i] = x[i] * f_y[i] + p[k + 1];
    }
  }
  /*      plot(f_y); */
  /*      hold on; */
  /*      plot(ECG_data(i).val); */
  /*      hold on; */
  for (i = 0; i < 3600; i++) {
    f_y[i] = ECG_data[i] - f_y[i];
  }
  /*      p = polyfit(1:size(ECG_data(i).val,2),ECG_data(i).val,4); */
  /* removing noise in ECG data to better analyze */
  /*      ECG_detrend = detrend(dt_ECG,5); */
  /*  Find local maxima which corresponds to top of the QRS complex */
  ex = f_y[0];
  for (k = 0; k < 3599; k++) {
    d = f_y[k + 1];
    if (ex < d) {
      ex = d;
    }
  }
  diff = f_y[0];
  for (k = 0; k < 1023; k++) {
    diff += f_y[k + 1];
  }
  for (ib = 0; ib < 3; ib++) {
    xblockoffset = (ib + 1) << 10;
    bsum = f_y[xblockoffset];
    if (ib + 2 == 4) {
      hi = 528;
    } else {
      hi = 1024;
    }
    for (k = 2; k <= hi; k++) {
      bsum += f_y[(xblockoffset + k) - 1];
    }
    diff += bsum;
  }
  islocalmax(f_y, (ex + diff / 3600.0) / 2.0, r_point);
  xblockoffset = 0;
  hi = 0;
  exitg1 = false;
  while ((!exitg1) && (hi < 3600)) {
    if (r_point[hi]) {
      xblockoffset++;
      ii_data[xblockoffset - 1] = (short)(hi + 1);
      if (xblockoffset >= 3600) {
        exitg1 = true;
      } else {
        hi++;
      }
    } else {
      hi++;
    }
  }
  if (1 > xblockoffset) {
    xblockoffset = 0;
  }
  r_index_size[0] = 1;
  r_index_size[1] = xblockoffset;
  for (i = 0; i < xblockoffset; i++) {
    r_index_data[i] = ii_data[i];
  }
  /* setting the default q_value and q_index and s_value and s_index size */
  q_index_size[0] = 1;
  q_index_size[1] = r_index_size[1];
  xblockoffset = r_index_size[1];
  if (0 <= xblockoffset - 1) {
    memset(&q_index_data[0], 0, xblockoffset * sizeof(double));
  }
  s_index_size[0] = 1;
  s_index_size[1] = r_index_size[1];
  xblockoffset = r_index_size[1];
  if (0 <= xblockoffset - 1) {
    memset(&s_index_data[0], 0, xblockoffset * sizeof(double));
  }
  /* finding the q and s points surrounding the r indices */
  i = r_index_size[1];
  if (0 <= i - 1) {
    f_y_size[0] = 1;
  }
  for (j = 0; j < i; j++) {
    /* finding q points */
    d = r_index_data[j];
    ex = f_y[(short)((short)d + -20) - 1];
    xblockoffset = -1;
    for (k = 0; k < 20; k++) {
      bsum = f_y[(short)((k + (short)d) - 19) - 1];
      if (ex > bsum) {
        ex = bsum;
        xblockoffset = k;
      }
    }
    q_index_data[j] = (double)((xblockoffset + (short)d) - 18) - 1.0;
    /* finding s points */
    if ((short)d + 20 > 3600) {
      xblockoffset = 3580;
    } else {
      xblockoffset = (short)d;
    }
    /* use is localmin to find the lowest point in the range between 2 r */
    /* pointsx */
    /*          while true */
    /*              [s_value(1,j), s_index(1,j)] = min(ECG_detrend(r_index(j):
     * s_index_max)); */
    /*              s_index(1,j) = s_index(1,j) + r_index(j) - 1; */
    /*   */
    /*              if(ECG_detrend(s_index + 1) && ECG_detrend(s_index + 1) >
     * ECG_detrend(s_index)) */
    /*                  break; */
    /*              end */
    /*          end */
    if ((short)d > xblockoffset + 20) {
      hi = 0;
      xblockoffset = -20;
    } else {
      hi = (short)d - 1;
    }
    xblockoffset -= hi;
    f_y_size[1] = xblockoffset + 20;
    for (k = 0; k <= xblockoffset + 19; k++) {
      x[k] = f_y[hi + k];
    }
    minimum(x, f_y_size, &s_value_data[j], &xblockoffset);
    s_index_data[j] =
        ((double)xblockoffset + (double)(short)r_index_data[j]) - 1.0;
  }
  /* default wave size */
  p_index_size[0] = 1;
  p_index_size[1] = q_index_size[1];
  xblockoffset = q_index_size[1];
  if (0 <= xblockoffset - 1) {
    memset(&p_index_data[0], 0, xblockoffset * sizeof(double));
  }
  t_index_size[0] = 1;
  t_index_size[1] = q_index_size[1];
  xblockoffset = q_index_size[1];
  if (0 <= xblockoffset - 1) {
    memset(&t_index_data[0], 0, xblockoffset * sizeof(double));
  }
  ib = q_index_size[1];
  xblockoffset = q_index_size[1];
  if (0 <= xblockoffset - 1) {
    memset(&tp_valley_index_data[0], 0, xblockoffset * sizeof(double));
  }
  /* using the q and s points to find the p and t waves */
  i = q_index_size[1];
  for (j = 0; j < i; j++) {
    /* thresholding values */
    d = q_index_data[j];
    if (d - 50.0 < 1.0) {
      bsum = 1.0;
    } else {
      bsum = d - 50.0;
    }
    if (bsum > d) {
      hi = 0;
      k = 0;
    } else {
      hi = (int)bsum - 1;
      k = (int)d;
    }
    f_y_size[0] = 1;
    xblockoffset = k - hi;
    f_y_size[1] = xblockoffset;
    for (k = 0; k < xblockoffset; k++) {
      x[k] = f_y[hi + k];
    }
    maximum(x, f_y_size, &s_value_data[j], &xblockoffset);
    d = ((double)xblockoffset + bsum) - 1.0;
    p_index_data[j] = d;
    /* thresholding corne cases */
    if (d - 150.0 < 1.0) {
      bsum = 1.0;
    } else {
      bsum = d - 150.0;
    }
    if (d - 50.0 < 1.0) {
      diff = 1.0;
    } else {
      diff = d - 50.0;
    }
    /* finding t wave */
    if (bsum > diff) {
      hi = 0;
      k = 0;
    } else {
      hi = (int)bsum - 1;
      k = (int)diff;
    }
    f_y_size[0] = 1;
    xblockoffset = k - hi;
    f_y_size[1] = xblockoffset;
    for (k = 0; k < xblockoffset; k++) {
      x[k] = f_y[hi + k];
    }
    maximum(x, f_y_size, &s_value_data[j], &xblockoffset);
    d = ((double)xblockoffset + bsum) - 1.0;
    t_index_data[j] = d;
    /* finding minimum between prior t and next p wave to show the zone */
    /* on the plot */
    bsum = p_index_data[j];
    if (d > bsum) {
      hi = 0;
      k = 0;
    } else {
      hi = (int)d - 1;
      k = (int)bsum;
    }
    f_y_size[0] = 1;
    xblockoffset = k - hi;
    f_y_size[1] = xblockoffset;
    for (k = 0; k < xblockoffset; k++) {
      x[k] = f_y[hi + k];
    }
    minimum(x, f_y_size, &s_value_data[j], &xblockoffset);
    tp_valley_index_data[j] = (double)xblockoffset + t_index_data[j];
  }
  /* multiply heart rate by 6 to find the rate per 60 seconds */
  /* plotting the features and displaying heart rate */
  i = px_values->size[0] * px_values->size[1];
  px_values->size[0] = 4;
  px_values->size[1] = ib;
  emxEnsureCapacity_real_T(px_values, i);
  px_values_data = px_values->data;
  xblockoffset = ib << 2;
  for (i = 0; i < xblockoffset; i++) {
    px_values_data[i] = 0.0;
  }
  i = tx_values->size[0] * tx_values->size[1];
  tx_values->size[0] = 4;
  tx_values->size[1] = ib;
  emxEnsureCapacity_real_T(tx_values, i);
  tx_values_data = tx_values->data;
  for (i = 0; i < xblockoffset; i++) {
    tx_values_data[i] = 0.0;
  }
  i = y_values->size[0] * y_values->size[1];
  y_values->size[0] = 4;
  y_values->size[1] = ib;
  emxEnsureCapacity_real_T(y_values, i);
  y_values_data = y_values->data;
  for (i = 0; i < xblockoffset; i++) {
    y_values_data[i] = 0.0;
  }
  i = r_index_size[1];
  for (j = 0; j < i; j++) {
    d = tp_valley_index_data[j];
    diff = p_index_data[j] - d;
    if (j + 1 == 1) {
      px_values_data[0] = tp_valley_index_data[0];
      px_values_data[1] = q_index_data[0] - 5.0;
      px_values_data[2] = q_index_data[0] - 5.0;
      px_values_data[3] = tp_valley_index_data[0];
      ex = t_index_data[0] - diff / 2.0;
      tx_values_data[0] = ex;
      bsum = t_index_data[0] + diff / 2.0;
      tx_values_data[1] = bsum;
      tx_values_data[2] = bsum;
      tx_values_data[3] = ex;
    } else if (j + 1 == r_index_size[1]) {
      px_values_data[4 * j] = d;
      hi = 4 * j + 1;
      px_values_data[hi] = q_index_data[j] - 5.0;
      k = 4 * j + 2;
      px_values_data[k] = q_index_data[j] - 5.0;
      xblockoffset = 4 * j + 3;
      px_values_data[xblockoffset] = d;
      /*              tx_values(1:4,j) = [s_index(j-1)+20 tp_valley_index(j)
       * tp_valley_index(j) s_index(j-1)+20]; */
      ex = t_index_data[j] - diff / 2.0;
      tx_values_data[4 * j] = ex;
      bsum = t_index_data[j] + diff / 2.0;
      tx_values_data[hi] = bsum;
      tx_values_data[k] = bsum;
      tx_values_data[xblockoffset] = ex;
    } else {
      px_values_data[4 * j] = d;
      hi = 4 * j + 1;
      px_values_data[hi] = q_index_data[j] - 5.0;
      k = 4 * j + 2;
      px_values_data[k] = q_index_data[j] - 5.0;
      xblockoffset = 4 * j + 3;
      px_values_data[xblockoffset] = d;
      /*              tx_values(1:4,j) = [s_index(j-1)+20 tp_valley_index(j)
       * tp_valley_index(j) s_index(j-1)+20]; */
      ex = t_index_data[j] - diff / 2.0;
      tx_values_data[4 * j] = ex;
      bsum = t_index_data[j] + diff / 2.0;
      tx_values_data[hi] = bsum;
      tx_values_data[k] = bsum;
      tx_values_data[xblockoffset] = ex;
    }
    ex = f_y[0];
    diff = f_y[0];
    for (k = 0; k < 3599; k++) {
      d = f_y[k + 1];
      if (ex > d) {
        ex = d;
      }
      if (diff < d) {
        diff = d;
      }
    }
    y_values_data[4 * j] = ex;
    y_values_data[4 * j + 2] = diff;
    y_values_data[4 * j + 1] = ex;
    y_values_data[4 * j + 3] = diff;
  }
  *heartRate = (double)r_index_size[1] * 6.0;
}

/* End of code generation (ECG_algorithm.c) */
