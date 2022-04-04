/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * minOrMax.c
 *
 * Code generation for function 'minOrMax'
 *
 */

/* Include files */
#include "minOrMax.h"

/* Function Definitions */
void maximum(const double x_data[], const int x_size[2], double *ex, int *idx)
{
  double d;
  int k;
  int last;
  last = x_size[1];
  if (x_size[1] <= 2) {
    if (x_size[1] == 1) {
      *ex = x_data[0];
      *idx = 1;
    } else {
      *ex = x_data[x_size[1] - 1];
      if (x_data[0] < *ex) {
        *idx = x_size[1];
      } else {
        *ex = x_data[0];
        *idx = 1;
      }
    }
  } else {
    *ex = x_data[0];
    *idx = 1;
    for (k = 2; k <= last; k++) {
      d = x_data[k - 1];
      if (*ex < d) {
        *ex = d;
        *idx = k;
      }
    }
  }
}

void minimum(const double x_data[], const int x_size[2], double *ex, int *idx)
{
  double d;
  int k;
  int last;
  last = x_size[1];
  if (x_size[1] <= 2) {
    if (x_size[1] == 1) {
      *ex = x_data[0];
      *idx = 1;
    } else {
      *ex = x_data[x_size[1] - 1];
      if (x_data[0] > *ex) {
        *idx = x_size[1];
      } else {
        *ex = x_data[0];
        *idx = 1;
      }
    }
  } else {
    *ex = x_data[0];
    *idx = 1;
    for (k = 2; k <= last; k++) {
      d = x_data[k - 1];
      if (*ex > d) {
        *ex = d;
        *idx = k;
      }
    }
  }
}

/* End of code generation (minOrMax.c) */
