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
  if (A->columns != A->rows) return BAD_MATRIX;
  if (result) s21_create_matrix(A->rows, A->columns, result);
  int status = OK;
  if (result->matrix) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = calc_minor(A, i, j) * pow(-1, i + j);
      }
  } else {
    status = BAD_RES;
  }
  return status;
}
double calc_minor(matrix_t *A, int row, int col) {
  matrix_t new;
  s21_create_matrix(A->rows - 1, A->columns - 1, &new);
  if (new.matrix) {
    int r = 0;
    int s = 0;
    for (int i = 0; i < A->rows; i++) {
      if (i == row) continue;
      for (int j = 0; j < A->columns; j++) {
        if (j == col) continue;
        new.matrix[r][s] = A->matrix[i][j];
        s = s + 1;
      }
      r = r + 1;
    }
  }
  double minor = 0.0;
  s21_determinant(&new, &minor);
  s21_remove_matrix(&new);
  return minor;
}
int s21_determinant(matrix_t *A, double *result) {
  if (!A->matrix) return BAD_MATRIX;
  if (A->columns != A->rows) return BAD_MATRIX;
  *result = 0;
  if (A->rows == 1)
    *result = A->matrix[0][0];
  else if (A->rows == 2)
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  else {
    for (int j = 0; j < A->columns; j++) {
      *result += calc_minor(A, 0, j) * pow(-1, 2 + j) * A->matrix[0][j];
    }
  }
  return 0;
}