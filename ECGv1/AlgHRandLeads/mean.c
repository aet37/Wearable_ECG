/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mean.c
 *
 * Code generation for function 'mean'
 *
 */

/* Include files */
#include "mean.h"
#include "rt_nonfinite.h"

/* Function Definitions */
double mean(const double x_data[], const int x_size[2])
{
  double bsum;
  double y;
  int firstBlockLength;
  int hi;
  int ib;
  int k;
  int lastBlockLength;
  int nblocks;
  if (x_size[1] == 0) {
    y = 0.0;
  } else {
    if (x_size[1] <= 1024) {
      firstBlockLength = x_size[1];
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = x_size[1] / 1024;
      lastBlockLength = x_size[1] - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    y = x_data[0];
    for (k = 2; k <= firstBlockLength; k++) {
      y += x_data[k - 1];
    }
    for (ib = 2; ib <= nblocks; ib++) {
      firstBlockLength = (ib - 1) << 10;
      bsum = x_data[firstBlockLength];
      if (ib == nblocks) {
        hi = lastBlockLength;
      } else {
        hi = 1024;
      }
      for (k = 2; k <= hi; k++) {
        bsum += x_data[(firstBlockLength + k) - 1];
      }
      y += bsum;
    }
  }
  y /= (double)x_size[1];
  return y;
}

/* End of code generation (mean.c) */
