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
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "rt_nonfinite.h"
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
  int bLen2;
  int b_b;
  int exitg1;
  int i2;
  int i3;
  int i4;
  int ib;
  int idx_tmp;
  int k;
  int n;
  int nBlocks;
  int nNaNs;
  int nNonNaN;
  int nPairs;
  int quartetOffset;
  short iwork[256];
  short idx4[4];
  signed char perm[4];
  quartetOffset = (short)*x_size;
  *idx_size = (short)*x_size;
  if (0 <= quartetOffset - 1) {
    memset(&idx_data[0], 0, quartetOffset * sizeof(int));
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
    if (0 <= quartetOffset - 1) {
      memset(&iwork_data[0], 0, quartetOffset * sizeof(int));
    }
    quartetOffset = *x_size;
    if (0 <= quartetOffset - 1) {
      memset(&xwork_data[0], 0, quartetOffset * sizeof(double));
    }
    nNaNs = 0;
    ib = -1;
    for (k = 0; k < n; k++) {
      if (rtIsNaN(x_data[k])) {
        idx_tmp = (n - nNaNs) - 1;
        idx_data[idx_tmp] = k + 1;
        xwork_data[idx_tmp] = x_data[k];
        nNaNs++;
      } else {
        ib++;
        idx4[ib] = (short)(k + 1);
        x4[ib] = x_data[k];
        if (ib + 1 == 4) {
          quartetOffset = k - nNaNs;
          if (x4[0] >= x4[1]) {
            ib = 1;
            i2 = 2;
          } else {
            ib = 2;
            i2 = 1;
          }
          if (x4[2] >= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }
          d = x4[ib - 1];
          d1 = x4[i3 - 1];
          if (d >= d1) {
            d = x4[i2 - 1];
            if (d >= d1) {
              perm[0] = (signed char)ib;
              perm[1] = (signed char)i2;
              perm[2] = (signed char)i3;
              perm[3] = (signed char)i4;
            } else if (d >= x4[i4 - 1]) {
              perm[0] = (signed char)ib;
              perm[1] = (signed char)i3;
              perm[2] = (signed char)i2;
              perm[3] = (signed char)i4;
            } else {
              perm[0] = (signed char)ib;
              perm[1] = (signed char)i3;
              perm[2] = (signed char)i4;
              perm[3] = (signed char)i2;
            }
          } else {
            d1 = x4[i4 - 1];
            if (d >= d1) {
              if (x4[i2 - 1] >= d1) {
                perm[0] = (signed char)i3;
                perm[1] = (signed char)ib;
                perm[2] = (signed char)i2;
                perm[3] = (signed char)i4;
              } else {
                perm[0] = (signed char)i3;
                perm[1] = (signed char)ib;
                perm[2] = (signed char)i4;
                perm[3] = (signed char)i2;
              }
            } else {
              perm[0] = (signed char)i3;
              perm[1] = (signed char)i4;
              perm[2] = (signed char)ib;
              perm[3] = (signed char)i2;
            }
          }
          idx_data[quartetOffset - 3] = idx4[perm[0] - 1];
          idx_data[quartetOffset - 2] = idx4[perm[1] - 1];
          idx_data[quartetOffset - 1] = idx4[perm[2] - 1];
          idx_data[quartetOffset] = idx4[perm[3] - 1];
          x_data[quartetOffset - 3] = x4[perm[0] - 1];
          x_data[quartetOffset - 2] = x4[perm[1] - 1];
          x_data[quartetOffset - 1] = x4[perm[2] - 1];
          x_data[quartetOffset] = x4[perm[3] - 1];
          ib = -1;
        }
      }
    }
    i3 = (n - nNaNs) - 1;
    if (ib + 1 > 0) {
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (ib + 1 == 1) {
        perm[0] = 1;
      } else if (ib + 1 == 2) {
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
      for (k = 0; k <= ib; k++) {
        idx_tmp = perm[k] - 1;
        quartetOffset = (i3 - ib) + k;
        idx_data[quartetOffset] = idx4[idx_tmp];
        x_data[quartetOffset] = x4[idx_tmp];
      }
    }
    ib = (nNaNs >> 1) + 1;
    for (k = 0; k <= ib - 2; k++) {
      quartetOffset = (i3 + k) + 1;
      i2 = idx_data[quartetOffset];
      idx_tmp = (n - k) - 1;
      idx_data[quartetOffset] = idx_data[idx_tmp];
      idx_data[idx_tmp] = i2;
      x_data[quartetOffset] = xwork_data[idx_tmp];
      x_data[idx_tmp] = xwork_data[quartetOffset];
    }
    if ((nNaNs & 1) != 0) {
      quartetOffset = i3 + ib;
      x_data[quartetOffset] = xwork_data[quartetOffset];
    }
    nNonNaN = n - nNaNs;
    quartetOffset = 2;
    if (nNonNaN > 1) {
      if (n >= 256) {
        nBlocks = nNonNaN >> 8;
        if (nBlocks > 0) {
          for (b = 0; b < nBlocks; b++) {
            i4 = (b << 8) - 1;
            for (b_b = 0; b_b < 6; b_b++) {
              n = 1 << (b_b + 2);
              bLen2 = n << 1;
              nPairs = 256 >> (b_b + 3);
              for (k = 0; k < nPairs; k++) {
                i2 = (i4 + k * bLen2) + 1;
                for (quartetOffset = 0; quartetOffset < bLen2;
                     quartetOffset++) {
                  ib = i2 + quartetOffset;
                  iwork[quartetOffset] = (short)idx_data[ib];
                  xwork[quartetOffset] = x_data[ib];
                }
                i3 = 0;
                quartetOffset = n;
                ib = i2 - 1;
                do {
                  exitg1 = 0;
                  ib++;
                  if (xwork[i3] >= xwork[quartetOffset]) {
                    idx_data[ib] = iwork[i3];
                    x_data[ib] = xwork[i3];
                    if (i3 + 1 < n) {
                      i3++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    idx_data[ib] = iwork[quartetOffset];
                    x_data[ib] = xwork[quartetOffset];
                    if (quartetOffset + 1 < bLen2) {
                      quartetOffset++;
                    } else {
                      ib -= i3;
                      for (quartetOffset = i3 + 1; quartetOffset <= n;
                           quartetOffset++) {
                        idx_tmp = ib + quartetOffset;
                        idx_data[idx_tmp] = iwork[quartetOffset - 1];
                        x_data[idx_tmp] = xwork[quartetOffset - 1];
                      }
                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }
          quartetOffset = nBlocks << 8;
          ib = nNonNaN - quartetOffset;
          if (ib > 0) {
            merge_block(idx_data, x_data, quartetOffset, ib, 2, iwork_data,
                        xwork_data);
          }
          quartetOffset = 8;
        }
      }
      merge_block(idx_data, x_data, 0, nNonNaN, quartetOffset, iwork_data,
                  xwork_data);
    }
    if ((nNaNs > 0) && (nNonNaN > 0)) {
      for (k = 0; k < nNaNs; k++) {
        quartetOffset = nNonNaN + k;
        xwork_data[k] = x_data[quartetOffset];
        iwork_data[k] = idx_data[quartetOffset];
      }
      for (k = nNonNaN; k >= 1; k--) {
        quartetOffset = (nNaNs + k) - 1;
        x_data[quartetOffset] = x_data[k - 1];
        idx_data[quartetOffset] = idx_data[k - 1];
      }
      if (0 <= nNaNs - 1) {
        memcpy(&x_data[0], &xwork_data[0], nNaNs * sizeof(double));
        memcpy(&idx_data[0], &iwork_data[0], nNaNs * sizeof(int));
      }
    }
  }
}

/* End of code generation (sort.c) */
