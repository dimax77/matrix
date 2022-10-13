#include "s21_matrix.h"

#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
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
  return res;
}
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
  }
}