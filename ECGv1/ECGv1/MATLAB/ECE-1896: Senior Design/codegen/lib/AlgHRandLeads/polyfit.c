/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * polyfit.c
 *
 * Code generation for function 'polyfit'
 *
 */

/* Include files */
#include "polyfit.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void polyfit(double x[3600], const double y[3600], double p[10],
             double S_R[100], double *S_df, double *S_normr, double mu[2])
{
  static double A[36000];
  static double V[36000];
  double absdiff[3600];
  double tau[10];
  double b_y;
  double bsum;
  double d;
  double t;
  double xbar;
  int jpvt[10];
  int assumedRank;
  int b_i;
  int hi;
  int i;
  int ib;
  int k;
  int xblockoffset;
  xbar = x[0];
  for (k = 0; k < 1023; k++) {
    xbar += x[k + 1];
  }
  for (ib = 0; ib < 3; ib++) {
    xblockoffset = (ib + 1) << 10;
    bsum = x[xblockoffset];
    if (ib + 2 == 4) {
      hi = 528;
    } else {
      hi = 1024;
    }
    for (k = 2; k <= hi; k++) {
      bsum += x[(xblockoffset + k) - 1];
    }
    xbar += bsum;
  }
  xbar /= 3600.0;
  for (k = 0; k < 3600; k++) {
    absdiff[k] = fabs(x[k] - xbar);
  }
  b_y = x[0];
  for (k = 0; k < 1023; k++) {
    b_y += x[k + 1];
  }
  for (ib = 0; ib < 3; ib++) {
    xblockoffset = (ib + 1) << 10;
    bsum = x[xblockoffset];
    if (ib + 2 == 4) {
      hi = 528;
    } else {
      hi = 1024;
    }
    for (k = 2; k <= hi; k++) {
      bsum += x[(xblockoffset + k) - 1];
    }
    b_y += bsum;
  }
  xbar = 0.0;
  bsum = 3.3121686421112381E-170;
  for (k = 0; k < 3600; k++) {
    d = absdiff[k];
    if (d > bsum) {
      t = bsum / d;
      xbar = xbar * t * t + 1.0;
      bsum = d;
    } else {
      t = d / bsum;
      xbar += t * t;
    }
  }
  xbar = bsum * sqrt(xbar);
  mu[0] = b_y / 3600.0;
  mu[1] = xbar / 59.991666087882571;
  d = mu[0];
  xbar = mu[1];
  for (k = 0; k < 3600; k++) {
    bsum = (x[k] - d) / xbar;
    x[k] = bsum;
    V[k + 32400] = 1.0;
    V[k + 28800] = bsum;
  }
  for (hi = 0; hi < 8; hi++) {
    for (k = 0; k < 3600; k++) {
      V[k + 3600 * (7 - hi)] = x[k] * V[k + 3600 * (8 - hi)];
    }
  }
  memcpy(&absdiff[0], &y[0], 3600U * sizeof(double));
  memcpy(&A[0], &V[0], 36000U * sizeof(double));
  xgeqp3(A, tau, jpvt);
  assumedRank = 0;
  for (k = 0; k < 10; k++) {
    if (A[k + 3600 * k] != 0.0) {
      assumedRank++;
    }
    p[k] = 0.0;
    if (tau[k] != 0.0) {
      xbar = absdiff[k];
      b_i = k + 2;
      for (i = b_i; i < 3601; i++) {
        xbar += A[(i + 3600 * k) - 1] * absdiff[i - 1];
      }
      xbar *= tau[k];
      if (xbar != 0.0) {
        absdiff[k] -= xbar;
        for (i = b_i; i < 3601; i++) {
          absdiff[i - 1] -= A[(i + 3600 * k) - 1] * xbar;
        }
      }
    }
  }
  for (i = 0; i < assumedRank; i++) {
    p[jpvt[i] - 1] = absdiff[i];
  }
  for (hi = assumedRank; hi >= 1; hi--) {
    ib = jpvt[hi - 1] - 1;
    xblockoffset = 3600 * (hi - 1);
    p[ib] /= A[(hi + xblockoffset) - 1];
    for (i = 0; i <= hi - 2; i++) {
      b_i = jpvt[i];
      p[b_i - 1] -= p[ib] * A[i + xblockoffset];
    }
  }
  for (hi = 0; hi < 10; hi++) {
    for (i = 0; i <= hi; i++) {
      S_R[i + 10 * hi] = A[i + 3600 * hi];
    }
    b_i = hi + 2;
    if (b_i <= 10) {
      memset(&S_R[(hi * 10 + b_i) + -1], 0, (-b_i + 11) * sizeof(double));
    }
  }
  *S_df = 3590.0;
  b_y = 0.0;
  bsum = 3.3121686421112381E-170;
  for (k = 0; k < 3600; k++) {
    d = 0.0;
    for (b_i = 0; b_i < 10; b_i++) {
      d += V[k + 3600 * b_i] * p[b_i];
    }
    xbar = fabs(y[k] - d);
    if (xbar > bsum) {
      t = bsum / xbar;
      b_y = b_y * t * t + 1.0;
      bsum = xbar;
    } else {
      t = xbar / bsum;
      b_y += t * t;
    }
  }
  *S_normr = bsum * sqrt(b_y);
}

/* End of code generation (polyfit.c) */
