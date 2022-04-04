/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * interp1.c
 *
 * Code generation for function 'interp1'
 *
 */

/* Include files */
#include "interp1.h"

/* Function Definitions */
void interp1Step(const double y_data[], const double xi_data[],
                 const int xi_size[2], double yi_data[],
                 const double varargin_1_data[], const int varargin_1_size[2])
{
  double d;
  double maxx;
  double minx;
  int high_i;
  int k;
  int low_i;
  int low_ip1;
  int mid_i;
  int ub_loop;
  minx = varargin_1_data[0];
  maxx = varargin_1_data[varargin_1_size[1] - 1];
  ub_loop = xi_size[1] - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    d, high_i, low_i, low_ip1, mid_i)

  for (k = 0; k <= ub_loop; k++) {
    d = xi_data[k];
    if (d > maxx) {
      yi_data[k] = 0.0;
    } else if (d < minx) {
      yi_data[k] = y_data[0];
    } else {
      high_i = varargin_1_size[1];
      low_i = 1;
      low_ip1 = 2;
      while (high_i > low_ip1) {
        mid_i = (low_i >> 1) + (high_i >> 1);
        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }
        if (xi_data[k] >= varargin_1_data[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }
      if (xi_data[k] <= varargin_1_data[low_i - 1]) {
        low_i--;
      }
      yi_data[k] = y_data[low_i];
    }
  }
}

/* End of code generation (interp1.c) */
