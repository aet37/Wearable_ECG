/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sort.c
 *
 * Code generation for function 'sort'
 *
 */

/* Include files */
#include "sort.h"
#include "sortIdx.h"
#include <string.h>

/* Function Definitions */
void sort(double x_data[], const int *x_size, int idx_data[], int *idx_size)
{
  double xwork_data[3600];
  double xwork[256];
  double x4[4];
  double d;
  double d1;
  int iwork_data[3600];
  int b;
  int bLen;
  int bLen2;
  int b_b;
  int exitg1;
  int i1;
  int i3;
  int i4;
  int ib;
  int k;
  int n;
  int nBlocks;
  int nPairs;
  int offset;
  short iwork[256];
  short idx4[4];
  signed char perm[4];
  ib = (short)*x_size;
  *idx_size = (short)*x_size;
  if (0 <= ib - 1) {
    memset(&idx_data[0], 0, ib * sizeof(int));
  }
  if (*x_size != 0) {
    n = *x_size;
    x4[0] = 0.0;
    idx4[0] = 0;
    x4[1] = 0.0;
    idx4[1] = 0;
    x4[2] = 0.0;
    idx4[2] = 0;
    x4[3] = 0.0;
    idx4[3] = 0;
    if (0 <= ib - 1) {
      memset(&iwork_data[0], 0, ib * sizeof(int));
    }
    ib = *x_size;
    if (0 <= ib - 1) {
      memset(&xwork_data[0], 0, ib * sizeof(double));
    }
    ib = 0;
    for (k = 0; k < n; k++) {
      ib++;
      idx4[ib - 1] = (short)(k + 1);
      x4[ib - 1] = x_data[k];
      if (ib == 4) {
        if (x4[0] >= x4[1]) {
          i1 = 1;
          ib = 2;
        } else {
          i1 = 2;
          ib = 1;
        }
        if (x4[2] >= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }
        d = x4[i1 - 1];
        d1 = x4[i3 - 1];
        if (d >= d1) {
          d = x4[ib - 1];
          if (d >= d1) {
            perm[0] = (signed char)i1;
            perm[1] = (signed char)ib;
            perm[2] = (signed char)i3;
            perm[3] = (signed char)i4;
          } else if (d >= x4[i4 - 1]) {
            perm[0] = (signed char)i1;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)ib;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)i1;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)ib;
          }
        } else {
          d1 = x4[i4 - 1];
          if (d >= d1) {
            if (x4[ib - 1] >= d1) {
              perm[0] = (signed char)i3;
              perm[1] = (signed char)i1;
              perm[2] = (signed char)ib;
              perm[3] = (signed char)i4;
            } else {
              perm[0] = (signed char)i3;
              perm[1] = (signed char)i1;
              perm[2] = (signed char)i4;
              perm[3] = (signed char)ib;
            }
          } else {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)i4;
            perm[2] = (signed char)i1;
            perm[3] = (signed char)ib;
          }
        }
        idx_data[k - 3] = idx4[perm[0] - 1];
        idx_data[k - 2] = idx4[perm[1] - 1];
        idx_data[k - 1] = idx4[perm[2] - 1];
        idx_data[k] = idx4[perm[3] - 1];
        x_data[k - 3] = x4[perm[0] - 1];
        x_data[k - 2] = x4[perm[1] - 1];
        x_data[k - 1] = x4[perm[2] - 1];
        x_data[k] = x4[perm[3] - 1];
        ib = 0;
      }
    }
    if (ib > 0) {
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (ib == 1) {
        perm[0] = 1;
      } else if (ib == 2) {
        if (x4[0] >= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] >= x4[1]) {
        if (x4[1] >= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] >= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] >= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] >= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }
      for (k = 0; k < ib; k++) {
        i3 = perm[k] - 1;
        i1 = (n - ib) + k;
        idx_data[i1] = idx4[i3];
        x_data[i1] = x4[i3];
      }
    }
    ib = 2;
    if (n > 1) {
      if (n >= 256) {
        nBlocks = n >> 8;
        for (b = 0; b < nBlocks; b++) {
          offset = (b << 8) - 1;
          for (b_b = 0; b_b < 6; b_b++) {
            bLen = 1 << (b_b + 2);
            bLen2 = bLen << 1;
            nPairs = 256 >> (b_b + 3);
            for (k = 0; k < nPairs; k++) {
              i3 = (offset + k * bLen2) + 1;
              for (i1 = 0; i1 < bLen2; i1++) {
                ib = i3 + i1;
                iwork[i1] = (short)idx_data[ib];
                xwork[i1] = x_data[ib];
              }
              i4 = 0;
              i1 = bLen;
              ib = i3 - 1;
              do {
                exitg1 = 0;
                ib++;
                if (xwork[i4] >= xwork[i1]) {
                  idx_data[ib] = iwork[i4];
                  x_data[ib] = xwork[i4];
                  if (i4 + 1 < bLen) {
                    i4++;
                  } else {
                    exitg1 = 1;
                  }
                } else {
                  idx_data[ib] = iwork[i1];
                  x_data[ib] = xwork[i1];
                  if (i1 + 1 < bLen2) {
                    i1++;
                  } else {
                    ib -= i4;
                    for (i1 = i4 + 1; i1 <= bLen; i1++) {
                      i3 = ib + i1;
                      idx_data[i3] = iwork[i1 - 1];
                      x_data[i3] = xwork[i1 - 1];
                    }
                    exitg1 = 1;
                  }
                }
              } while (exitg1 == 0);
            }
          }
        }
        ib = nBlocks << 8;
        i1 = n - ib;
        if (i1 > 0) {
          merge_block(idx_data, x_data, ib, i1, 2, iwork_data, xwork_data);
        }
        ib = 8;
      }
      merge_block(idx_data, x_data, 0, n, ib, iwork_data, xwork_data);
    }
  }
}

/* End of code generation (sort.c) */
