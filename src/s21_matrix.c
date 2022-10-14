#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (rows && columns) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc((size_t)rows, sizeof(double *));
    if (result->matrix) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc((size_t)columns, sizeof(double));
        if (!result->matrix[i]) {
          res = 1;
          break;
        }
      }
    } else {
      res = 1;
    }
  } else {
    res = 1;
  }
  return res;
}
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
  }
}
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!A->matrix) return FAILURE;
  if (!B->matrix) return FAILURE;
  int status = SUCCESS;
  if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
          status = FAILURE;
          break;
        }
      }
      if (status == FAILURE) break;
    }
  } else {
    status = FAILURE;
  }
  return status;
}
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A->matrix) return BAD_MATRIX;
  if (!B->matrix) return BAD_MATRIX;
  if (A->columns != B->columns || (A->rows != B->rows)) return BAD_RES;
  if (result) s21_create_matrix(A->rows, A->columns, result);
  int status = OK;
  if (result->matrix) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else {
    status = BAD_RES;
  }
  return status;
}
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A->matrix) return BAD_MATRIX;
  if (!B->matrix) return BAD_MATRIX;
  if (A->columns != B->columns || (A->rows != B->rows)) return BAD_RES;
  if (result) s21_create_matrix(A->rows, A->columns, result);
  int status = OK;
  if (result->matrix) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else {
    status = BAD_RES;
  }
  return status;
}
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!A->matrix) return BAD_MATRIX;
  if (result) s21_create_matrix(A->rows, A->columns, result);
  int status = OK;
  if (result->matrix) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    status = BAD_RES;
  }
  return status;
}
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A->matrix) return BAD_MATRIX;
  if (!B->matrix) return BAD_MATRIX;
  if (A->columns != B->rows || (A->rows != B->columns)) return BAD_RES;
  if (result) s21_create_matrix(A->rows, B->columns, result);
  int status = OK;
  int summ = 0;
  if (result->matrix) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          summ += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = summ;
        summ = 0;
      }
    }
  } else {
    status = BAD_RES;
  }
  return status;
}
void print_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      printf("%f ", A->matrix[i][j]);
    }
    printf("\n");
  }
}
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!A->matrix) return BAD_MATRIX;
  if (result) s21_create_matrix(A->columns, A->rows, result);
  int status = OK;
  if (result->matrix) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    status = BAD_RES;
  }
  return status;
}
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!A->matrix) return BAD_MATRIX;
  if (result) s21_create_matrix(A->rows, A->columns, result);
  int status = OK;
  if (result->matrix) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    status = BAD_RES;
  }
  return status;
}
#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 1;

  if (rows > 0 && columns > 0) {
    result->matrix = NULL;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    res = 0;
    for (int i = 0; i < rows && !res; i++) {
      res = 1;
      result->matrix[i] = NULL;
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i]) {
        res = 0;
      }
    }
  }
  result->rows = rows;
  result->columns = columns;
  return res;
}

void s21_fill_matrix(matrix_t A, matrix_t *d, int r, int c) {
  int k = 0;
  for (int i = 0; i < d->rows; i++) {
    int g = 0;
    k = (i >= r) ? i + 1 : i;
    for (int t = 0; t < d->columns; t++) {
      if (t == c) g++;
      d->matrix[i][t] = A.matrix[k][g];
      g++;
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = 2;
  if (!s21_check_on_0(*A, *A)) {
    if (A->columns == A->rows) {
      double det = 0;
      s21_determinant(A, &det);
      if (det) {
        ret = 0;
        matrix_t for_calc = {NULL, 0, 0};
        matrix_t trans = {NULL, 0, 0};
        s21_calc_complements(A, &for_calc);
        s21_transpose(&for_calc, &trans);
        s21_mult_number(&trans, 1. / det, result);
        s21_remove_matrix(&for_calc);
        s21_remove_matrix(&trans);
      }
    }
  } else {
    ret = 1;
  }

  return ret;
}

int s21_determinant(matrix_t *A, double *result) {
  int ret = 2;
  if (!s21_check_on_0(*A, *A)) {
    if (A->columns == A->rows) {
      ret = 0;
      if (A->columns > 2) {
        ret = 0;
        int r = A->columns - 1;
        for (int i = 0; i < A->columns; i++) {
          matrix_t d = {NULL, 0, 0};
          s21_create_matrix(r, r, &d);
          s21_fill_matrix(*A, &d, 0, i);
          double mul = A->matrix[0][i];
          if (d.columns == 2) {
            *result += pow(-1, i) * s21_sum_2x2m_w_mul(d, mul);
            s21_remove_matrix(&d);
          } else {
            double old_res = *result;
            s21_determinant(&d, result);
            *result = old_res + (*result - old_res) * (mul * pow(-1, i));
            s21_remove_matrix(&d);
          }
        }
      } else {
        ret = 0;
        *result += s21_sum_2x2m_w_mul(*A, 1.);
      }
    }
  } else {
    ret = 1;
  }
  return ret;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = 2;
  if (!s21_check_on_0(*A, *A)) {
    if (A->columns == A->rows && A->rows > 2) {
      if (!s21_create_matrix(A->columns, A->rows, result)) {
        ret = 0;
        for (int i = 0; i < A->columns; i++) {
          for (int t = 0; t < A->rows; t++) {
            matrix_t min = {NULL, 0, 0};
            double res = 0;
            s21_create_matrix(A->columns - 1, A->rows - 1, &min);
            s21_fill_matrix(*A, &min, i, t);
            s21_determinant(&min, &res);
            result->matrix[i][t] = res * pow(-1, i + t);
            s21_remove_matrix(&min);
          }
        }
      }
    }
  } else {
    ret = 1;
  }
  return ret;
}

double s21_sum_2x2m_w_mul(matrix_t A, double mul) {
  double ret = 0;
  if (A.columns == 1) {
    ret = A.matrix[0][0];
  } else {
    ret = mul * ((A.matrix[0][0] * A.matrix[1][1]) -
                 (A.matrix[0][1] * A.matrix[1][0]));
  }
  return ret;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = 2;
  if (!s21_check_on_0(*A, *A)) {
    if (!s21_create_matrix(A->columns, A->rows, result)) {
      ret = 0;
      for (int i = 0; i < A->columns; i++) {
        for (int t = 0; t < A->rows; t++) {
          result->matrix[i][t] += A->matrix[t][i];
        }
      }
    } else {
      ret = 1;
    }
  } else {
    ret = 1;
  }
  return ret;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 2;
  if (!s21_check_on_0(*A, *B)) {
    if (A->columns == B->rows && A->rows == B->columns) {
      if (!s21_create_matrix(A->rows, B->columns, result)) {
        ret = 0;
        for (int i = 0; i < A->rows; i++) {
          for (int t = 0; t < B->columns; t++) {
            int k = 0;
            while (k < A->columns) {
              result->matrix[i][t] += A->matrix[i][k] * B->matrix[k][t];
              k++;
            }
          }
        }
      } else {
        ret = 1;
      }
    }
  } else {
    ret = 1;
  }
  return ret;
}

int s21_check_on_0(matrix_t a, matrix_t b) {
  int ret = 0;
  if (a.columns < 1 || b.columns < 1 || a.rows < 1 || b.rows < 1) ret = 1;
  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = 2;
  if (!s21_check_on_0(*A, *A)) {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      ret = 0;
      for (int i = 0; i < A->rows; i++) {
        for (int t = 0; t < A->columns; t++) {
          result->matrix[i][t] = A->matrix[i][t] * number;
        }
      }
    }
  } else {
    ret = 1;
  }

  return ret;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 2;
  if (!s21_check_on_0(*A, *B)) {
    if (A->columns == B->columns && A->rows == B->rows) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        ret = 0;
        for (int i = 0; i < A->rows; i++) {
          for (int t = 0; t < A->columns; t++) {
            result->matrix[i][t] = A->matrix[i][t] + B->matrix[i][t];
          }
        }
      } else {
        ret = 1;
      }
    }
  } else {
    ret = 1;
  }
  return ret;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 2;
  if (!s21_check_on_0(*A, *B)) {
    if (A->columns == B->columns && A->rows == B->rows) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        ret = 0;
        for (int i = 0; i < A->rows; i++) {
          for (int t = 0; t < A->columns; t++) {
            result->matrix[i][t] = A->matrix[i][t] - B->matrix[i][t];
          }
        }
      } else {
        ret = 1;
      }
    }
  } else {
    ret = 1;
  }
  return ret;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->columns = 0;
    A->rows = 0;
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = FAILURE;
  if (A->columns == B->columns && A->rows == B->rows) {
    ret = SUCCESS;
    for (int i = 0; i < A->rows && ret; i++) {
      for (int t = 0; t < A->columns && ret; t++) {
        if (fabs(A->matrix[i][t] - B->matrix[i][t]) > 1e-7) {
          ret = FAILURE;
        }
      }
    }
  }
  return ret;
}