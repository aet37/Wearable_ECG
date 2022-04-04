/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * diff.c
 *
 * Code generation for function 'diff'
 *
 */

/* Include files */
#include "diff.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void diff(const double x_data[], int x_size, double y_data[], int *y_size)
{
  double tmp2;
  double work_data;
  int u0;
  if (x_size == 0) {
    *y_size = 0;
  } else {
    u0 = x_size - 1;
    if (u0 > 1) {
      u0 = 1;
    }
    if (u0 < 1) {
      *y_size = 0;
    } else {
      *y_size = (short)(x_size - 1);
      if ((short)(x_size - 1) != 0) {
        work_data = x_data[0];
        for (u0 = 2; u0 <= x_size; u0++) {
          tmp2 = work_data;
          work_data = x_data[u0 - 1];
          y_data[u0 - 2] = work_data - tmp2;
        }
      }
    }
  }
}

/* End of code generation (diff.c) */
