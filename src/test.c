#include "s21_matrix.h"
#include "stdio.h"
#include "math.h"

int main() {
  int rows = 3;
  matrix_t m, res;
  s21_create_matrix(rows, rows, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;
//   print_matrix(&m);
  s21_inverse_matrix(NULL, NULL);
  // ck_assert_double_eq(res.matrix[1][1], 41.0);
//   print_matrix(&res);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
}