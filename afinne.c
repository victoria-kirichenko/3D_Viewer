#include "back.h"

double grad_to_rad(double grad) { return grad * M_PI / 180; }

void rotation_x(matrix_t *A, double angle) {
  angle = grad_to_rad(angle);
  for (register int i = 0; i < A->rows; i++) {
    double y = A->matrix[i][1];
    double z = A->matrix[i][2];
    A->matrix[i][1] = cos(angle) * y - sin(angle) * z;
    A->matrix[i][2] = sin(angle) * y + cos(angle) * z;
  }
}

void rotation_y(matrix_t *A, double angle) {
  angle = grad_to_rad(angle);
  for (register int i = 0; i < A->rows; i++) {
    double x = A->matrix[i][0];
    double z = A->matrix[i][2];
    A->matrix[i][0] = cos(angle) * x - sin(angle) * z;
    A->matrix[i][2] = sin(angle) * x + cos(angle) * z;
  }
}

void rotation_z(matrix_t *A, double angle) {
  angle = grad_to_rad(angle);
  for (register int i = 0; i < A->rows; i++) {
    double x = A->matrix[i][0];
    double y = A->matrix[i][1];
    A->matrix[i][0] = cos(angle) * x - sin(angle) * y;
    A->matrix[i][1] = sin(angle) * x + cos(angle) * y;
  }
}

void move_x(matrix_t *A, double a) {
  for (register int i = 0; i < A->rows; i++) {
    A->matrix[i][0] += a;
  }
}

void move_y(matrix_t *A, double a) {
  for (register int i = 0; i < A->rows; i++) {
    A->matrix[i][1] += a;
  }
}

void move_z(matrix_t *A, double a) {
  for (register int i = 0; i < A->rows; i++) {
    A->matrix[i][2] += a;
  }
}

void scale_x(matrix_t *A, double k) {
  for (register int i = 0; i < A->rows; i++) {
    if (k > 0) {
      A->matrix[i][0] *= k;
    } else if (k < 0) {
      A->matrix[i][0] /= (-1) * k;
    }
  }
}

void scale_y(matrix_t *A, double k) {
  for (register int i = 0; i < A->rows; i++) {
    if (k > 0) {
      A->matrix[i][1] *= k;
    } else if (k < 0) {
      A->matrix[i][1] /= (-1) * k;
    }
  }
}

void scale_z(matrix_t *A, double k) {
  for (register int i = 0; i < A->rows; i++) {
    if (k > 0) {
      A->matrix[i][2] *= k;
    } else if (k < 0) {
      A->matrix[i][2] /= (-1) * k;
    }
  }
}

void scale_xyz(matrix_t *A, double k) {
  for (register int i = 0; i < A->rows; i++) {
    if (k > 0) {
      A->matrix[i][0] *= k;
      A->matrix[i][1] *= k;
      A->matrix[i][2] *= k;
    } else if (k < 0) {
      A->matrix[i][0] /= -k;
      A->matrix[i][1] /= -k;
      A->matrix[i][2] /= -k;
    }
  }
}
