/**
 * @file matrix.c
 * @brief Implementation of matrix operations in C
 * @author Joaquin Thiogo
 *
 * This file contains functions for creating matrices, reading,
 * addition, subtraction, multiplication, transpose, and scalar operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char str[100];

typedef struct {
  str name;
  int row;
  int col;
  int *data;
} Matrix;

void read_data_matrix(Matrix m) {
  printf("reading matrix %s\n", m.name);
  for (int i = 0; i < m.row; i++) {
    for (int j = 0; j < m.col; j++) {
      printf("%d ", m.data[i * m.col + j]);
    }
    printf("\n");
  }
}

Matrix create_matrix(const char *name, int row, int col) {
  Matrix m;
  strcpy(m.name, name);
  m.row = row;
  m.col = col;
  m.data = (int *)calloc(m.row * m.col, sizeof(int));

  printf("matrix %s %d x %d is created\n", m.name, m.row, m.col);
  return m;
}

void add_data_matrix(Matrix *m, int *data, int n) {
  if (n > m->col * m->row) {
    fprintf(stderr,
            "err: the number of data elements (%d) exceeds the capacity of the "
            "matrix %d\n",
            n, m->col * m->row);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    m->data[i] = data[i];
  }
}

Matrix transpose(Matrix m) {
  str n_name;
  strcpy(n_name, m.name);
  Matrix n_m = create_matrix(n_name, m.col, m.row);

  int *data = calloc(m.row * m.col, sizeof(int));

  for (int i = 0; i < n_m.row; i++) {
    for (int j = 0; j < n_m.col; j++) {
      data[i * n_m.col + j] = m.data[j * m.col + i];
    }
  }

  add_data_matrix(&n_m, data, m.row * m.col);
  return n_m;
}

Matrix addition(Matrix m1, Matrix m2) {
  if (m1.row != m2.row || m1.col != m2.col) {
    fprintf(stderr,
            "err: matrix sizes do not match for addition.\n"
            "\tMatrix %s: %d x %d\n"
            "\tMatrix %s: %d x %d\n",
            m1.name, m1.row, m1.col, m2.name, m2.row, m2.col);
    exit(EXIT_FAILURE);
  }

  str n_name;
  sprintf(n_name, "%s_Add_%s", m1.name, m2.name);
  Matrix m = create_matrix(n_name, m1.row, m1.col);

  for (int i = 0; i < m.row * m.col; i++) {
    m.data[i] = m1.data[i] + m2.data[i];
  }
  return m;
}

Matrix subtraction(Matrix m1, Matrix m2) {
  if (m1.row != m2.row || m1.col != m2.col) {
    fprintf(stderr,
            "err: matrix sizes do not match for addition.\n"
            "\tMatrix %s: %d x %d\n"
            "\tMatrix %s: %d x %d\n",
            m1.name, m1.row, m1.col, m2.name, m2.row, m2.col);
    exit(EXIT_FAILURE);
  }

  str n_name;
  sprintf(n_name, "%s_Sub_%s", m1.name, m2.name);
  Matrix m = create_matrix(n_name, m1.row, m1.col);

  for (int i = 0; i < m.row * m.col; i++) {
    m.data[i] = m1.data[i] - m2.data[i];
  }
  return m;
}

int main() {
  Matrix matrix = create_matrix("Alpha", 2, 3);
  read_data_matrix(matrix);
  int data_a[] = {1, 3, -2, 0, -2, 2};
  add_data_matrix(&matrix, data_a, sizeof(data_a) / sizeof(int));
  read_data_matrix(matrix);

  Matrix matrix2 = create_matrix("Beta", 2, 3);
  int data_b[] = {2, -1, 3, 1, -1, -3};
  add_data_matrix(&matrix2, data_b, sizeof(data_b) / sizeof(int));
  read_data_matrix(matrix2);

  read_data_matrix(addition(matrix, matrix2));
  read_data_matrix(subtraction(matrix, matrix2));

  return 0;
}
