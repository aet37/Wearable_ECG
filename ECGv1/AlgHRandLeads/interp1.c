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
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Declarations */
static void interp1Step(const double y_data[], const double xi_data[],
                        const int xi_size[2], double yi_data[],
                        const double varargin_1_data[],
                        const int varargin_1_size[2]);

/* Function Definitions */
static void interp1Step(const double y_data[], const double xi_data[],
                        const int xi_size[2], double yi_data[],
                        const double varargin_1_data[],
                        const int varargin_1_size[2])
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
    if (rtIsNaN(d)) {
      yi_data[k] = rtNaN;
    } else if (d > maxx) {
      yi_data[k] = rtNaN;
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
      if (!(xi_data[k] > varargin_1_data[low_i - 1])) {
        low_i--;
      }
      yi_data[k] = y_data[low_i];
    }
  }
}

void interp1(const double varargin_1_data[], const int varargin_1_size[2],
             const double varargin_2_data[], int varargin_2_size,
             const double varargin_3_data[], const int varargin_3_size[2],
             double Vq_data[], int Vq_size[2])
{
  static double y_data[3599];
  double x_data[3599];
  double xtmp;
  int x_size[2];
  int exitg1;
  int k;
  int nd2;
  int nx;
  int x_tmp;
  boolean_T b;
  if (0 <= varargin_2_size - 1) {
    memcpy(&y_data[0], &varargin_2_data[0], varargin_2_size * sizeof(double));
  }
  x_size[0] = 1;
  x_size[1] = varargin_1_size[1];
  nd2 = varargin_1_size[1];
  if (0 <= nd2 - 1) {
    memcpy(&x_data[0], &varargin_1_data[0], nd2 * sizeof(double));
  }
  nx = varargin_1_size[1] - 1;
  Vq_size[0] = 1;
  Vq_size[1] = (short)varargin_3_size[1];
  nd2 = (short)varargin_3_size[1];
  if (0 <= nd2 - 1) {
    memset(&Vq_data[0], 0, nd2 * sizeof(double));
  }
  b = (varargin_3_size[1] == 0);
  if (!b) {
    k = 0;
    do {
      exitg1 = 0;
      if (k <= nx) {
        if (rtIsNaN(varargin_1_data[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1_data[1] < varargin_1_data[0]) {
          nd2 = (nx + 1) >> 1;
          for (k = 0; k < nd2; k++) {
            xtmp = x_data[k];
            x_tmp = nx - k;
            x_data[k] = x_data[x_tmp];
            x_data[x_tmp] = xtmp;
          }
          if ((varargin_2_size != 0) && (varargin_2_size > 1)) {
            nd2 = varargin_2_size >> 1;
            for (k = 0; k < nd2; k++) {
              xtmp = y_data[k];
              x_tmp = (varargin_2_size - k) - 1;
              y_data[k] = y_data[x_tmp];
              y_data[x_tmp] = xtmp;
            }
          }
        }
        interp1Step(y_data, varargin_3_data, varargin_3_size, Vq_data, x_data,
                    x_size);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

/* End of code generation (interp1.c) */
