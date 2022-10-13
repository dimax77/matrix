#include "s21_matrix.h"

#include <math.h>
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