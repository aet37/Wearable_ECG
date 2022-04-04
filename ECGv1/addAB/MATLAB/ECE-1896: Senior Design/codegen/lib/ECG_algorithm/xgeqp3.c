/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgeqp3.c
 *
 * Code generation for function 'xgeqp3'
 *
 */

/* Include files */
#include "xgeqp3.h"
#include "xnrm2.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static int div_nde_s32_floor(int numerator);

static double rt_hypotd(double u0, double u1);

/* Function Definitions */
static int div_nde_s32_floor(int numerator)
{
  int b_numerator;
  if ((numerator < 0) && (numerator % 3600 != 0)) {
    b_numerator = -1;
  } else {
    b_numerator = 0;
  }
  return numerator / 3600 + b_numerator;
}

static double rt_hypotd(double u0, double u1)
{
  double a;
  double b;
  double y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else {
    y = a * 1.4142135623730951;
  }
  return y;
}

void xgeqp3(double A[36000], double tau[10], int jpvt[10])
{
  double vn1[10];
  double vn2[10];
  double work[10];
  double absxk;
  double scale;
  double smax;
  double t;
  int b_i;
  int exitg1;
  int i;
  int ii;
  int ip1;
  int ix0;
  int iy;
  int k;
  int kend;
  int lastc;
  int lastv;
  int pvt;
  boolean_T exitg2;
  for (k = 0; k < 10; k++) {
    jpvt[k] = k + 1;
    tau[k] = 0.0;
    work[k] = 0.0;
    ix0 = k * 3600;
    smax = 0.0;
    scale = 3.3121686421112381E-170;
    kend = ix0 + 3600;
    for (iy = ix0 + 1; iy <= kend; iy++) {
      absxk = fabs(A[iy - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        smax = smax * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        smax += t * t;
      }
    }
    absxk = scale * sqrt(smax);
    vn1[k] = absxk;
    vn2[k] = absxk;
  }
  for (i = 0; i < 10; i++) {
    ip1 = i + 2;
    ii = i * 3600 + i;
    kend = 10 - i;
    iy = 0;
    if (10 - i > 1) {
      smax = fabs(vn1[i]);
      for (k = 2; k <= kend; k++) {
        scale = fabs(vn1[(i + k) - 1]);
        if (scale > smax) {
          iy = k - 1;
          smax = scale;
        }
      }
    }
    pvt = i + iy;
    if (pvt != i) {
      kend = pvt * 3600;
      iy = i * 3600;
      for (k = 0; k < 3600; k++) {
        ix0 = kend + k;
        smax = A[ix0];
        b_i = iy + k;
        A[ix0] = A[b_i];
        A[b_i] = smax;
      }
      kend = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = kend;
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }
    t = A[ii];
    ix0 = ii + 2;
    tau[i] = 0.0;
    smax = xnrm2(3599 - i, A, ii + 2);
    if (smax != 0.0) {
      scale = rt_hypotd(A[ii], smax);
      if (A[ii] >= 0.0) {
        scale = -scale;
      }
      if (fabs(scale) < 1.0020841800044864E-292) {
        kend = -1;
        b_i = (ii - i) + 3600;
        do {
          kend++;
          for (k = ix0; k <= b_i; k++) {
            A[k - 1] *= 9.9792015476736E+291;
          }
          scale *= 9.9792015476736E+291;
          t *= 9.9792015476736E+291;
        } while (!(fabs(scale) >= 1.0020841800044864E-292));
        scale = rt_hypotd(t, xnrm2(3599 - i, A, ii + 2));
        if (t >= 0.0) {
          scale = -scale;
        }
        tau[i] = (scale - t) / scale;
        smax = 1.0 / (t - scale);
        for (k = ix0; k <= b_i; k++) {
          A[k - 1] *= smax;
        }
        for (k = 0; k <= kend; k++) {
          scale *= 1.0020841800044864E-292;
        }
        t = scale;
      } else {
        tau[i] = (scale - A[ii]) / scale;
        smax = 1.0 / (A[ii] - scale);
        b_i = (ii - i) + 3600;
        for (k = ix0; k <= b_i; k++) {
          A[k - 1] *= smax;
        }
        t = scale;
      }
    }
    A[ii] = t;
    if (i + 1 < 10) {
      t = A[ii];
      A[ii] = 1.0;
      pvt = ii + 3601;
      if (tau[i] != 0.0) {
        lastv = 3600 - i;
        kend = (ii - i) + 3599;
        while ((lastv > 0) && (A[kend] == 0.0)) {
          lastv--;
          kend--;
        }
        lastc = 8 - i;
        exitg2 = false;
        while ((!exitg2) && (lastc + 1 > 0)) {
          kend = (ii + lastc * 3600) + 3600;
          ix0 = kend;
          do {
            exitg1 = 0;
            if (ix0 + 1 <= kend + lastv) {
              if (A[ix0] != 0.0) {
                exitg1 = 1;
              } else {
                ix0++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = -1;
      }
      if (lastv > 0) {
        if (lastc + 1 != 0) {
          if (0 <= lastc) {
            memset(&work[0], 0, (lastc + 1) * sizeof(double));
          }
          b_i = (ii + 3600 * lastc) + 3601;
          for (iy = pvt; iy <= b_i; iy += 3600) {
            smax = 0.0;
            k = (iy + lastv) - 1;
            for (ix0 = iy; ix0 <= k; ix0++) {
              smax += A[ix0 - 1] * A[(ii + ix0) - iy];
            }
            kend = div_nde_s32_floor((iy - ii) - 3601);
            work[kend] += smax;
          }
        }
        if (-tau[i] != 0.0) {
          kend = ii;
          for (iy = 0; iy <= lastc; iy++) {
            absxk = work[iy];
            if (absxk != 0.0) {
              smax = absxk * -tau[i];
              b_i = kend + 3601;
              k = lastv + kend;
              for (ix0 = b_i; ix0 <= k + 3600; ix0++) {
                A[ix0 - 1] += A[((ii + ix0) - kend) - 3601] * smax;
              }
            }
            kend += 3600;
          }
        }
      }
      A[ii] = t;
    }
    for (iy = ip1; iy < 11; iy++) {
      kend = i + (iy - 1) * 3600;
      absxk = vn1[iy - 1];
      if (absxk != 0.0) {
        smax = fabs(A[kend]) / absxk;
        smax = 1.0 - smax * smax;
        if (smax < 0.0) {
          smax = 0.0;
        }
        scale = absxk / vn2[iy - 1];
        scale = smax * (scale * scale);
        if (scale <= 1.4901161193847656E-8) {
          absxk = xnrm2(3599 - i, A, kend + 2);
          vn1[iy - 1] = absxk;
          vn2[iy - 1] = absxk;
        } else {
          vn1[iy - 1] = absxk * sqrt(smax);
        }
      }
    }
  }
}

/* End of code generation (xgeqp3.c) */
